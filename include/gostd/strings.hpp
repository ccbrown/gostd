#pragma once

#include <gostd.hpp>
#include <gostd/unicode/utf8.hpp>

namespace gostd::strings {

static bool HasPrefix(String s, String prefix) {
    if (prefix.Len() > s.Len()) {
        return false;
    }
    for (Int i = 0; i < prefix.Len(); ++i) {
        if (s[i] != prefix[i]) {
            return false;
        }
    }
    return true;
}

static bool HasSuffix(String s, String suffix) {
    if (suffix.Len() > s.Len()) {
        return false;
    }
    for (Int i = 0; i < suffix.Len(); ++i) {
        if (s[s.Len() - suffix.Len() + i] != suffix[i]) {
            return false;
        }
    }
    return true;
}

static Int IndexByte(String s, Byte b) {
    for (Int i = 0; i < s.Len(); i++) {
        if (s[i] == b) {
            return i;
        }
    }
    return -1;
}

static Int IndexRune(String s, Rune r) {
    if (r >= 0 && r < unicode::utf8::RuneSelf) {
        return IndexByte(s, Byte(r));
    }
    Panic("not yet implemented");
    return -1;
}

static Func<bool(Rune)> makeCutsetFunc(String cutset) {
    return [=](Rune r) {
        return IndexRune(cutset, r) >= 0;
    };
}

static String TrimRightFunc(String s, Func<bool(Rune)> f) {
    // TODO: utf8
    while (s.Len() > 0 && f(s[s.Len() - 1])) {
        s = s.Head(s.Len()-1);
    }
    return s;
}

static String TrimRight(String s, String cutset) {
    return TrimRightFunc(s, makeCutsetFunc(cutset));
}

} // namespace gostd::strings
