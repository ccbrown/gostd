#include <cx/errors.hpp>

namespace cx::io {

Error ErrShortBuffer = errors::New("short buffer");
Error ErrShortWrite = errors::New("short write");
Error EOF = errors::New("EOF");

} // namespace cx::io
