// THIS FILE WAS GENERATED VIA TRANSPILING. DO NOT MODIFY.
#pragma once

#include <gostd.hpp>

namespace gostd::unicode::utf8 {

::gostd::Tuple<::gostd::Rune, ::gostd::Int> DecodeRuneInString(::gostd::String s);


constexpr auto rune1Max = ::gostd::UntypedConstant(((1<<7)-1));


constexpr auto s5 = ::gostd::UntypedConstant(52);


constexpr auto xx = ::gostd::UntypedConstant(241);


constexpr auto MaxRune = ::gostd::UntypedConstant(1114111);


constexpr auto locb = ::gostd::UntypedConstant(128);


constexpr auto tx = ::gostd::UntypedConstant(128);


constexpr auto RuneError = ::gostd::UntypedConstant(65533);


::gostd::Tuple<::gostd::Rune, ::gostd::Int> DecodeLastRune(::gostd::Slice<::gostd::Byte> p);


constexpr auto mask2 = ::gostd::UntypedConstant(31);


constexpr auto as = ::gostd::UntypedConstant(240);


::gostd::Tuple<::gostd::Rune, ::gostd::Int> DecodeRune(::gostd::Slice<::gostd::Byte> p);


constexpr auto s1 = ::gostd::UntypedConstant(2);


::gostd::Bool FullRune(::gostd::Slice<::gostd::Byte> p);


::gostd::Int EncodeRune(::gostd::Slice<::gostd::Byte> p, ::gostd::Rune r);


constexpr auto RuneSelf = ::gostd::UntypedConstant(128);


::gostd::Bool Valid(::gostd::Slice<::gostd::Byte> p);


constexpr auto s2 = ::gostd::UntypedConstant(19);


::gostd::Bool ValidRune(::gostd::Rune r);


constexpr auto surrogateMax = ::gostd::UntypedConstant(57343);


extern ::gostd::Array<::gostd::Uint8, 256> first;


constexpr auto mask4 = ::gostd::UntypedConstant(7);


constexpr auto t3 = ::gostd::UntypedConstant(224);


::gostd::Tuple<::gostd::Rune, ::gostd::Int> DecodeLastRuneInString(::gostd::String s);


constexpr auto maskx = ::gostd::UntypedConstant(63);


constexpr auto s4 = ::gostd::UntypedConstant(35);


::gostd::Bool FullRuneInString(::gostd::String s);


constexpr auto surrogateMin = ::gostd::UntypedConstant(55296);


::gostd::Bool ValidString(::gostd::String s);


constexpr auto t1 = ::gostd::UntypedConstant(0);


constexpr auto rune3Max = ::gostd::UntypedConstant(((1<<16)-1));


constexpr auto mask3 = ::gostd::UntypedConstant(15);


constexpr auto t2 = ::gostd::UntypedConstant(192);


::gostd::Int RuneLen(::gostd::Rune r);


constexpr auto s6 = ::gostd::UntypedConstant(4);


struct acceptRange {
::gostd::Uint8 lo;
::gostd::Uint8 hi;
};


constexpr auto rune2Max = ::gostd::UntypedConstant(((1<<11)-1));


extern ::gostd::Array<acceptRange, 5> acceptRanges;


constexpr auto s7 = ::gostd::UntypedConstant(68);


constexpr auto hicb = ::gostd::UntypedConstant(191);


constexpr auto t5 = ::gostd::UntypedConstant(248);


constexpr auto UTFMax = ::gostd::UntypedConstant(4);


constexpr auto s3 = ::gostd::UntypedConstant(3);


::gostd::Int RuneCount(::gostd::Slice<::gostd::Byte> p);


constexpr auto t4 = ::gostd::UntypedConstant(240);


::gostd::Bool RuneStart(::gostd::Byte b);


::gostd::Int RuneCountInString(::gostd::String s);


}
