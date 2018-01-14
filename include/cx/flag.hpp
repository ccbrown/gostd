#pragma once

#include <cx.hpp>
#include <cx/errors.hpp>

namespace cx::flag {

class FlagSet {
public:
    FlagSet(String name) : _name{name} {}

    Error Parse(Slice<String> arguments) {
        return errors::New("not yet implemented");
    }

private:
    String _name;
};

} // namespace cx::flag
