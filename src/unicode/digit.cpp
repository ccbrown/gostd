// THIS FILE WAS GENERATED VIA TRANSPILING. DO NOT MODIFY.
#include <gostd/unicode.hpp>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wparentheses-equality"

namespace gostd::unicode {

::gostd::Bool IsDigit(::gostd::Rune r) {
if ((r<=MaxLatin1)) {
return ((48<=r)&&(r<=57));
};
return isExcludingLatin(Digit, r);
}

} // namespace gostd::unicode

#pragma clang diagnostic pop
