// THIS FILE WAS GENERATED VIA TRANSPILING. DO NOT MODIFY.
#pragma once

#include <gostd.hpp>

namespace gostd::unicode::utf8 {

::gostd::Int RuneLen(::gostd::Rune r);

constexpr auto MaxRune = ::gostd::UntypedConstant(1114111);

constexpr auto maskx = ::gostd::UntypedConstant(63);

::gostd::Bool FullRune(::gostd::Slice<::gostd::Byte> p);

constexpr auto UTFMax = ::gostd::UntypedConstant(4);

constexpr auto t5 = ::gostd::UntypedConstant(248);

::gostd::Int EncodeRune(::gostd::Slice<::gostd::Byte> p, ::gostd::Rune r);

::gostd::Bool ValidString(::gostd::String s);

struct acceptRange {
    ::gostd::Uint8 lo;
    ::gostd::Uint8 hi;
};

::gostd::Tuple<::gostd::Rune, ::gostd::Int> DecodeRune(::gostd::Slice<::gostd::Byte> p);

constexpr auto RuneError = ::gostd::UntypedConstant(65533);

constexpr auto rune1Max = ::gostd::UntypedConstant(((1<<7)-1));

constexpr auto surrogateMax = ::gostd::UntypedConstant(57343);

constexpr auto s2 = ::gostd::UntypedConstant(19);

constexpr auto mask4 = ::gostd::UntypedConstant(7);

constexpr auto s1 = ::gostd::UntypedConstant(2);

constexpr auto surrogateMin = ::gostd::UntypedConstant(55296);

constexpr auto tx = ::gostd::UntypedConstant(128);

constexpr auto RuneSelf = ::gostd::UntypedConstant(128);

constexpr auto t4 = ::gostd::UntypedConstant(240);

constexpr auto s5 = ::gostd::UntypedConstant(52);

constexpr auto s3 = ::gostd::UntypedConstant(3);

constexpr auto rune3Max = ::gostd::UntypedConstant(((1<<16)-1));

constexpr auto rune2Max = ::gostd::UntypedConstant(((1<<11)-1));

constexpr auto s6 = ::gostd::UntypedConstant(4);

constexpr auto mask2 = ::gostd::UntypedConstant(31);

::gostd::Bool FullRuneInString(::gostd::String s);

constexpr auto hicb = ::gostd::UntypedConstant(191);

constexpr auto t3 = ::gostd::UntypedConstant(224);

constexpr auto as = ::gostd::UntypedConstant(240);

constexpr auto s7 = ::gostd::UntypedConstant(68);

extern ::gostd::Array<::gostd::Uint8, 256> first;

constexpr auto xx = ::gostd::UntypedConstant(241);

extern ::gostd::Array<acceptRange, 5> acceptRanges;

::gostd::Tuple<::gostd::Rune, ::gostd::Int> DecodeRuneInString(::gostd::String s);

constexpr auto mask3 = ::gostd::UntypedConstant(15);

constexpr auto s4 = ::gostd::UntypedConstant(35);

::gostd::Int RuneCountInString(::gostd::String s);

::gostd::Bool Valid(::gostd::Slice<::gostd::Byte> p);

constexpr auto locb = ::gostd::UntypedConstant(128);

constexpr auto t1 = ::gostd::UntypedConstant(0);

::gostd::Int RuneCount(::gostd::Slice<::gostd::Byte> p);

::gostd::Bool ValidRune(::gostd::Rune r);

constexpr auto t2 = ::gostd::UntypedConstant(192);

::gostd::Bool RuneStart(::gostd::Byte b);

::gostd::Tuple<::gostd::Rune, ::gostd::Int> DecodeLastRune(::gostd::Slice<::gostd::Byte> p);

::gostd::Tuple<::gostd::Rune, ::gostd::Int> DecodeLastRuneInString(::gostd::String s);

}
