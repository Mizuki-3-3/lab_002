#include <concepts>
#include <iostream>


template <std::integral T>
class bit_proxy {
    T& ref;
    unsigned idx;
public:
    bit_proxy(T& w, size_t b) : word(w), bit(b) {}
    bit_proxy operator=(bool val) {
        if (val) { ref |= (static_cast<T>(1) << idx); }
        else { ref &= ~(static_cast<T>(1) << idx); }
        return *this;
    }

    operator bool() const { return (ref >> idx) & 1; }
};

template <std::integral T>
class bit {
    T value;
    static constexpr unsigned len {sizeof(T)};
    using proxy = bit_proxy
public:
    bit_proxy<T> operator[](size_t idx) {
        return bit_proxy<T>(value, idx);
    }
};