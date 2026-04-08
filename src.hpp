#pragma once
#include <new>
#include <utility>

namespace sjtu {

template <typename _Tp>
class unique_ptr {
  private:
    _Tp *ptr;

  public:
    unique_ptr() noexcept : ptr(nullptr) {}

    unique_ptr(const unique_ptr &) = delete;

    unique_ptr(unique_ptr &&other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    ~unique_ptr() {
        static_assert(sizeof(_Tp) > 0, "can't delete an incomplete type");
        delete ptr;
    }

    unique_ptr &operator=(const unique_ptr &) = delete;

    unique_ptr &operator=(unique_ptr &&other) noexcept {
        if (this != &other) {
            static_assert(sizeof(_Tp) > 0, "can't delete an incomplete type");
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    explicit unique_ptr(_Tp *p) noexcept : ptr(p) {}

    void reset() noexcept {
        static_assert(sizeof(_Tp) > 0, "can't delete an incomplete type");
        delete ptr;
        ptr = nullptr;
    }

    _Tp *release() noexcept {
        _Tp *temp = ptr;
        ptr = nullptr;
        return temp;
    }

    _Tp *get() const noexcept {
        return ptr;
    }

    _Tp &operator*() const {
        return *ptr;
    }

    _Tp *operator->() const noexcept {
        return ptr;
    }
};

static_assert(sizeof(unique_ptr<int>) <= sizeof(void *));

template <typename _Tp, typename... Args>
unique_ptr<_Tp> make_unique(Args &&... args) {
    return unique_ptr<_Tp>(new _Tp(std::forward<Args>(args)...));
}

} // namespace sjtu