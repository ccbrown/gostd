#include <cx/sys/unix/errno.hpp>

#include <cx/sys/unix/zerrors_darwin_amd64.hpp>

namespace cx::sys::unix {

String Errno::Error() const {
    auto errno = Int(_errno);
    if (errno > 0 && errno <= sizeof(errors) / sizeof(*errors)) {
        return errors[errno];
    }
    return "errno " + itoa(errno);
}


} // namespace cx::sys::unix
