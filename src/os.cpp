#include <cx/os.hpp>

namespace cx::os {

Ptr<File> Stdin = New<File>(sys::unix::Stdin, "/dev/stdin");
Ptr<File> Stdout = New<File>(sys::unix::Stdout, "/dev/stdout");
Ptr<File> Stderr = New<File>(sys::unix::Stderr, "/dev/stderr");


} // namespace cx::os
