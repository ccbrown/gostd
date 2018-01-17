#include <gostd/errors.hpp>

namespace gostd::strconv {

Error ErrSyntax = errors::New("invalid syntax");
Error ErrRange = errors::New("value out of range");

} //namespace gostd::strconv
