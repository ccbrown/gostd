#include <cx/io.hpp>

namespace cx::io::ioutil {

struct devNull {
    Writer::WriteResult Write(Slice<Byte> p) const {
        return {p.Len(), {}};
    }
};

Writer Discard = New<devNull>();

} // namespace cx::io::ioutil
