#include <gostd/unicode/utf8.hpp>

namespace gostd {

String::iterator& String::iterator::operator++() {
    auto [r, size] = unicode::utf8::DecodeRuneInString(string->Tail(offset));
    offset += size;
    return *this;
}

Tuple<Int, Rune> String::iterator::operator*() const {
    auto [r, size] = unicode::utf8::DecodeRuneInString(string->Tail(offset));
    return {offset, r};
}

} // namespace gostd
