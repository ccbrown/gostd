// THIS FILE WAS GENERATED VIA TRANSPILING. DO NOT MODIFY.
#pragma once

#include <gostd.hpp>

namespace gostd::unicode::utf16 {

::gostd::Slice<::gostd::Rune> Decode(::gostd::Slice<::gostd::Uint16> s);

::gostd::Rune DecodeRune(::gostd::Rune r1, ::gostd::Rune r2);

::gostd::Slice<::gostd::Uint16> Encode(::gostd::Slice<::gostd::Rune> s);

::gostd::Tuple<::gostd::Rune, ::gostd::Rune> EncodeRune(::gostd::Rune r);

::gostd::Bool IsSurrogate(::gostd::Rune r);

constexpr auto maxRune = ::gostd::UntypedConstant(1114111);

#if GOSTD_TEST
constexpr auto MaxRune = ::gostd::UntypedConstant(maxRune);
#endif

constexpr auto replacementChar = ::gostd::UntypedConstant(65533);

#if GOSTD_TEST
constexpr auto ReplacementChar = ::gostd::UntypedConstant(replacementChar);
#endif

constexpr auto surr1 = ::gostd::UntypedConstant(55296);

constexpr auto surr2 = ::gostd::UntypedConstant(56320);

constexpr auto surr3 = ::gostd::UntypedConstant(57344);

constexpr auto surrSelf = ::gostd::UntypedConstant(65536);

}
