#pragma once

namespace gostd {

// TODO
template <typename K, typename V>
class Map {
public:
    Map() {}

    template <typename... Rem>
    Map(K key, V value, Rem&&... rem) {}
};

} // namespace gostd
