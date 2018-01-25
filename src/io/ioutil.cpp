#include <gostd/io.hpp>

namespace gostd::io::ioutil {

Uint32 suffixN = 0;

struct devNull {
    Writer::WriteResult Write(Slice<Byte> p) const {
        return {Len(p), {}};
    }
};

Writer Discard = New<devNull>();

} // namespace gostd::io::ioutil
