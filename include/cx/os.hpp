#pragma once

#include <cx/strings.hpp>
#include <cx/sys/unix.hpp>

namespace cx::os {

class File {
public:
    File(UIntPtr fd, String name) : _fd{fd}, _name{name} {}

    auto Write(Slice<Byte> b) const {
        return sys::unix::Write(_fd, b);
    }

private:
    const UIntPtr _fd;
    const String _name;
};

extern File Stdin, Stdout, Stderr;

} // namespace cx::os
