#pragma once

#include <cx/cpp/cstdint.hpp>
#include <cx/cpp/utility.hpp>
#include <cx/cpp/type_traits.hpp>

namespace cx::cpp {

struct placement{ void* ptr; };

} // namespace cx::cpp

void* operator new(cx::cpp::size_t size, cx::cpp::placement placement);
void operator delete(void* ptr, cx::cpp::placement placement);

namespace cx::cpp {

size_t malloc_size(void* ptr);
void* malloc(size_t size);
void free(void* ptr);

static size_t strlen(const char* s) {
    size_t len = 0;
    while (s[len]) {
        ++len;
    }
    return len;
}

template <class T>
class shared_ptr {
public:
    constexpr shared_ptr() {}

    void reset() noexcept {
        if (_ptr && --*_refs == 0) {
            _deleter(_ptr);
            _ptr = nullptr;
        }
    }

    template <class Y>
    void reset(Y* ptr, void(*d)(T*)) {
        reset();
        _ptr = ptr;
        _refs = reinterpret_cast<size_t*>(malloc(sizeof(*_refs)));
        _deleter = d;
        *_refs = 1;
    }

    T* get() const noexcept { return _ptr; }

private:
    T* _ptr = nullptr;
    size_t* _refs = nullptr;
    void(*_deleter)(T*) = nullptr;
};

class any {
public:
    constexpr any() {}

    template <class ValueType>
    any(ValueType&& other) {
        emplace<typename decay<ValueType>::type>(forward<ValueType>(other));
    }

    template <class ValueType>
    any& operator=(ValueType&& other) {
        reset();
        emplace<typename decay<ValueType>::type>(forward<ValueType>(other));
        return *this;
    }

    ~any() {
        reset();
    }

    template <class ValueType, class... Args>
    void emplace(Args&&... args) {
        reset();
        auto ptr = new(placement{malloc(sizeof(ValueType))}) ValueType(forward<Args>(args)...);
        _ptr.reset(ptr, &_deleter<ValueType>);
        _tag = &_type_tag<ValueType>;
    }

    void reset() {
        _ptr.reset();
    }

private:
    shared_ptr<void> _ptr;
    void(*_tag)() = nullptr;

    template <class ValueType>
    friend ValueType* any_cast(const any* operand) noexcept;

    template <class ValueType>
    static void _type_tag() {}

    template <class ValueType>
    static void _deleter(void* ptr) {
        reinterpret_cast<ValueType*>(ptr)->~ValueType();
    }
};

template <class ValueType>
ValueType* any_cast(const any* operand) noexcept {
    if (operand->_tag == &any::_type_tag<ValueType>) {
        return reinterpret_cast<ValueType*>(operand->_ptr.get());
    }
    return nullptr;
}

template <class>
class function;

template <class R, class... Args>
class function<R(Args...)> {
public:
    constexpr function() {}

    template <class F>
    function(F&& f) : _functor{forward<F>(f)}, _invoker{&_invoke<F>} {}

    template <class F>
    function& operator=(F&& f) {
        _functor = forward<F>(f);
        _invoker = &_invoke<F>;
        return *this;
    }

    R operator()(Args... args) const {
        return _invoker(&_functor, args...);
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

} // namespace cx::cpp
