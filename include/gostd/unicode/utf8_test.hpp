// THIS FILE WAS GENERATED VIA TRANSPILING. DO NOT MODIFY.
#pragma once

#include <gostd.hpp>
#include <gostd/bytes.hpp>
#include <gostd/fmt.hpp>
#include <gostd/testing.hpp>
#include <gostd/unicode.hpp>
#include <gostd/unicode/utf8.hpp>

namespace gostd::unicode::utf8_test {

void BenchmarkDecodeASCIIRune(::gostd::Ptr<::gostd::testing::B> b);

void BenchmarkDecodeJapaneseRune(::gostd::Ptr<::gostd::testing::B> b);

void BenchmarkEncodeASCIIRune(::gostd::Ptr<::gostd::testing::B> b);

void BenchmarkEncodeJapaneseRune(::gostd::Ptr<::gostd::testing::B> b);

void BenchmarkFullASCIIRune(::gostd::Ptr<::gostd::testing::B> b);

void BenchmarkFullJapaneseRune(::gostd::Ptr<::gostd::testing::B> b);

void BenchmarkRuneCountInStringTenASCIIChars(::gostd::Ptr<::gostd::testing::B> b);

void BenchmarkRuneCountInStringTenJapaneseChars(::gostd::Ptr<::gostd::testing::B> b);

void BenchmarkRuneCountTenASCIIChars(::gostd::Ptr<::gostd::testing::B> b);

void BenchmarkRuneCountTenJapaneseChars(::gostd::Ptr<::gostd::testing::B> b);

void BenchmarkValidStringTenASCIIChars(::gostd::Ptr<::gostd::testing::B> b);

void BenchmarkValidStringTenJapaneseChars(::gostd::Ptr<::gostd::testing::B> b);

void BenchmarkValidTenASCIIChars(::gostd::Ptr<::gostd::testing::B> b);

void BenchmarkValidTenJapaneseChars(::gostd::Ptr<::gostd::testing::B> b);

void ExampleDecodeLastRune();

void ExampleDecodeLastRuneInString();

void ExampleDecodeRune();

void ExampleDecodeRuneInString();

void ExampleEncodeRune();

void ExampleFullRune();

void ExampleFullRuneInString();

void ExampleRuneCount();

void ExampleRuneCountInString();

void ExampleRuneLen();

void ExampleRuneStart();

void ExampleValid();

void ExampleValidRune();

void ExampleValidString();

struct RuneCountTest {
    ::gostd::String in;
    ::gostd::Int out;
};

struct RuneLenTest {
    ::gostd::Rune r;
    ::gostd::Int size;
};

void TestConstants(::gostd::Ptr<::gostd::testing::T> t);

void TestDecodeInvalidSequence(::gostd::Ptr<::gostd::testing::T> t);

void TestDecodeRune(::gostd::Ptr<::gostd::testing::T> t);

void TestDecodeSurrogateRune(::gostd::Ptr<::gostd::testing::T> t);

void TestEncodeRune(::gostd::Ptr<::gostd::testing::T> t);

void TestFullRune(::gostd::Ptr<::gostd::testing::T> t);

void TestIntConversion(::gostd::Ptr<::gostd::testing::T> t);

void TestNegativeRune(::gostd::Ptr<::gostd::testing::T> t);

void TestRuneCount(::gostd::Ptr<::gostd::testing::T> t);

void TestRuneLen(::gostd::Ptr<::gostd::testing::T> t);

void TestSequencing(::gostd::Ptr<::gostd::testing::T> t);

void TestValid(::gostd::Ptr<::gostd::testing::T> t);

void TestValidRune(::gostd::Ptr<::gostd::testing::T> t);

struct Utf8Map {
    ::gostd::Rune r;
    ::gostd::String str;
};

struct ValidRuneTest {
    ::gostd::Rune r;
    ::gostd::Bool ok;
};

struct ValidTest {
    ::gostd::String in;
    ::gostd::Bool out;
};

void init();

extern ::gostd::Slice<::gostd::String> invalidSequenceTests;

extern ::gostd::Slice<RuneCountTest> runecounttests;

extern ::gostd::Slice<RuneLenTest> runelentests;

::gostd::Rune runtimeDecodeRune(::gostd::String s);

extern ::gostd::Slice<Utf8Map> surrogateMap;

void testSequence(::gostd::Ptr<::gostd::testing::T> t, ::gostd::String s);

extern ::gostd::Slice<::gostd::String> testStrings;

extern ::gostd::Slice<Utf8Map> utf8map;

extern ::gostd::Slice<ValidTest> validTests;

extern ::gostd::Slice<ValidRuneTest> validrunetests;

}
