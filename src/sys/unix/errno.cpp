#include <cx/sys/unix/errno.hpp>

#include <cx/sys/unix/zerrors_darwin_amd64.hpp>

namespace cx::sys::unix {

template <typename T>
String uitoa(T v) {
    char buf[33] = {0};
    auto i = sizeof(buf) - 2;
    while (v >= 10) {
        buf[i] = v%10 + '0';
        --i;
        v /= 10;
    }
    buf[i] = v + '0';
    return buf + i;
}

template <typename T>
String itoa(T v) {
    if (v < 0) {
        return "-" + uitoa(-v);
    }
    return uitoa(v);
}

String Errno::Error() const {
    auto errno = Int(_errno);
    if (errno > 0 && errno <= sizeof(errors) / sizeof(*errors)) {
        return errors[errno];
    }
    return "errno " + itoa(errno);
}


} // namespace cx::sys::unix
