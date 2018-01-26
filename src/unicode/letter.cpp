// THIS FILE WAS GENERATED VIA TRANSPILING. DO NOT MODIFY.
#include <gostd/unicode.hpp>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wparentheses-equality"

namespace gostd::unicode {

::gostd::Bool is16(::gostd::Slice<Range16> ranges, ::gostd::Uint16 r) {
if (((::gostd::Len(ranges)<=linearMax)||(r<=MaxLatin1))) {
for (auto [i, _242267] : ranges) {
auto range_=&ranges[i];
if ((r<range_->Lo)) {
return false;
};
if ((r<=range_->Hi)) {
return ((((r-range_->Lo))%range_->Stride)==0);
};
};
return false;
};
::gostd::Int lo=0;
auto hi=::gostd::Len(ranges);
for (;(lo<hi);){
auto m=(lo+(((hi-lo))/2));
auto range_=&ranges[m];
if (((range_->Lo<=r)&&(r<=range_->Hi))) {
return ((((r-range_->Lo))%range_->Stride)==0);
};
if ((r<range_->Lo)) {
hi=m;
} else {
lo=(m+1);
};
};
return false;
}

::gostd::Bool is32(::gostd::Slice<Range32> ranges, ::gostd::Uint32 r) {
if ((::gostd::Len(ranges)<=linearMax)) {
for (auto [i, _242884] : ranges) {
auto range_=&ranges[i];
if ((r<range_->Lo)) {
return false;
};
if ((r<=range_->Hi)) {
return ((((r-range_->Lo))%range_->Stride)==0);
};
};
return false;
};
::gostd::Int lo=0;
auto hi=::gostd::Len(ranges);
for (;(lo<hi);){
auto m=(lo+(((hi-lo))/2));
auto range_=ranges[m];
if (((range_.Lo<=r)&&(r<=range_.Hi))) {
return ((((r-range_.Lo))%range_.Stride)==0);
};
if ((r<range_.Lo)) {
hi=m;
} else {
lo=(m+1);
};
};
return false;
}

::gostd::Bool Is(::gostd::Ptr<RangeTable> rangeTab, ::gostd::Rune r) {
auto r16=rangeTab->R16;
if (((::gostd::Len(r16)>0)&&(r<=::gostd::Rune(r16[(::gostd::Len(r16)-1)].Hi)))) {
return is16(r16, ::gostd::Uint16(r));
};
auto r32=rangeTab->R32;
if (((::gostd::Len(r32)>0)&&(r>=::gostd::Rune(r32[0].Lo)))) {
return is32(r32, ::gostd::Uint32(r));
};
return false;
}

::gostd::Bool isExcludingLatin(::gostd::Ptr<RangeTable> rangeTab, ::gostd::Rune r) {
auto r16=rangeTab->R16;
if (auto off=rangeTab->LatinOffset; ((::gostd::Len(r16)>off)&&(r<=::gostd::Rune(r16[(::gostd::Len(r16)-1)].Hi)))) {
return is16(r16.Tail(off), ::gostd::Uint16(r));
};
auto r32=rangeTab->R32;
if (((::gostd::Len(r32)>0)&&(r>=::gostd::Rune(r32[0].Lo)))) {
return is32(r32, ::gostd::Uint32(r));
};
return false;
}

::gostd::Bool IsUpper(::gostd::Rune r) {
if ((::gostd::Uint32(r)<=MaxLatin1)) {
return ((properties[::gostd::Uint8(r)]&pLmask)==pLu);
};
return isExcludingLatin(Upper, r);
}

::gostd::Bool IsLower(::gostd::Rune r) {
if ((::gostd::Uint32(r)<=MaxLatin1)) {
return ((properties[::gostd::Uint8(r)]&pLmask)==pLl);
};
return isExcludingLatin(Lower, r);
}

::gostd::Bool IsTitle(::gostd::Rune r) {
if ((r<=MaxLatin1)) {
return false;
};
return isExcludingLatin(Title, r);
}

::gostd::Rune to(::gostd::Int _case, ::gostd::Rune r, ::gostd::Slice<CaseRange> caseRange) {
if (((_case<0)||(MaxCase<=_case))) {
return ReplacementChar;
};
::gostd::Int lo=0;
auto hi=::gostd::Len(caseRange);
for (;(lo<hi);){
auto m=(lo+(((hi-lo))/2));
auto cr=caseRange[m];
if (((::gostd::Rune(cr.Lo)<=r)&&(r<=::gostd::Rune(cr.Hi)))) {
auto delta=cr.Delta[_case];
if ((delta>MaxRune)) {
return (::gostd::Rune(cr.Lo)+(((((r-::gostd::Rune(cr.Lo)))&~1)|::gostd::Rune((_case&1)))));
};
return (r+delta);
};
if ((r<::gostd::Rune(cr.Lo))) {
hi=m;
} else {
lo=(m+1);
};
};
return r;
}

::gostd::Rune To(::gostd::Int _case, ::gostd::Rune r) {
return to(_case, r, CaseRanges);
}

::gostd::Rune ToUpper(::gostd::Rune r) {
if ((r<=MaxASCII)) {
if (((97<=r)&&(r<=122))) {
r-=(97-65);
};
return r;
};
return To(UpperCase, r);
}

::gostd::Rune ToLower(::gostd::Rune r) {
if ((r<=MaxASCII)) {
if (((65<=r)&&(r<=90))) {
r+=(97-65);
};
return r;
};
return To(LowerCase, r);
}

::gostd::Rune ToTitle(::gostd::Rune r) {
if ((r<=MaxASCII)) {
if (((97<=r)&&(r<=122))) {
r-=(97-65);
};
return r;
};
return To(TitleCase, r);
}

::gostd::Rune SpecialCase::ToUpper(::gostd::Rune r) {
auto r1=to(UpperCase, r, ::gostd::Slice<CaseRange>((*this)));
if ((r1==r)) {
r1=ToUpper(r);
};
return r1;
}

::gostd::Rune SpecialCase::ToTitle(::gostd::Rune r) {
auto r1=to(TitleCase, r, ::gostd::Slice<CaseRange>((*this)));
if ((r1==r)) {
r1=ToTitle(r);
};
return r1;
}

::gostd::Rune SpecialCase::ToLower(::gostd::Rune r) {
auto r1=to(LowerCase, r, ::gostd::Slice<CaseRange>((*this)));
if ((r1==r)) {
r1=ToLower(r);
};
return r1;
}

::gostd::Rune SimpleFold(::gostd::Rune r) {
if (((r<0)||(r>MaxRune))) {
return r;
};
if ((::gostd::Int(r)<::gostd::Len(asciiFold))) {
return ::gostd::Rune(asciiFold[r]);
};
::gostd::Int lo=0;
auto hi=::gostd::Len(caseOrbit);
for (;(lo<hi);){
auto m=(lo+(((hi-lo))/2));
if ((::gostd::Rune(caseOrbit[m].From)<r)) {
lo=(m+1);
} else {
hi=m;
};
};
if (((lo<::gostd::Len(caseOrbit))&&(::gostd::Rune(caseOrbit[lo].From)==r))) {
return ::gostd::Rune(caseOrbit[lo].To);
};
if (auto l=ToLower(r); (l!=r)) {
return l;
};
return ToUpper(r);
}

} // namespace gostd::unicode

#pragma clang diagnostic pop
