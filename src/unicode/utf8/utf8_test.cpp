// THIS FILE WAS GENERATED VIA TRANSPILING. DO NOT MODIFY.
#include <gostd/unicode/utf8_test.hpp>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wparentheses-equality"

namespace gostd::unicode::utf8_test {

void init() {
if ((::gostd::unicode::utf8::MaxRune!=::gostd::unicode::MaxRune)) {
::gostd::Panic("utf8.MaxRune is wrong");
};
if ((::gostd::unicode::utf8::RuneError!=::gostd::unicode::ReplacementChar)) {
::gostd::Panic("utf8.RuneError is wrong");
};
}

void TestConstants(::gostd::Ptr<::gostd::testing::T> t) {
if ((::gostd::unicode::utf8::MaxRune!=::gostd::unicode::MaxRune)) {
t->Errorf("utf8.MaxRune is wrong: %x should be %x", ::gostd::unicode::utf8::MaxRune, ::gostd::unicode::MaxRune);
};
if ((::gostd::unicode::utf8::RuneError!=::gostd::unicode::ReplacementChar)) {
t->Errorf("utf8.RuneError is wrong: %x should be %x", ::gostd::unicode::utf8::RuneError, ::gostd::unicode::ReplacementChar);
};
}

::gostd::Slice<Utf8Map> utf8map = ::gostd::Slice<Utf8Map>(Utf8Map{0, "\x00"""}, Utf8Map{1, "\x01"""}, Utf8Map{126, "~"}, Utf8Map{127, "\x7f"""}, Utf8Map{128, "\xc2""\x80"""}, Utf8Map{129, "\xc2""\x81"""}, Utf8Map{191, "\xc2""\xbf"""}, Utf8Map{192, "\xc3""\x80"""}, Utf8Map{193, "\xc3""\x81"""}, Utf8Map{200, "\xc3""\x88"""}, Utf8Map{208, "\xc3""\x90"""}, Utf8Map{224, "\xc3""\xa0"""}, Utf8Map{240, "\xc3""\xb0"""}, Utf8Map{248, "\xc3""\xb8"""}, Utf8Map{255, "\xc3""\xbf"""}, Utf8Map{256, "\xc4""\x80"""}, Utf8Map{2047, "\xdf""\xbf"""}, Utf8Map{1024, "\xd0""\x80"""}, Utf8Map{2048, "\xe0""\xa0""\x80"""}, Utf8Map{2049, "\xe0""\xa0""\x81"""}, Utf8Map{4096, "\xe1""\x80""\x80"""}, Utf8Map{53248, "\xed""\x80""\x80"""}, Utf8Map{55295, "\xed""\x9f""\xbf"""}, Utf8Map{57344, "\xee""\x80""\x80"""}, Utf8Map{65534, "\xef""\xbf""\xbe"""}, Utf8Map{65535, "\xef""\xbf""\xbf"""}, Utf8Map{65536, "\xf0""\x90""\x80""\x80"""}, Utf8Map{65537, "\xf0""\x90""\x80""\x81"""}, Utf8Map{262144, "\xf1""\x80""\x80""\x80"""}, Utf8Map{1114110, "\xf4""\x8f""\xbf""\xbe"""}, Utf8Map{1114111, "\xf4""\x8f""\xbf""\xbf"""}, Utf8Map{65533, "\xef""\xbf""\xbd"""});

::gostd::Slice<Utf8Map> surrogateMap = ::gostd::Slice<Utf8Map>(Utf8Map{55296, "\xed""\xa0""\x80"""}, Utf8Map{57343, "\xed""\xbf""\xbf"""});

::gostd::Slice<::gostd::String> testStrings = ::gostd::Slice<::gostd::String>("", "abcd", "\xe2""\x98""\xba""\xe2""\x98""\xbb""\xe2""\x98""\xb9""", "\xe6""\x97""\xa5""a\xe6""\x9c""\xac""b\xe8""\xaa""\x9e""\xc3""\xa7""\xe6""\x97""\xa5""\xc3""\xb0""\xe6""\x9c""\xac""\xc3""\x8a""\xe8""\xaa""\x9e""\xc3""\xbe""\xe6""\x97""\xa5""\xc2""\xa5""\xe6""\x9c""\xac""\xc2""\xbc""\xe8""\xaa""\x9e""i\xe6""\x97""\xa5""\xc2""\xa9""", "\xe6""\x97""\xa5""a\xe6""\x9c""\xac""b\xe8""\xaa""\x9e""\xc3""\xa7""\xe6""\x97""\xa5""\xc3""\xb0""\xe6""\x9c""\xac""\xc3""\x8a""\xe8""\xaa""\x9e""\xc3""\xbe""\xe6""\x97""\xa5""\xc2""\xa5""\xe6""\x9c""\xac""\xc2""\xbc""\xe8""\xaa""\x9e""i\xe6""\x97""\xa5""\xc2""\xa9""\xe6""\x97""\xa5""a\xe6""\x9c""\xac""b\xe8""\xaa""\x9e""\xc3""\xa7""\xe6""\x97""\xa5""\xc3""\xb0""\xe6""\x9c""\xac""\xc3""\x8a""\xe8""\xaa""\x9e""\xc3""\xbe""\xe6""\x97""\xa5""\xc2""\xa5""\xe6""\x9c""\xac""\xc2""\xbc""\xe8""\xaa""\x9e""i\xe6""\x97""\xa5""\xc2""\xa9""\xe6""\x97""\xa5""a\xe6""\x9c""\xac""b\xe8""\xaa""\x9e""\xc3""\xa7""\xe6""\x97""\xa5""\xc3""\xb0""\xe6""\x9c""\xac""\xc3""\x8a""\xe8""\xaa""\x9e""\xc3""\xbe""\xe6""\x97""\xa5""\xc2""\xa5""\xe6""\x9c""\xac""\xc2""\xbc""\xe8""\xaa""\x9e""i\xe6""\x97""\xa5""\xc2""\xa9""", "\x80""\x80""\x80""\x80""");

void TestFullRune(::gostd::Ptr<::gostd::testing::T> t) {
for (auto [_, m] : utf8map) {
auto b=::gostd::Slice<::gostd::Byte>(m.str);
if (!::gostd::unicode::utf8::FullRune(b)) {
t->Errorf("FullRune(%q) (%U) = false, want true", b, m.r);
};
auto s=m.str;
if (!::gostd::unicode::utf8::FullRuneInString(s)) {
t->Errorf("FullRuneInString(%q) (%U) = false, want true", s, m.r);
};
auto b1=b.Head((::gostd::Len(b)-1)).Tail(0);
if (::gostd::unicode::utf8::FullRune(b1)) {
t->Errorf("FullRune(%q) = true, want false", b1);
};
auto s1=::gostd::String(b1);
if (::gostd::unicode::utf8::FullRuneInString(s1)) {
t->Errorf("FullRune(%q) = true, want false", s1);
};
};
for (auto [_, s] : ::gostd::Slice<::gostd::String>("\xc0""", "\xc1""")) {
auto b=::gostd::Slice<::gostd::Byte>(s);
if (!::gostd::unicode::utf8::FullRune(b)) {
t->Errorf("FullRune(%q) = false, want true", s);
};
if (!::gostd::unicode::utf8::FullRuneInString(s)) {
t->Errorf("FullRuneInString(%q) = false, want true", s);
};
};
}

void TestEncodeRune(::gostd::Ptr<::gostd::testing::T> t) {
for (auto [_, m] : utf8map) {
auto b=::gostd::Slice<::gostd::Byte>(m.str);
::gostd::Array<::gostd::Byte, 10> buf;
;
auto n=::gostd::unicode::utf8::EncodeRune(buf.Tail(0), m.r);
auto b1=buf.Head(n).Tail(0);
if (!::gostd::bytes::Equal(b, b1)) {
t->Errorf("EncodeRune(%#04x) = %q want %q", m.r, b1, b);
};
};
}

void TestDecodeRune(::gostd::Ptr<::gostd::testing::T> t) {
for (auto [_, m] : utf8map) {
auto b=::gostd::Slice<::gostd::Byte>(m.str);
auto [r, size] = ::gostd::unicode::utf8::DecodeRune(b);
if (((r!=m.r)||(size!=::gostd::Len(b)))) {
t->Errorf("DecodeRune(%q) = %#04x, %d want %#04x, %d", b, r, size, m.r, ::gostd::Len(b));
};
auto s=m.str;
auto [_binding6487, _binding6490] = ::gostd::unicode::utf8::DecodeRuneInString(s); r = _binding6487; size = _binding6490;
if (((r!=m.r)||(size!=::gostd::Len(b)))) {
t->Errorf("DecodeRuneInString(%q) = %#04x, %d want %#04x, %d", s, r, size, m.r, ::gostd::Len(b));
};
auto [_binding6732, _binding6735] = ::gostd::unicode::utf8::DecodeRune(b.Head(::gostd::Cap(b)).Tail(0)); r = _binding6732; size = _binding6735;
if (((r!=m.r)||(size!=::gostd::Len(b)))) {
t->Errorf("DecodeRune(%q) = %#04x, %d want %#04x, %d", b, r, size, m.r, ::gostd::Len(b));
};
s=(m.str+"\x00""");
auto [_binding6909, _binding6912] = ::gostd::unicode::utf8::DecodeRuneInString(s); r = _binding6909; size = _binding6912;
if (((r!=m.r)||(size!=::gostd::Len(b)))) {
t->Errorf("DecodeRuneInString(%q) = %#04x, %d want %#04x, %d", s, r, size, m.r, ::gostd::Len(b));
};
::gostd::Int wantsize=1;
if ((wantsize>=::gostd::Len(b))) {
wantsize=0;
};
auto [_binding7168, _binding7171] = ::gostd::unicode::utf8::DecodeRune(b.Head((::gostd::Len(b)-1)).Tail(0)); r = _binding7168; size = _binding7171;
if (((r!=::gostd::unicode::utf8::RuneError)||(size!=wantsize))) {
t->Errorf("DecodeRune(%q) = %#04x, %d want %#04x, %d", b.Head((::gostd::Len(b)-1)).Tail(0), r, size, ::gostd::unicode::utf8::RuneError, wantsize);
};
s=m.str.Head((::gostd::Len(m.str)-1)).Tail(0);
auto [_binding7386, _binding7389] = ::gostd::unicode::utf8::DecodeRuneInString(s); r = _binding7386; size = _binding7389;
if (((r!=::gostd::unicode::utf8::RuneError)||(size!=wantsize))) {
t->Errorf("DecodeRuneInString(%q) = %#04x, %d want %#04x, %d", s, r, size, ::gostd::unicode::utf8::RuneError, wantsize);
};
if ((::gostd::Len(b)==1)) {
b[0]=128;
} else {
b[(::gostd::Len(b)-1)]=127;
};
auto [_binding7670, _binding7673] = ::gostd::unicode::utf8::DecodeRune(b); r = _binding7670; size = _binding7673;
if (((r!=::gostd::unicode::utf8::RuneError)||(size!=1))) {
t->Errorf("DecodeRune(%q) = %#04x, %d want %#04x, %d", b, r, size, ::gostd::unicode::utf8::RuneError, 1);
};
s=::gostd::String(b);
auto [_binding7834, _binding7837] = ::gostd::unicode::utf8::DecodeRuneInString(s); r = _binding7834; size = _binding7837;
if (((r!=::gostd::unicode::utf8::RuneError)||(size!=1))) {
t->Errorf("DecodeRuneInString(%q) = %#04x, %d want %#04x, %d", s, r, size, ::gostd::unicode::utf8::RuneError, 1);
};
};
}

void TestDecodeSurrogateRune(::gostd::Ptr<::gostd::testing::T> t) {
for (auto [_, m] : surrogateMap) {
auto b=::gostd::Slice<::gostd::Byte>(m.str);
auto [r, size] = ::gostd::unicode::utf8::DecodeRune(b);
if (((r!=::gostd::unicode::utf8::RuneError)||(size!=1))) {
t->Errorf("DecodeRune(%q) = %x, %d want %x, %d", b, r, size, ::gostd::unicode::utf8::RuneError, 1);
};
auto s=m.str;
auto [_binding8261, _binding8264] = ::gostd::unicode::utf8::DecodeRuneInString(s); r = _binding8261; size = _binding8264;
if (((r!=::gostd::unicode::utf8::RuneError)||(size!=1))) {
t->Errorf("DecodeRuneInString(%q) = %x, %d want %x, %d", b, r, size, ::gostd::unicode::utf8::RuneError, 1);
};
};
}

void TestSequencing(::gostd::Ptr<::gostd::testing::T> t) {
for (auto [_, ts] : testStrings) {
for (auto [_, m] : utf8map) {
for (auto [_, s] : ::gostd::Slice<::gostd::String>((ts+m.str), (m.str+ts), ((ts+m.str)+ts))) {
testSequence(t, s);
};
};
};
}

void TestIntConversion(::gostd::Ptr<::gostd::testing::T> t) {
for (auto [_, ts] : testStrings) {
auto runes=::gostd::Slice<::gostd::Rune>(ts);
if ((::gostd::unicode::utf8::RuneCountInString(ts)!=::gostd::Len(runes))) {
t->Errorf("%q: expected %d runes; got %d", ts, ::gostd::Len(runes), ::gostd::unicode::utf8::RuneCountInString(ts));
break;
};
::gostd::Int i=0;
for (auto [_, r] : ts) {
if ((r!=runes[i])) {
t->Errorf("%q[%d]: expected %c (%U); got %c (%U)", ts, i, runes[i], runes[i], r, r);
};
i++;
};
};
}

::gostd::Slice<::gostd::String> invalidSequenceTests = ::gostd::Slice<::gostd::String>("\xed""\xa0""\x80""\x80""", "\xed""\xbf""\xbf""\x80""", "\x91""\x80""\x80""\x80""", "\xc2""\x7f""\x80""\x80""", "\xc2""\xc0""\x80""\x80""", "\xdf""\x7f""\x80""\x80""", "\xdf""\xc0""\x80""\x80""", "\xe0""\x9f""\xbf""\x80""", "\xe0""\xa0""\x7f""\x80""", "\xe0""\xbf""\xc0""\x80""", "\xe0""\xc0""\x80""\x80""", "\xe1""\x7f""\xbf""\x80""", "\xe1""\x80""\x7f""\x80""", "\xe1""\xbf""\xc0""\x80""", "\xe1""\xc0""\x80""\x80""", "\xed""\x7f""\xbf""\x80""", "\xed""\x80""\x7f""\x80""", "\xed""\x9f""\xc0""\x80""", "\xed""\xa0""\x80""\x80""", "\xf0""\x8f""\xbf""\xbf""", "\xf0""\x90""\x7f""\xbf""", "\xf0""\x90""\x80""\x7f""", "\xf0""\xbf""\xbf""\xc0""", "\xf0""\xbf""\xc0""\x80""", "\xf0""\xc0""\x80""\x80""", "\xf1""\x7f""\xbf""\xbf""", "\xf1""\x80""\x7f""\xbf""", "\xf1""\x80""\x80""\x7f""", "\xf1""\xbf""\xbf""\xc0""", "\xf1""\xbf""\xc0""\x80""", "\xf1""\xc0""\x80""\x80""", "\xf4""\x7f""\xbf""\xbf""", "\xf4""\x80""\x7f""\xbf""", "\xf4""\x80""\x80""\x7f""", "\xf4""\x8f""\xbf""\xc0""", "\xf4""\x8f""\xc0""\x80""", "\xf4""\x90""\x80""\x80""");

::gostd::Rune runtimeDecodeRune(::gostd::String s) {
for (auto [_, r] : s) {
return r;
};
return -1;
}

void TestDecodeInvalidSequence(::gostd::Ptr<::gostd::testing::T> t) {
for (auto [_, s] : invalidSequenceTests) {
auto [r1, _10391] = ::gostd::unicode::utf8::DecodeRune(::gostd::Slice<::gostd::Byte>(s));
if (::gostd::Int want=::gostd::unicode::utf8::RuneError; (r1!=want)) {
t->Errorf("DecodeRune(%#x) = %#04x, want %#04x", s, r1, want);
return;
};
auto [r2, _10539] = ::gostd::unicode::utf8::DecodeRuneInString(s);
if (::gostd::Int want=::gostd::unicode::utf8::RuneError; (r2!=want)) {
t->Errorf("DecodeRuneInString(%q) = %#04x, want %#04x", s, r2, want);
return;
};
if ((r1!=r2)) {
t->Errorf("DecodeRune(%#x) = %#04x mismatch with DecodeRuneInString(%q) = %#04x", s, r1, s, r2);
return;
};
auto r3=runtimeDecodeRune(s);
if ((r2!=r3)) {
t->Errorf("DecodeRuneInString(%q) = %#04x mismatch with runtime.decoderune(%q) = %#04x", s, r2, s, r3);
return;
};
};
}

void testSequence(::gostd::Ptr<::gostd::testing::T> t, ::gostd::String s) {
struct info {
::gostd::Int index;
::gostd::Rune r;
};
;
auto index=::gostd::Make<::gostd::Slice<info>>(::gostd::Len(s));
auto b=::gostd::Slice<::gostd::Byte>(s);
::gostd::Int si=0;
::gostd::Int j=0;
for (auto [i, r] : s) {
if ((si!=i)) {
t->Errorf("Sequence(%q) mismatched index %d, want %d", s, si, i);
return;
};
index[j]=info{i, r};
j++;
auto [r1, size1] = ::gostd::unicode::utf8::DecodeRune(b.Tail(i));
if ((r!=r1)) {
t->Errorf("DecodeRune(%q) = %#04x, want %#04x", s.Tail(i), r1, r);
return;
};
auto [r2, size2] = ::gostd::unicode::utf8::DecodeRuneInString(s.Tail(i));
if ((r!=r2)) {
t->Errorf("DecodeRuneInString(%q) = %#04x, want %#04x", s.Tail(i), r2, r);
return;
};
if ((size1!=size2)) {
t->Errorf("DecodeRune/DecodeRuneInString(%q) size mismatch %d/%d", s.Tail(i), size1, size2);
return;
};
si+=size1;
};
j--;
for (si=::gostd::Len(s);(si>0);){
auto [r1, size1] = ::gostd::unicode::utf8::DecodeLastRune(b.Head(si).Tail(0));
auto [r2, size2] = ::gostd::unicode::utf8::DecodeLastRuneInString(s.Head(si).Tail(0));
if ((size1!=size2)) {
t->Errorf("DecodeLastRune/DecodeLastRuneInString(%q, %d) size mismatch %d/%d", s, si, size1, size2);
return;
};
if ((r1!=index[j].r)) {
t->Errorf("DecodeLastRune(%q, %d) = %#04x, want %#04x", s, si, r1, index[j].r);
return;
};
if ((r2!=index[j].r)) {
t->Errorf("DecodeLastRuneInString(%q, %d) = %#04x, want %#04x", s, si, r2, index[j].r);
return;
};
si-=size1;
if ((si!=index[j].index)) {
t->Errorf("DecodeLastRune(%q) index mismatch at %d, want %d", s, si, index[j].index);
return;
};
j--;
};
if ((si!=0)) {
t->Errorf("DecodeLastRune(%q) finished at %d, not 0", s, si);
};
}

void TestNegativeRune(::gostd::Ptr<::gostd::testing::T> t) {
auto errorbuf=::gostd::Make<::gostd::Slice<::gostd::Byte>>(::gostd::unicode::utf8::UTFMax);
errorbuf=errorbuf.Head(::gostd::unicode::utf8::EncodeRune(errorbuf, ::gostd::unicode::utf8::RuneError)).Tail(0);
auto buf=::gostd::Make<::gostd::Slice<::gostd::Byte>>(::gostd::unicode::utf8::UTFMax);
buf=buf.Head(::gostd::unicode::utf8::EncodeRune(buf, -1)).Tail(0);
if (!::gostd::bytes::Equal(buf, errorbuf)) {
t->Errorf("incorrect encoding [% x] for -1; expected [% x]", buf, errorbuf);
};
}

::gostd::Slice<RuneCountTest> runecounttests = ::gostd::Slice<RuneCountTest>(RuneCountTest{"abcd", 4}, RuneCountTest{"\xe2""\x98""\xba""\xe2""\x98""\xbb""\xe2""\x98""\xb9""", 3}, RuneCountTest{"1,2,3,4", 7}, RuneCountTest{"\xe2""\x00""", 2}, RuneCountTest{"\xe2""\x80""", 2}, RuneCountTest{"a\xe2""\x80""", 3});

void TestRuneCount(::gostd::Ptr<::gostd::testing::T> t) {
for (auto [_, tt] : runecounttests) {
if (auto out=::gostd::unicode::utf8::RuneCountInString(tt.in); (out!=tt.out)) {
t->Errorf("RuneCountInString(%q) = %d, want %d", tt.in, out, tt.out);
};
if (auto out=::gostd::unicode::utf8::RuneCount(::gostd::Slice<::gostd::Byte>(tt.in)); (out!=tt.out)) {
t->Errorf("RuneCount(%q) = %d, want %d", tt.in, out, tt.out);
};
};
}

::gostd::Slice<RuneLenTest> runelentests = ::gostd::Slice<RuneLenTest>(RuneLenTest{0, 1}, RuneLenTest{101, 1}, RuneLenTest{233, 2}, RuneLenTest{9786, 3}, RuneLenTest{::gostd::unicode::utf8::RuneError, 3}, RuneLenTest{::gostd::unicode::utf8::MaxRune, 4}, RuneLenTest{55296, -1}, RuneLenTest{57343, -1}, RuneLenTest{(::gostd::unicode::utf8::MaxRune+1), -1}, RuneLenTest{-1, -1});

void TestRuneLen(::gostd::Ptr<::gostd::testing::T> t) {
for (auto [_, tt] : runelentests) {
if (auto size=::gostd::unicode::utf8::RuneLen(tt.r); (size!=tt.size)) {
t->Errorf("RuneLen(%#U) = %d, want %d", tt.r, size, tt.size);
};
};
}

::gostd::Slice<ValidTest> validTests = ::gostd::Slice<ValidTest>(ValidTest{"", true}, ValidTest{"a", true}, ValidTest{"abc", true}, ValidTest{"\xd0""\x96""", true}, ValidTest{"\xd0""\x96""\xd0""\x96""", true}, ValidTest{"\xd0""\xb1""\xd1""\x80""\xd1""\x8d""\xd0""\xb4""-\xd0""\x9b""\xd0""\x93""\xd0""\xa2""\xd0""\x9c""", true}, ValidTest{"\xe2""\x98""\xba""\xe2""\x98""\xbb""\xe2""\x98""\xb9""", true}, ValidTest{"aa\xe2""", false}, ValidTest{::gostd::String(::gostd::Slice<::gostd::Byte>(66, 250)), false}, ValidTest{::gostd::String(::gostd::Slice<::gostd::Byte>(66, 250, 67)), false}, ValidTest{"a\xef""\xbf""\xbd""b", true}, ValidTest{::gostd::String("\xf4""\x8f""\xbf""\xbf"""), true}, ValidTest{::gostd::String("\xf4""\x90""\x80""\x80"""), false}, ValidTest{::gostd::String("\xf7""\xbf""\xbf""\xbf"""), false}, ValidTest{::gostd::String("\xfb""\xbf""\xbf""\xbf""\xbf"""), false}, ValidTest{::gostd::String("\xc0""\x80"""), false}, ValidTest{::gostd::String("\xed""\xa0""\x80"""), false}, ValidTest{::gostd::String("\xed""\xbf""\xbf"""), false});

void TestValid(::gostd::Ptr<::gostd::testing::T> t) {
for (auto [_, tt] : validTests) {
if ((::gostd::unicode::utf8::Valid(::gostd::Slice<::gostd::Byte>(tt.in))!=tt.out)) {
t->Errorf("Valid(%q) = %v; want %v", tt.in, !tt.out, tt.out);
};
if ((::gostd::unicode::utf8::ValidString(tt.in)!=tt.out)) {
t->Errorf("ValidString(%q) = %v; want %v", tt.in, !tt.out, tt.out);
};
};
}

::gostd::Slice<ValidRuneTest> validrunetests = ::gostd::Slice<ValidRuneTest>(ValidRuneTest{0, true}, ValidRuneTest{101, true}, ValidRuneTest{233, true}, ValidRuneTest{9786, true}, ValidRuneTest{::gostd::unicode::utf8::RuneError, true}, ValidRuneTest{::gostd::unicode::utf8::MaxRune, true}, ValidRuneTest{55295, true}, ValidRuneTest{55296, false}, ValidRuneTest{57343, false}, ValidRuneTest{57344, true}, ValidRuneTest{(::gostd::unicode::utf8::MaxRune+1), false}, ValidRuneTest{-1, false});

void TestValidRune(::gostd::Ptr<::gostd::testing::T> t) {
for (auto [_, tt] : validrunetests) {
if (auto ok=::gostd::unicode::utf8::ValidRune(tt.r); (ok!=tt.ok)) {
t->Errorf("ValidRune(%#U) = %t, want %t", tt.r, ok, tt.ok);
};
};
}

void BenchmarkRuneCountTenASCIIChars(::gostd::Ptr<::gostd::testing::B> b) {
auto s=::gostd::Slice<::gostd::Byte>("0123456789");
for (::gostd::Int i=0;(i<b->N);i++){
::gostd::unicode::utf8::RuneCount(s);
};
}

void BenchmarkRuneCountTenJapaneseChars(::gostd::Ptr<::gostd::testing::B> b) {
auto s=::gostd::Slice<::gostd::Byte>("\xe6""\x97""\xa5""\xe6""\x9c""\xac""\xe8""\xaa""\x9e""\xe6""\x97""\xa5""\xe6""\x9c""\xac""\xe8""\xaa""\x9e""\xe6""\x97""\xa5""\xe6""\x9c""\xac""\xe8""\xaa""\x9e""\xe6""\x97""\xa5""");
for (::gostd::Int i=0;(i<b->N);i++){
::gostd::unicode::utf8::RuneCount(s);
};
}

void BenchmarkRuneCountInStringTenASCIIChars(::gostd::Ptr<::gostd::testing::B> b) {
for (::gostd::Int i=0;(i<b->N);i++){
::gostd::unicode::utf8::RuneCountInString("0123456789");
};
}

void BenchmarkRuneCountInStringTenJapaneseChars(::gostd::Ptr<::gostd::testing::B> b) {
for (::gostd::Int i=0;(i<b->N);i++){
::gostd::unicode::utf8::RuneCountInString("\xe6""\x97""\xa5""\xe6""\x9c""\xac""\xe8""\xaa""\x9e""\xe6""\x97""\xa5""\xe6""\x9c""\xac""\xe8""\xaa""\x9e""\xe6""\x97""\xa5""\xe6""\x9c""\xac""\xe8""\xaa""\x9e""\xe6""\x97""\xa5""");
};
}

void BenchmarkValidTenASCIIChars(::gostd::Ptr<::gostd::testing::B> b) {
auto s=::gostd::Slice<::gostd::Byte>("0123456789");
for (::gostd::Int i=0;(i<b->N);i++){
::gostd::unicode::utf8::Valid(s);
};
}

void BenchmarkValidTenJapaneseChars(::gostd::Ptr<::gostd::testing::B> b) {
auto s=::gostd::Slice<::gostd::Byte>("\xe6""\x97""\xa5""\xe6""\x9c""\xac""\xe8""\xaa""\x9e""\xe6""\x97""\xa5""\xe6""\x9c""\xac""\xe8""\xaa""\x9e""\xe6""\x97""\xa5""\xe6""\x9c""\xac""\xe8""\xaa""\x9e""\xe6""\x97""\xa5""");
for (::gostd::Int i=0;(i<b->N);i++){
::gostd::unicode::utf8::Valid(s);
};
}

void BenchmarkValidStringTenASCIIChars(::gostd::Ptr<::gostd::testing::B> b) {
for (::gostd::Int i=0;(i<b->N);i++){
::gostd::unicode::utf8::ValidString("0123456789");
};
}

void BenchmarkValidStringTenJapaneseChars(::gostd::Ptr<::gostd::testing::B> b) {
for (::gostd::Int i=0;(i<b->N);i++){
::gostd::unicode::utf8::ValidString("\xe6""\x97""\xa5""\xe6""\x9c""\xac""\xe8""\xaa""\x9e""\xe6""\x97""\xa5""\xe6""\x9c""\xac""\xe8""\xaa""\x9e""\xe6""\x97""\xa5""\xe6""\x9c""\xac""\xe8""\xaa""\x9e""\xe6""\x97""\xa5""");
};
}

void BenchmarkEncodeASCIIRune(::gostd::Ptr<::gostd::testing::B> b) {
auto buf=::gostd::Make<::gostd::Slice<::gostd::Byte>>(::gostd::unicode::utf8::UTFMax);
for (::gostd::Int i=0;(i<b->N);i++){
::gostd::unicode::utf8::EncodeRune(buf, 97);
};
}

void BenchmarkEncodeJapaneseRune(::gostd::Ptr<::gostd::testing::B> b) {
auto buf=::gostd::Make<::gostd::Slice<::gostd::Byte>>(::gostd::unicode::utf8::UTFMax);
for (::gostd::Int i=0;(i<b->N);i++){
::gostd::unicode::utf8::EncodeRune(buf, 26412);
};
}

void BenchmarkDecodeASCIIRune(::gostd::Ptr<::gostd::testing::B> b) {
auto a=::gostd::Slice<::gostd::Byte>(97);
for (::gostd::Int i=0;(i<b->N);i++){
::gostd::unicode::utf8::DecodeRune(a);
};
}

void BenchmarkDecodeJapaneseRune(::gostd::Ptr<::gostd::testing::B> b) {
auto nihon=::gostd::Slice<::gostd::Byte>("\xe6""\x9c""\xac""");
for (::gostd::Int i=0;(i<b->N);i++){
::gostd::unicode::utf8::DecodeRune(nihon);
};
}

void BenchmarkFullASCIIRune(::gostd::Ptr<::gostd::testing::B> b) {
auto a=::gostd::Slice<::gostd::Byte>(97);
for (::gostd::Int i=0;(i<b->N);i++){
::gostd::unicode::utf8::FullRune(a);
};
}

void BenchmarkFullJapaneseRune(::gostd::Ptr<::gostd::testing::B> b) {
auto nihon=::gostd::Slice<::gostd::Byte>("\xe6""\x9c""\xac""");
for (::gostd::Int i=0;(i<b->N);i++){
::gostd::unicode::utf8::FullRune(nihon);
};
}

} // namespace gostd::unicode::utf8_test

#pragma clang diagnostic pop
