#include <cx/io.hpp>

namespace cx::io::ioutil {

Uint32 suffixN = 0;

struct devNull {
    Writer::WriteResult Write(Slice<Byte> p) const {
        return {p.Len(), {}};
    }
};

Writer Discard = New<devNull>();

} // namespace cx::io::ioutil
