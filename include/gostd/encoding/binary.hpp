#pragma once

#include <gostd.hpp>
#include <gostd/cpp.hpp>
#include <gostd/io.hpp>

namespace gostd::encoding::binary {

struct ByteOrder {
    constexpr ByteOrder() {}

    template <typename T>
    ByteOrder(T bo)
        : Uint16{[=](Slice<Byte> b) { return bo.Uint16(b); }}
        , Uint32{[=](Slice<Byte> b) { return bo.Uint32(b); }}
        , Uint64{[=](Slice<Byte> b) { return bo.Uint64(b); }}
    {}

    Func<Uint16(Slice<Byte>)> Uint16;
    Func<Uint32(Slice<Byte>)> Uint32;
    Func<Uint64(Slice<Byte>)> Uint64;
};

struct bigEndian {
    auto Uint16(Slice<Byte> b) const {
        return gostd::Uint16(b[1]) | (gostd::Uint16(b[0]) << 8);
    }

    auto Uint32(Slice<Byte> b) const {
        return gostd::Uint32(b[3]) | (gostd::Uint32(b[2]) << 8) | (gostd::Uint32(b[1]) << 16) | (gostd::Uint32(b[0]) << 24);
    }

    auto Uint64(Slice<Byte> b) const {
        return gostd::Uint64(b[7]) | (gostd::Uint64(b[6]) << 8) | (gostd::Uint64(b[5]) << 16) | (gostd::Uint64(b[4]) << 24 | (gostd::Uint64(b[3]) << 32 | (gostd::Uint64(b[2]) << 40 | (gostd::Uint64(b[1]) << 48)))) | (gostd::Uint64(b[0]) << 56);
    }
};

struct littleEndian {
    auto Uint16(Slice<Byte> b) const {
        return gostd::Uint16(b[0]) | (gostd::Uint16(b[1]) << 8);
    }

    auto Uint32(Slice<Byte> b) const {
        return gostd::Uint32(b[0]) | (gostd::Uint32(b[1]) << 8) | (gostd::Uint32(b[2]) << 16) | (gostd::Uint32(b[3]) << 24);
    }

    auto Uint64(Slice<Byte> b) const {
        return gostd::Uint64(b[0]) | (gostd::Uint64(b[1]) << 8) | (gostd::Uint64(b[2]) << 16) | (gostd::Uint64(b[3]) << 24 | (gostd::Uint64(b[4]) << 32 | (gostd::Uint64(b[5]) << 40 | (gostd::Uint64(b[6]) << 48)))) | (gostd::Uint64(b[7]) << 56);
    }
};

extern bigEndian BigEndian;
extern littleEndian LittleEndian;

template <typename T>
struct intType {
    static constexpr Int serializedSize() { return sizeof(T); }

    static void deserialize(Slice<Byte> buf, const ByteOrder& order, T* dest) {
        if (sizeof(T) == 1) {
            *dest = static_cast<T>(buf[0]);
        } else if (sizeof(T) == 2) {
            *dest = static_cast<T>(order.Uint16(buf));
        } else if (sizeof(T) == 4) {
            *dest = static_cast<T>(order.Uint32(buf));
        } else if (sizeof(T) == 8) {
            *dest = static_cast<T>(order.Uint64(buf));
        }
    }
};

struct boolType {
    static constexpr Int serializedSize() { return 1; }

    static void deserialize(Slice<Byte> buf, const ByteOrder& order, bool* dest) {
        *dest = buf[0] != 0;
    }
};

template <typename T> struct classType;
template <typename T> struct numericType;

template <typename T>
using dataType = typename cpp::conditional<IsNumericType<T>::value, numericType<T>,
                 typename cpp::conditional<cpp::is_class<T>::value, classType<T>,
                 typename cpp::conditional<cpp::is_enum<T>::value || cpp::is_integral<T>::value, intType<T>,
                 typename cpp::conditional<cpp::is_same<T, bool>::value, boolType,
                 void>::type>::type>::type>::type;

template <typename T>
struct classType {
    static constexpr Int intDataSizeForClassFields(cpp::integral_constant<cpp::size_t, 0> i) { return 0; }

    template <typename I>
    static constexpr Int intDataSizeForClassFields(I i) {
        return dataType<typename cpp::field<I::value - 1, T>::type>::serializedSize() + intDataSizeForClassFields(cpp::integral_constant<cpp::size_t, i - 1>{});
    }

    static constexpr Int serializedSize() {
        return intDataSizeForClassFields(cpp::integral_constant<cpp::size_t, cpp::field_count<T>()>{});
    }

    static void _deserializeFields(Slice<Byte> buf, const ByteOrder& order) {}

    template <typename Next, typename... Rem>
    static void _deserializeFields(Slice<Byte> buf, const ByteOrder& order, Next&& next, Rem&&... rem) {
        using dt = dataType<typename cpp::remove_reference<Next>::type>;
        dt::deserialize(buf, order, &next);
        _deserializeFields(buf.Tail(dt::serializedSize()), order, cpp::forward<Rem>(rem)...);
    }

    template <cpp::size_t... I>
    static void _deserialize(Slice<Byte> buf, const ByteOrder& order, T* dest, cpp::index_sequence<I...> i) {
        _deserializeFields(buf, order, cpp::get_field<I>(*dest)...);
    }

    static void deserialize(Slice<Byte> buf, const ByteOrder& order, T* dest) {
        _deserialize(buf, order, dest, cpp::make_index_sequence<cpp::field_count<T>()>{});
    }
};

template <typename T>
struct numericType {
    static constexpr Int serializedSize() { return dataType<typename T::ValueType>::serializedSize(); }

    static void deserialize(Slice<Byte> buf, const ByteOrder& order, T* dest) {
        typename T::ValueType n;
        dataType<typename T::ValueType>::deserialize(buf, order, &n);
        *dest = T(n);
    }
};

template <typename T>
Error Read(io::Reader r, ByteOrder order, T* data) {
    auto buf = Make<Slice<Byte>>(dataType<T>::serializedSize());
    if (auto [n, err] = io::ReadFull(r, buf); err) {
        return err;
    }
    dataType<T>::deserialize(buf, order, data);
    return {};
}

} // namespace gostd::encoding::binary
