// THIS FILE WAS GENERATED VIA TRANSPILING. DO NOT MODIFY.
#include <gostd/unicode/utf8_test.hpp>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wparentheses-equality"

namespace gostd::unicode::utf8_test {

void ExampleDecodeLastRune() {
auto b=::gostd::Slice<::gostd::Byte>("Hello, \xe4""\xb8""\x96""\xe7""\x95""\x8c""");
for (;(::gostd::Len(b)>0);){
auto [r, size] = ::gostd::unicode::utf8::DecodeLastRune(b);
::gostd::fmt::Printf("%c %v\x0a""", r, size);
b=b.Head((::gostd::Len(b)-size));
};
}

void ExampleDecodeLastRuneInString() {
::gostd::String str="Hello, \xe4""\xb8""\x96""\xe7""\x95""\x8c""";
for (;(::gostd::Len(str)>0);){
auto [r, size] = ::gostd::unicode::utf8::DecodeLastRuneInString(str);
::gostd::fmt::Printf("%c %v\x0a""", r, size);
str=str.Head((::gostd::Len(str)-size));
};
}

void ExampleDecodeRune() {
auto b=::gostd::Slice<::gostd::Byte>("Hello, \xe4""\xb8""\x96""\xe7""\x95""\x8c""");
for (;(::gostd::Len(b)>0);){
auto [r, size] = ::gostd::unicode::utf8::DecodeRune(b);
::gostd::fmt::Printf("%c %v\x0a""", r, size);
b=b.Tail(size);
};
}

void ExampleDecodeRuneInString() {
::gostd::String str="Hello, \xe4""\xb8""\x96""\xe7""\x95""\x8c""";
for (;(::gostd::Len(str)>0);){
auto [r, size] = ::gostd::unicode::utf8::DecodeRuneInString(str);
::gostd::fmt::Printf("%c %v\x0a""", r, size);
str=str.Tail(size);
};
}

void ExampleEncodeRune() {
::gostd::Int r=19990;
auto buf=::gostd::Make<::gostd::Slice<::gostd::Byte>>(3);
auto n=::gostd::unicode::utf8::EncodeRune(buf, r);
::gostd::fmt::Println(buf);
::gostd::fmt::Println(n);
}

void ExampleFullRune() {
auto buf=::gostd::Slice<::gostd::Byte>(228, 184, 150);
::gostd::fmt::Println(::gostd::unicode::utf8::FullRune(buf));
::gostd::fmt::Println(::gostd::unicode::utf8::FullRune(buf.Head(2)));
}

void ExampleFullRuneInString() {
::gostd::String str="\xe4""\xb8""\x96""";
::gostd::fmt::Println(::gostd::unicode::utf8::FullRuneInString(str));
::gostd::fmt::Println(::gostd::unicode::utf8::FullRuneInString(str.Head(2)));
}

void ExampleRuneCount() {
auto buf=::gostd::Slice<::gostd::Byte>("Hello, \xe4""\xb8""\x96""\xe7""\x95""\x8c""");
::gostd::fmt::Println("bytes =", ::gostd::Len(buf));
::gostd::fmt::Println("runes =", ::gostd::unicode::utf8::RuneCount(buf));
}

void ExampleRuneCountInString() {
::gostd::String str="Hello, \xe4""\xb8""\x96""\xe7""\x95""\x8c""";
::gostd::fmt::Println("bytes =", ::gostd::Len(str));
::gostd::fmt::Println("runes =", ::gostd::unicode::utf8::RuneCountInString(str));
}

void ExampleRuneLen() {
::gostd::fmt::Println(::gostd::unicode::utf8::RuneLen(97));
::gostd::fmt::Println(::gostd::unicode::utf8::RuneLen(30028));
}

void ExampleRuneStart() {
auto buf=::gostd::Slice<::gostd::Byte>("a\xe7""\x95""\x8c""");
::gostd::fmt::Println(::gostd::unicode::utf8::RuneStart(buf[0]));
::gostd::fmt::Println(::gostd::unicode::utf8::RuneStart(buf[1]));
::gostd::fmt::Println(::gostd::unicode::utf8::RuneStart(buf[2]));
}

void ExampleValid() {
auto valid=::gostd::Slice<::gostd::Byte>("Hello, \xe4""\xb8""\x96""\xe7""\x95""\x8c""");
auto invalid=::gostd::Slice<::gostd::Byte>(255, 254, 253);
::gostd::fmt::Println(::gostd::unicode::utf8::Valid(valid));
::gostd::fmt::Println(::gostd::unicode::utf8::Valid(invalid));
}

void ExampleValidRune() {
::gostd::Int valid=97;
::gostd::Int invalid=::gostd::Rune(268435455);
::gostd::fmt::Println(::gostd::unicode::utf8::ValidRune(valid));
::gostd::fmt::Println(::gostd::unicode::utf8::ValidRune(invalid));
}

void ExampleValidString() {
::gostd::String valid="Hello, \xe4""\xb8""\x96""\xe7""\x95""\x8c""";
auto invalid=::gostd::String(::gostd::Slice<::gostd::Byte>(255, 254, 253));
::gostd::fmt::Println(::gostd::unicode::utf8::ValidString(valid));
::gostd::fmt::Println(::gostd::unicode::utf8::ValidString(invalid));
}

} // namespace gostd::unicode::utf8_test

#pragma clang diagnostic pop
