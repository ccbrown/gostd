#pragma once

#include <gostd.hpp>
#include <gostd/cpp.hpp>
#include <gostd/errors.hpp>

namespace gostd::strconv {

constexpr const char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";

static String Quote(String s) {
    auto quotedLength = s.Len();
    for (Int i = 0; i < s.Len(); i++) {
        auto c = s[i];
        if (c == '\n' || c == '\t' || c == '\r' || c == '\\' || c == '"') {
            ++quotedLength;
        } else if (c < ' ' || c > '~') {
            quotedLength += 3;
        }
    }
    Slice<Byte> buf(quotedLength);
    auto dest = 0;
    for (Int i = 0; i < s.Len(); i++) {
        auto c = s[i];
        if (c == '\n' || c == '\t' || c == '\r' || c == '\\' || c == '"') {
            buf[dest++] = '\\';
            if (c == '\n') {
                buf[dest++] = 'n';
            } else if (c == '\t') {
                buf[dest++] = 't';
            } else if (c == '\r') {
                buf[dest++] = 'r';
            } else {
                buf[dest++] = c;
            }
        } else if (c < ' ' || c > '~') {
            buf[dest++] = '\\';
            buf[dest++] = 'x';
            buf[dest++] = digits[c >> 4];
            buf[dest++] = digits[c & 0xf];
        } else {
            buf[dest++] = c;
        }
    }
    return String(buf);
}

static String FormatInt(Int64 i, Int base) {
    if (base < 2 || base > 36) {
        Panic("strconv: illegal FormatInt base");
    }
    char buf[66] = {0};
    auto neg = i < 0;
    if (i < 0) {
        i = -i;
    }
    auto pos = sizeof(buf) - 2;
    while (i >= base) {
        buf[pos--] = digits[i % base];
        i /= base;
    }
    buf[pos] = digits[i];
    if (neg) {
        buf[--pos] = '-';
    }
    return buf + pos;
}

static String Itoa(Int i) {
    return FormatInt(Int64(i), 10);
}

struct NumError {
    NumError(String func, String num, Error err) : Func{func}, Num{num}, Err{err} {}

    String Func;
    String Num;
    Error Err;

    String Error() const {
        return "strconv." + Func + ": parsing " + Quote(Num) + ": " + String(Err);
    }
};

extern Error ErrSyntax, ErrRange;

static auto ParseUint(String s, Int base, Int bitSize) {
    struct { Uint64 n = 0; Error err; } ret;

    if (s.Len() == 0) {
        ret.err = New<NumError>("ParseUint", s, ErrSyntax);
        return ret;
    }

    if (base == 0) {
        if (s.Len() > 1 && s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
            return ParseUint(s.Tail(2), 16, bitSize);
        } else if (s[0] == '0') {
            return ParseUint(s.Tail(1), 8, bitSize);
        }
        base = 10;
    }

    auto cutoff = cpp::UINT64_MAX / base + 1;
    auto maxVal = (Uint64(1) << bitSize) - 1;
    if (bitSize == 64) {
        maxVal = -1;
    }

    if (base < 2 || base > 36) {
        ret.err = errors::New("invalid base " + Itoa(base));
        goto Error;
    }

    if (bitSize == 0) {
        bitSize = sizeof(Int) * 8;
    }

    for (Int i = 0; i < s.Len(); ++i) {
        auto c = s[i];

        auto v = base;
        if (c >= '0' && c <= '9') {
            v = c - '0';
        } else if (c >= 'a' && c <= 'z') {
            v = 10 + c - 'a';
        } else if (c >= 'A' && c <= 'Z') {
            v = 10 + c - 'A';
        }

        if (v >= base) {
            ret.err = ErrSyntax;
            goto Error;
        }

        if (ret.n >= cutoff) {
            ret.n = cpp::UINT64_MAX;
            ret.err = ErrRange;
            goto Error;
        }
        ret.n *= base;

        auto n2 = ret.n + v;
        if (n2 < ret.n || n2 > maxVal) {
            ret.n = cpp::UINT64_MAX;
            ret.err = ErrRange;
            goto Error;
        }
        ret.n = n2;
    }

    return ret;

Error:
    ret.err = New<NumError>("ParseUint", s, ret.err);
    return ret;
}

static auto ParseInt(String s, Int base, Int bitSize) {
    struct { Int64 n = 0; Error err; } ret;

    if (s.Len() == 0) {
        ret.err = New<NumError>("ParseInt", s, ErrSyntax);
        return ret;
    }

    auto s0 = s;
    auto neg = false;
    if (s[0] == '+') {
        s = s.Tail(1);
    } else if (s[0] == '-') {
        neg = true;
        s = s.Tail(1);
    }

    auto [un, err] = ParseUint(s, base, bitSize);
    if (err) {
        if (auto [ne, ok] = err.As<Ptr<NumError>>(); ok) {
            ne->Func = "ParseInt";
            ne->Num = s0;
        }
        ret.err = err;
        return ret;
    }

    auto cutoff = Uint64(1) << (bitSize - 1);
    if (!neg && un >= cutoff) {
        ret.n = cutoff - 1;
        ret.err = New<NumError>("ParseInt", s0, ErrRange);
    } else if (neg && un > cutoff) {
        ret.n = -Int64(cutoff);
        ret.err = New<NumError>("ParseInt", s0, ErrRange);
    } else {
        ret.n = un;
        if (neg) {
            ret.n = -ret.n;
        }
    }

    return ret;
}

} // namespace gostd::strconv
