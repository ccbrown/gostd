#include <gostd/errors.hpp>

namespace gostd::io {

Error ErrShortBuffer = errors::New("short buffer");
Error ErrShortWrite = errors::New("short write");
Error EOF = errors::New("EOF");

} // namespace gostd::io
