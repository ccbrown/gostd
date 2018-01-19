#pragma once

#include <gostd/_string.hpp>

namespace gostd {

class Error {
public:
    constexpr Error() {}
    Error(const Error& other) = default;
    Error(Error&& other) = default;
    Error& operator=(const Error& other) = default;
    Error& operator=(Error&& other) = default;

    template <typename T, typename = typename cpp::enable_if<!cpp::is_same<typename cpp::decay<T>::type, Error>::value>::type>
    constexpr Error(T&& err) : Error(cpp::forward<T>(err), typename from_value_or_pointer<typename cpp::decay<T>::type>::type{}) {}

    explicit constexpr operator bool() const {
        return _error.has_value();
    }

    explicit operator String() const {
        if (!_errorFunc) {
            return "<nil>";
        }
        return _errorFunc();
    }
    bool operator==(const Error& other) const { return _error == other._error; }
    bool operator!=(const Error& other) const { return _error != other._error; }

    template <typename T>
    auto As() const {
        struct { T v; bool ok = false; } ret;
        if (auto ptr = cpp::any_cast<T>(&_error); ptr != nullptr) {
            ret.v = *ptr;
            ret.ok = true;
        }
        return ret;
    }

private:
    struct from_value {};
    struct from_pointer {};

    template <typename T>
    struct from_value_or_pointer {
        template <typename U> static from_value test(decltype(&U::Error));
        template <typename U> static from_pointer test(...);
        using type = decltype(test<T>(0));
    };

    template <typename T>
    Error(T&& err, from_value x) : _error{cpp::forward<T>(err)} {
        auto stored = cpp::any_cast<typename cpp::decay<T>::type>(&_error);
        _errorFunc = [=] { return stored->Error(); };
    }

    template <typename T>
    Error(T&& err, from_pointer x) : _error{cpp::forward<T>(err)} {
        auto stored = cpp::any_cast<typename cpp::decay<T>::type>(&_error);
        _errorFunc = [=] { return (*stored)->Error(); };
    }

    Func<String()> _errorFunc;
    cpp::any _error;
};

} // namespace gostd
