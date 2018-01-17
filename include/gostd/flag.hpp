#pragma once

#include <gostd.hpp>
#include <gostd/errors.hpp>

namespace gostd::flag {

class FlagSet {
public:
    FlagSet(String name) : _name{name} {}

    Error Parse(Slice<String> arguments) {
        return errors::New("not yet implemented");
    }

private:
    String _name;
};

} // namespace gostd::flag
