#pragma once

#include <cx.hpp>
#include <cx/unicode/utf8.hpp>

namespace cx::strings {

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

} // namespace cx::strings
