// THIS FILE WAS GENERATED VIA TRANSPILING. DO NOT MODIFY.
#pragma once

#include <gostd.hpp>

namespace gostd::unicode::utf8 {

::gostd::Tuple<::gostd::Rune, ::gostd::Int> DecodeLastRune(::gostd::Slice<::gostd::Byte> p);

::gostd::Tuple<::gostd::Rune, ::gostd::Int> DecodeLastRuneInString(::gostd::String s);

::gostd::Tuple<::gostd::Rune, ::gostd::Int> DecodeRune(::gostd::Slice<::gostd::Byte> p);

::gostd::Tuple<::gostd::Rune, ::gostd::Int> DecodeRuneInString(::gostd::String s);

::gostd::Int EncodeRune(::gostd::Slice<::gostd::Byte> p, ::gostd::Rune r);

::gostd::Bool FullRune(::gostd::Slice<::gostd::Byte> p);

::gostd::Bool FullRuneInString(::gostd::String s);

constexpr auto MaxRune = ::gostd::UntypedConstant(1114111);

::gostd::Int RuneCount(::gostd::Slice<::gostd::Byte> p);

::gostd::Int RuneCountInString(::gostd::String s);

constexpr auto RuneError = ::gostd::UntypedConstant(65533);

::gostd::Int RuneLen(::gostd::Rune r);

constexpr auto RuneSelf = ::gostd::UntypedConstant(128);

::gostd::Bool RuneStart(::gostd::Byte b);

constexpr auto UTFMax = ::gostd::UntypedConstant(4);

::gostd::Bool Valid(::gostd::Slice<::gostd::Byte> p);

::gostd::Bool ValidRune(::gostd::Rune r);

::gostd::Bool ValidString(::gostd::String s);

struct acceptRange {
    ::gostd::Uint8 lo;
    ::gostd::Uint8 hi;
};

extern ::gostd::Array<acceptRange, 5> acceptRanges;

constexpr auto as = ::gostd::UntypedConstant(240);

extern ::gostd::Array<::gostd::Uint8, 256> first;

constexpr auto hicb = ::gostd::UntypedConstant(191);

constexpr auto locb = ::gostd::UntypedConstant(128);

constexpr auto mask2 = ::gostd::UntypedConstant(31);

constexpr auto mask3 = ::gostd::UntypedConstant(15);

constexpr auto mask4 = ::gostd::UntypedConstant(7);

constexpr auto maskx = ::gostd::UntypedConstant(63);

constexpr auto rune1Max = ::gostd::UntypedConstant(((1<<7)-1));

constexpr auto rune2Max = ::gostd::UntypedConstant(((1<<11)-1));

constexpr auto rune3Max = ::gostd::UntypedConstant(((1<<16)-1));

constexpr auto s1 = ::gostd::UntypedConstant(2);

constexpr auto s2 = ::gostd::UntypedConstant(19);

constexpr auto s3 = ::gostd::UntypedConstant(3);

constexpr auto s4 = ::gostd::UntypedConstant(35);

constexpr auto s5 = ::gostd::UntypedConstant(52);

constexpr auto s6 = ::gostd::UntypedConstant(4);

constexpr auto s7 = ::gostd::UntypedConstant(68);

constexpr auto surrogateMax = ::gostd::UntypedConstant(57343);

constexpr auto surrogateMin = ::gostd::UntypedConstant(55296);

constexpr auto t1 = ::gostd::UntypedConstant(0);

constexpr auto t2 = ::gostd::UntypedConstant(192);

constexpr auto t3 = ::gostd::UntypedConstant(224);

constexpr auto t4 = ::gostd::UntypedConstant(240);

constexpr auto t5 = ::gostd::UntypedConstant(248);

constexpr auto tx = ::gostd::UntypedConstant(128);

constexpr auto xx = ::gostd::UntypedConstant(241);

}
