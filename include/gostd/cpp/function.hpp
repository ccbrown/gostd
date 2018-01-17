#pragma once

#include <gostd/cpp/any.hpp>
#include <gostd/cpp/utility.hpp>

namespace gostd::cpp {

template <class>
class function;

template <class R, class... Args>
class function<R(Args...)> {
public:
    constexpr function() {}
    function(const function& other) = default;
    function(function&& other) = default;
    function& operator=(const function& other) = default;
    function& operator=(function&& other) = default;

    template <class F>
    function(F f) : _functor{move(f)}, _invoker{&_invoke<F>} {}

    template <class F>
    function& operator=(F f) {
        _functor = move(f);
        _invoker = &_invoke<F>;
        return *this;
    }

    R operator()(Args... args) const {
        return _invoker(&_functor, args...);
    }

    explicit operator bool() const noexcept {
        return _functor.has_value();
    }

private:
    any _functor;
    R(*_invoker)(const any* functor, Args...);

    template <class F>
    static R _invoke(const any* functor, Args... args) {
        auto f = any_cast<typename decay<F>::type>(functor);
        return (*f)(args...);
    }
};

} // namespace gostd::cpp
