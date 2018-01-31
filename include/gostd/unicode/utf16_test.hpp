// THIS FILE WAS GENERATED VIA TRANSPILING. DO NOT MODIFY.
#pragma once

#include <gostd.hpp>
#include <gostd/reflect.hpp>
#include <gostd/testing.hpp>
#include <gostd/unicode.hpp>
#include <gostd/unicode/utf16.hpp>

namespace gostd::unicode::utf16_test {

void BenchmarkDecodeRune(::gostd::Ptr<::gostd::testing::B> b);

void BenchmarkDecodeValidASCII(::gostd::Ptr<::gostd::testing::B> b);

void BenchmarkDecodeValidJapaneseChars(::gostd::Ptr<::gostd::testing::B> b);

void BenchmarkEncodeRune(::gostd::Ptr<::gostd::testing::B> b);

void BenchmarkEncodeValidASCII(::gostd::Ptr<::gostd::testing::B> b);

void BenchmarkEncodeValidJapaneseChars(::gostd::Ptr<::gostd::testing::B> b);

void TestConstants(::gostd::Ptr<::gostd::testing::T> t);

void TestDecode(::gostd::Ptr<::gostd::testing::T> t);

void TestDecodeRune(::gostd::Ptr<::gostd::testing::T> t);

void TestEncode(::gostd::Ptr<::gostd::testing::T> t);

void TestEncodeRune(::gostd::Ptr<::gostd::testing::T> t);

void TestIsSurrogate(::gostd::Ptr<::gostd::testing::T> t);

struct _struct2729 {
    ::gostd::Rune r1;
    ::gostd::Rune r2;
    ::gostd::Rune want;
};

struct _struct3194 {
    ::gostd::Rune r;
    ::gostd::Bool want;
};

extern ::gostd::Slice<_struct2729> decodeRuneTests;

struct decodeTest {
    ::gostd::Slice<::gostd::Uint16> in;
    ::gostd::Slice<::gostd::Rune> out;
};

extern ::gostd::Slice<decodeTest> decodeTests;

struct encodeTest {
    ::gostd::Slice<::gostd::Rune> in;
    ::gostd::Slice<::gostd::Uint16> out;
};

extern ::gostd::Slice<encodeTest> encodeTests;

extern ::gostd::Slice<_struct3194> surrogateTests;

}
