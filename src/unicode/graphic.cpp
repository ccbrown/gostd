// THIS FILE WAS GENERATED VIA TRANSPILING. DO NOT MODIFY.
#include <gostd/unicode.hpp>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wparentheses-equality"

namespace gostd::unicode {

::gostd::Slice<::gostd::Ptr<RangeTable>> GraphicRanges = ::gostd::Slice<::gostd::Ptr<RangeTable>>(L, M, N, P, S, Zs);

::gostd::Slice<::gostd::Ptr<RangeTable>> PrintRanges = ::gostd::Slice<::gostd::Ptr<RangeTable>>(L, M, N, P, S);

::gostd::Bool IsGraphic(::gostd::Rune r) {
if ((::gostd::Uint32(r)<=MaxLatin1)) {
return ((properties[::gostd::Uint8(r)]&pg)!=0);
};
return In(r, GraphicRanges);
}

::gostd::Bool IsPrint(::gostd::Rune r) {
if ((::gostd::Uint32(r)<=MaxLatin1)) {
return ((properties[::gostd::Uint8(r)]&pp)!=0);
};
return In(r, PrintRanges);
}

::gostd::Bool IsOneOf(::gostd::Slice<::gostd::Ptr<RangeTable>> ranges, ::gostd::Rune r) {
for (auto [_, inside] : ranges) {
if (Is(inside, r)) {
return true;
};
};
return false;
}

::gostd::Bool In(::gostd::Rune r, ::gostd::Slice<::gostd::Ptr<RangeTable>> ranges) {
for (auto [_, inside] : ranges) {
if (Is(inside, r)) {
return true;
};
};
return false;
}

::gostd::Bool IsControl(::gostd::Rune r) {
if ((::gostd::Uint32(r)<=MaxLatin1)) {
return ((properties[::gostd::Uint8(r)]&pC)!=0);
};
return false;
}

::gostd::Bool IsLetter(::gostd::Rune r) {
if ((::gostd::Uint32(r)<=MaxLatin1)) {
return ((properties[::gostd::Uint8(r)]&(pLmask))!=0);
};
return isExcludingLatin(Letter, r);
}

::gostd::Bool IsMark(::gostd::Rune r) {
return isExcludingLatin(Mark, r);
}

::gostd::Bool IsNumber(::gostd::Rune r) {
if ((::gostd::Uint32(r)<=MaxLatin1)) {
return ((properties[::gostd::Uint8(r)]&pN)!=0);
};
return isExcludingLatin(Number, r);
}

::gostd::Bool IsPunct(::gostd::Rune r) {
if ((::gostd::Uint32(r)<=MaxLatin1)) {
return ((properties[::gostd::Uint8(r)]&pP)!=0);
};
return Is(Punct, r);
}

::gostd::Bool IsSpace(::gostd::Rune r) {
if ((::gostd::Uint32(r)<=MaxLatin1)) {
{if ((r == 9) || (r == 10) || (r == 11) || (r == 12) || (r == 13) || (r == 32) || (r == 133) || (r == 160)) {
_case254442:
return true;
}
};
return false;
};
return isExcludingLatin(White_Space, r);
}

::gostd::Bool IsSymbol(::gostd::Rune r) {
if ((::gostd::Uint32(r)<=MaxLatin1)) {
return ((properties[::gostd::Uint8(r)]&pS)!=0);
};
return isExcludingLatin(Symbol, r);
}

} // namespace gostd::unicode

#pragma clang diagnostic pop
