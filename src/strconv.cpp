#include <cx/errors.hpp>

namespace cx::strconv {

Error ErrSyntax = errors::New("invalid syntax");
Error ErrRange = errors::New("value out of range");

} //namespace cx::strconv
