#pragma once

#include <gostd/cpp/shared_ptr.hpp>
#include <gostd/cpp/type_traits.hpp>
#include <gostd/cpp/utility.hpp>

namespace gostd::cpp {

class any;

template <typename ValueType>
ValueType* any_cast(const any* operand) noexcept;

class any {
public:
    constexpr any() {}
    any(const any& other) = default;
    any(any&& other) noexcept = default;
    any& operator=(const any& other) = default;
    any& operator=(any&& other) = default;

    template <typename ValueType, typename = typename enable_if<!is_same<typename decay<ValueType>::type, any>::value>::type>
    any(ValueType&& other) {
        emplace<typename decay<ValueType>::type>(forward<ValueType>(other));
    }

    template <typename ValueType>
    any& operator=(ValueType&& other) {
        reset();
        emplace<typename decay<ValueType>::type>(forward<ValueType>(other));
        return *this;
    }

    ~any() {
        reset();
    }

    template <typename ValueType, typename... Args>
    void emplace(Args&&... args) {
        reset();
        auto ptr = new(placement{malloc(sizeof(ValueType))}) ValueType(forward<Args>(args)...);
        _ptr.reset(ptr, &_deleter<ValueType>);
        _comparison = &_compare<ValueType>;
    }

    void reset() {
        _ptr.reset();
    }

    bool has_value() const noexcept { return bool(_ptr); }

    bool operator==(const any& other) const {
        if (_comparison == nullptr) {
            return other._comparison == nullptr;
        }
        return _comparison(_ptr.get(), &other);
    }

    bool operator!=(const any& other) const {
        return !(*this == other);
    }

private:
    shared_ptr<void> _ptr;
    bool(*_comparison)(void*, const any*) = nullptr;

    template <typename ValueType>
    friend ValueType* any_cast(const any* operand) noexcept;

    template <typename ValueType>
    static void _deleter(void* ptr) {
        reinterpret_cast<ValueType*>(ptr)->~ValueType();
    }

    template <typename T, typename = void_t<>>
    struct _compare_helper {
        static bool _compare(void* ptr, const any* other) {
            return false;
        }
    };

    template <typename T>
    struct _compare_helper <T, void_t<decltype(declval<T&>() == declval<T&>())>> {
        static bool _compare(void* ptr, const any* other) {
            auto op = any_cast<T>(other);
            return op != nullptr && *reinterpret_cast<T*>(ptr) == *op;
        }
    };

    template <typename ValueType>
    static bool _compare(void* ptr, const any* other) {
        return _compare_helper<ValueType>::_compare(ptr, other);
    }
};

template <typename ValueType>
ValueType* any_cast(const any* operand) noexcept {
    if (operand->_comparison == &any::_compare<ValueType>) {
        return reinterpret_cast<ValueType*>(operand->_ptr.get());
    }
    return nullptr;
}

} // namespace gostd::cpp
