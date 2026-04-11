#pragma once

#include "dyn_arr.hpp"
#include "Mutability.hpp"

template<Mutability M, typename T>
class array_seq {
private:
    dyn_arr<T>* arr;
public:
    array_seq();
    explicit array_seq(const dyn_arr<T>& other);
    array_seq(const T* items, unsigned count);
    array_seq(const array_seq& other);
    ~array_seq();

    array_seq& operator=(const array_seq& other);

    array_seq<M, T>* append(const T val);
    array_seq<M, T>* prepend(const T val);
    array_seq<M, T>* insert(const T val, unsigned index);

    template <typename Func>
    array_seq<M, T>* map(Func f);

    template <typename Func>
    array_seq<M, T>* where(Func f);

    template <typename Func>
    auto reduce(Func f, T first) const;

    unsigned size() const;
    T& operator[](unsigned index);
    const T& operator[](unsigned index) const;

    auto begin();
    auto end();
    auto begin() const;
    auto end() const;
};

#include "array_seq.cpp"