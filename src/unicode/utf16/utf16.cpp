// THIS FILE WAS GENERATED VIA TRANSPILING. DO NOT MODIFY.
#include <gostd/unicode/utf16.hpp>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wparentheses-equality"

namespace gostd::unicode::utf16 {

::gostd::Bool IsSurrogate(::gostd::Rune r) {
return ((surr1<=r)&&(r<surr3));
}

::gostd::Rune DecodeRune(::gostd::Rune r1, ::gostd::Rune r2) {
if (((((surr1<=r1)&&(r1<surr2))&&(surr2<=r2))&&(r2<surr3))) {
return (((((r1-surr1))<<10)|((r2-surr2)))+surrSelf);
};
return replacementChar;
}

::gostd::Tuple<::gostd::Rune, ::gostd::Rune> EncodeRune(::gostd::Rune r) {
::gostd::Rune r1;
::gostd::Rune r2;
{
if (((r<surrSelf)||(r>maxRune))) {
return {replacementChar, replacementChar};
};
r-=surrSelf;
return {(surr1+(((r>>10))&1023)), (surr2+(r&1023))};
}}


::gostd::Slice<::gostd::Uint16> Encode(::gostd::Slice<::gostd::Rune> s) {
auto n=::gostd::Len(s);
for (auto [_, v] : s) {
if ((v>=surrSelf)) {
n++;
};
};
auto a=::gostd::Make<::gostd::Slice<::gostd::Uint16>>(n);
n=0;
for (auto [_, v] : s) {
{if ((((0<=v)&&(v<surr1))) || (((surr3<=v)&&(v<surrSelf)))) {
_case7485:
a[n]=::gostd::Uint16(v);
n++;
}
 else if ((((surrSelf<=v)&&(v<=maxRune)))) {
_case7586:
auto [r1, r2] = EncodeRune(v);
a[n]=::gostd::Uint16(r1);
a[(n+1)]=::gostd::Uint16(r2);
n+=2;
}
 else {
_case7736:a[n]=::gostd::Uint16(replacementChar);
n++;
}
};
};
return a.Head(n);
}

::gostd::Slice<::gostd::Rune> Decode(::gostd::Slice<::gostd::Uint16> s) {
auto a=::gostd::Make<::gostd::Slice<::gostd::Rune>>(::gostd::Len(s));
::gostd::Int n=0;
for (::gostd::Int i=0;(i<::gostd::Len(s));i++){
{if (auto r=s[i]; ((r<surr1)) || ((surr3<=r))) {
_case8024:
a[n]=::gostd::Rune(r);
}
 else if (((((((surr1<=r)&&(r<surr2))&&((i+1)<::gostd::Len(s)))&&(surr2<=s[(i+1)]))&&(s[(i+1)]<surr3)))) {
_case8090:
a[n]=DecodeRune(::gostd::Rune(r), ::gostd::Rune(s[(i+1)]));
i++;
}
 else {
_case8260:a[n]=replacementChar;
}
};
n++;
};
return a.Head(n);
}

} // namespace gostd::unicode::utf16

#pragma clang diagnostic pop
