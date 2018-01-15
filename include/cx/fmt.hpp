#pragma once

#include <cx.hpp>
#include <cx/cpp.hpp>
#include <cx/os.hpp>

namespace cx::fmt {

template <typename T>
static String uitoa(T v) {
    char buf[33] = {0};
    auto i = sizeof(buf) - 2;
    while (v >= 10) {
        buf[i] = v%10 + '0';
        --i;
        v /= 10;
    }
    buf[i] = v + '0';
    return buf + i;
}

template <typename T>
static String itoa(T v) {
    if (v < 0) {
        return "-" + uitoa(-v);
    }
    return uitoa(v);
}

template <typename T, typename = void>
struct formatter {
    static String sprint(T arg) {
        return String(arg);
    }
};

template <typename T>
struct formatter<T, typename cpp::enable_if<cpp::is_same<T, char>::value>::type> {
    static String sprint(T arg) {
        return String(&arg, 1);
    }
};

template <typename T>
struct formatter<T, typename cpp::enable_if<!cpp::is_same<T, char>::value && cpp::is_integral<T>::value && !cpp::is_unsigned<T>::value>::type> {
    static String sprint(T arg) {
        return itoa(arg);
    }
};

template <typename T>
struct formatter<T, typename cpp::enable_if<cpp::is_integral<T>::value && cpp::is_unsigned<T>::value>::type> {
    static String sprint(T arg) {
        return uitoa(arg);
    }
};

template <typename T>
struct formatter<T, typename cpp::enable_if<cpp::is_enum<T>::value>::type> {
    using U = typename cpp::underlying_type<T>::type;
    static String sprint(T arg) {
        return formatter<U>::sprint(static_cast<U>(arg));
    }
};

static String Sprint() {
    return "";
}

template <typename Arg, typename... Args>
String Sprint(Arg arg, Args... args) {
    auto ret = formatter<Arg>::sprint(arg);
    if (sizeof...(args) > 0) {
        ret = ret + " ";
    }
    return ret + Sprint(args...);
}

template <typename Writer, typename... Args>
auto Fprint(Writer w, Args... args) {
    return w->Write(Slice<Byte>(Sprint(args...)));
}

template <typename... Args>
auto Print(Args... args) {
    return Fprint(os::Stdout, args...);
}

template <typename Writer, typename... Args>
auto Fprintln(Writer w, Args... args) {
    struct { int n; Error err; } ret;
    auto [n, err] = Fprint(w, args...);
    ret.n = n;
    ret.err = err;
    if (!err) {
        auto [n, err] = Fprint(w, "\n");
        ret.n += n;
        ret.err = err;
    }
    return ret;
}

template <typename... Args>
auto Println(Args... args) {
    return Fprintln(os::Stdout, args...);
}

} // namespace cx::fmt

