// THIS FILE WAS GENERATED VIA TRANSPILING. DO NOT MODIFY.
#define GOSTD_TEST 1

#include <gostd/unicode/utf16_test.hpp>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wparentheses-equality"

namespace gostd::unicode::utf16_test {

void TestConstants(::gostd::Ptr<::gostd::testing::T> t) {
if ((::gostd::unicode::utf16::MaxRune!=::gostd::unicode::MaxRune)) {
t->Errorf("utf16.maxRune is wrong: %x should be %x", ::gostd::unicode::utf16::MaxRune, ::gostd::unicode::MaxRune);
};
if ((::gostd::unicode::utf16::ReplacementChar!=::gostd::unicode::ReplacementChar)) {
t->Errorf("utf16.replacementChar is wrong: %x should be %x", ::gostd::unicode::utf16::ReplacementChar, ::gostd::unicode::ReplacementChar);
};
}

::gostd::Slice<encodeTest> encodeTests = ::gostd::Slice<encodeTest>(encodeTest{::gostd::Slice<::gostd::Rune>(1, 2, 3, 4), ::gostd::Slice<::gostd::Uint16>(1, 2, 3, 4)}, encodeTest{::gostd::Slice<::gostd::Rune>(65535, 65536, 65537, 74565, 1114111), ::gostd::Slice<::gostd::Uint16>(65535, 55296, 56320, 55296, 56321, 55304, 57157, 56319, 57343)}, encodeTest{::gostd::Slice<::gostd::Rune>(97, 98, 55295, 55296, 57343, 57344, 1114112, -1), ::gostd::Slice<::gostd::Uint16>(97, 98, 55295, 65533, 65533, 57344, 65533, 65533)});

void TestEncode(::gostd::Ptr<::gostd::testing::T> t) {
for (auto [_, tt] : encodeTests) {
auto out=::gostd::unicode::utf16::Encode(tt.in);
if (!::gostd::reflect::DeepEqual(out, tt.out)) {
t->Errorf("Encode(%x) = %x; want %x", tt.in, out, tt.out);
};
};
}

void TestEncodeRune(::gostd::Ptr<::gostd::testing::T> t) {
for (auto [i, tt] : encodeTests) {
::gostd::Int j=0;
for (auto [_, r] : tt.in) {
auto [r1, r2] = ::gostd::unicode::utf16::EncodeRune(r);
if (((r<65536)||(r>::gostd::unicode::MaxRune))) {
if ((j>=::gostd::Len(tt.out))) {
t->Errorf("#%d: ran out of tt.out", i);
break;
};
if (((r1!=::gostd::unicode::ReplacementChar)||(r2!=::gostd::unicode::ReplacementChar))) {
t->Errorf("EncodeRune(%#x) = %#x, %#x; want 0xfffd, 0xfffd", r, r1, r2);
};
j++;
} else {
if (((j+1)>=::gostd::Len(tt.out))) {
t->Errorf("#%d: ran out of tt.out", i);
break;
};
if (((r1!=::gostd::Rune(tt.out[j]))||(r2!=::gostd::Rune(tt.out[(j+1)])))) {
t->Errorf("EncodeRune(%#x) = %#x, %#x; want %#x, %#x", r, r1, r2, tt.out[j], tt.out[(j+1)]);
};
j+=2;
auto dec=::gostd::unicode::utf16::DecodeRune(r1, r2);
if ((dec!=r)) {
t->Errorf("DecodeRune(%#x, %#x) = %#x; want %#x", r1, r2, dec, r);
};
};
};
if ((j!=::gostd::Len(tt.out))) {
t->Errorf("#%d: EncodeRune didn't generate enough output", i);
};
};
}

::gostd::Slice<decodeTest> decodeTests = ::gostd::Slice<decodeTest>(decodeTest{::gostd::Slice<::gostd::Uint16>(1, 2, 3, 4), ::gostd::Slice<::gostd::Rune>(1, 2, 3, 4)}, decodeTest{::gostd::Slice<::gostd::Uint16>(65535, 55296, 56320, 55296, 56321, 55304, 57157, 56319, 57343), ::gostd::Slice<::gostd::Rune>(65535, 65536, 65537, 74565, 1114111)}, decodeTest{::gostd::Slice<::gostd::Uint16>(55296, 97), ::gostd::Slice<::gostd::Rune>(65533, 97)}, decodeTest{::gostd::Slice<::gostd::Uint16>(57343), ::gostd::Slice<::gostd::Rune>(65533)});

void TestDecode(::gostd::Ptr<::gostd::testing::T> t) {
for (auto [_, tt] : decodeTests) {
auto out=::gostd::unicode::utf16::Decode(tt.in);
if (!::gostd::reflect::DeepEqual(out, tt.out)) {
t->Errorf("Decode(%x) = %x; want %x", tt.in, out, tt.out);
};
};
}

::gostd::Slice<_struct2729> decodeRuneTests = ::gostd::Slice<_struct2729>(_struct2729{55296, 56320, 65536}, _struct2729{55296, 56321, 65537}, _struct2729{55304, 57157, 74565}, _struct2729{56319, 57343, 1114111}, _struct2729{55296, 97, 65533});

void TestDecodeRune(::gostd::Ptr<::gostd::testing::T> t) {
for (auto [i, tt] : decodeRuneTests) {
auto got=::gostd::unicode::utf16::DecodeRune(tt.r1, tt.r2);
if ((got!=tt.want)) {
t->Errorf("%d: DecodeRune(%q, %q) = %v; want %v", i, tt.r1, tt.r2, got, tt.want);
};
};
}

::gostd::Slice<_struct3194> surrogateTests = ::gostd::Slice<_struct3194>(_struct3194{122, false}, _struct3194{27700, false}, _struct3194{65279, false}, _struct3194{65536, false}, _struct3194{119070, false}, _struct3194{1114109, false}, _struct3194{::gostd::Rune(55295), false}, _struct3194{::gostd::Rune(55296), true}, _struct3194{::gostd::Rune(56320), true}, _struct3194{::gostd::Rune(57344), false}, _struct3194{::gostd::Rune(57343), true});

void TestIsSurrogate(::gostd::Ptr<::gostd::testing::T> t) {
for (auto [i, tt] : surrogateTests) {
auto got=::gostd::unicode::utf16::IsSurrogate(tt.r);
if ((got!=tt.want)) {
t->Errorf("%d: IsSurrogate(%q) = %v; want %v", i, tt.r, got, tt.want);
};
};
}

void BenchmarkDecodeValidASCII(::gostd::Ptr<::gostd::testing::B> b) {
auto data=::gostd::Slice<::gostd::Uint16>(104, 101, 108, 108, 111, 32, 119, 111, 114, 108, 100);
for (::gostd::Int i=0;(i<b->N);i++){
::gostd::unicode::utf16::Decode(data);
};
}

void BenchmarkDecodeValidJapaneseChars(::gostd::Ptr<::gostd::testing::B> b) {
auto data=::gostd::Slice<::gostd::Uint16>(26085, 26412, 35486, 26085, 26412, 35486, 26085, 26412, 35486);
for (::gostd::Int i=0;(i<b->N);i++){
::gostd::unicode::utf16::Decode(data);
};
}

void BenchmarkDecodeRune(::gostd::Ptr<::gostd::testing::B> b) {
auto rs=::gostd::Make<::gostd::Slice<::gostd::Rune>>(10);
for (auto [i, u] : ::gostd::Slice<::gostd::Rune>(120016, 120017, 120018, 120019, 120020)) {
auto [_binding4609, _binding4618] = ::gostd::unicode::utf16::EncodeRune(u); rs[(2*i)] = _binding4609; rs[((2*i)+1)] = _binding4618;
};
b->ResetTimer();
for (::gostd::Int i=0;(i<b->N);i++){
for (::gostd::Int j=0;(j<5);j++){
::gostd::unicode::utf16::DecodeRune(rs[(2*j)], rs[((2*j)+1)]);
};
};
}

void BenchmarkEncodeValidASCII(::gostd::Ptr<::gostd::testing::B> b) {
auto data=::gostd::Slice<::gostd::Rune>(104, 101, 108, 108, 111);
for (::gostd::Int i=0;(i<b->N);i++){
::gostd::unicode::utf16::Encode(data);
};
}

void BenchmarkEncodeValidJapaneseChars(::gostd::Ptr<::gostd::testing::B> b) {
auto data=::gostd::Slice<::gostd::Rune>(26085, 26412, 35486);
for (::gostd::Int i=0;(i<b->N);i++){
::gostd::unicode::utf16::Encode(data);
};
}

void BenchmarkEncodeRune(::gostd::Ptr<::gostd::testing::B> b) {
for (::gostd::Int i=0;(i<b->N);i++){
for (auto [_, u] : ::gostd::Slice<::gostd::Rune>(120016, 120017, 120018, 120019, 120020)) {
::gostd::unicode::utf16::EncodeRune(u);
};
};
}

} // namespace gostd::unicode::utf16_test

#pragma clang diagnostic pop
