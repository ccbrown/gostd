#include <gostd/os.hpp>

#include <gostd/errors.hpp>

namespace gostd::os {

Error ErrExist = errors::New("file already exists");
Error ErrNotExist = errors::New("file does not exist");

Ptr<File> Stdin = New<File>(sys::unix::Stdin, "/dev/stdin");
Ptr<File> Stdout = New<File>(sys::unix::Stdout, "/dev/stdout");
Ptr<File> Stderr = New<File>(sys::unix::Stderr, "/dev/stderr");


} // namespace gostd::os
