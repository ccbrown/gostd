#include <gostd/io.hpp>

namespace gostd::io::ioutil {

Uint32 suffixN = 0;

struct devNull {
    Writer::WriteResult Write(Slice<Byte> p) const {
        return {p.Len(), {}};
    }
};

Writer Discard = New<devNull>();

} // namespace gostd::io::ioutil
