// THIS FILE WAS GENERATED VIA TRANSPILING. DO NOT MODIFY.
#pragma once

#include <gostd.hpp>

namespace gostd::unicode::utf16 {

constexpr auto surr3 = ::gostd::UntypedConstant(57344);


::gostd::Rune DecodeRune(::gostd::Rune r1, ::gostd::Rune r2);


constexpr auto maxRune = ::gostd::UntypedConstant(1114111);


constexpr auto replacementChar = ::gostd::UntypedConstant(65533);


constexpr auto surr1 = ::gostd::UntypedConstant(55296);


constexpr auto surr2 = ::gostd::UntypedConstant(56320);


constexpr auto surrSelf = ::gostd::UntypedConstant(65536);


::gostd::Bool IsSurrogate(::gostd::Rune r);


::gostd::Slice<::gostd::Rune> Decode(::gostd::Slice<::gostd::Uint16> s);


::gostd::Slice<::gostd::Uint16> Encode(::gostd::Slice<::gostd::Rune> s);


::gostd::Tuple<::gostd::Rune, ::gostd::Rune> EncodeRune(::gostd::Rune r);


}
