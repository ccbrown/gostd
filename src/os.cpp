#include <cx/os.hpp>

namespace cx::os {

File Stdin{sys::unix::Stdin, "/dev/stdin"};
File Stdout{sys::unix::Stdout, "/dev/stdout"};
File Stderr{sys::unix::Stderr, "/dev/stderr"};


} // namespace cx::os
