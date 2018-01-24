#include <gostd/sys/unix/errno.hpp>

#include <gostd/sys/unix/zerrors_darwin_amd64.hpp>

namespace gostd::sys::unix {

String Errno::Error() const {
    auto errno = Int(_errno);
    if (errno > 0 && errno <= sizeof(errors) / sizeof(*errors)) {
        return errors[errno.value()];
    }
    return "errno " + itoa(errno);
}


} // namespace gostd::sys::unix
