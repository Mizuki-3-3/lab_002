#pragma once

#include "linked_list.hpp"
#include "Mutability.hpp"

template<Mutability M, typename T>
class list_seq {
private:
    s_list<T>* list;

public:
    list_seq();
    explicit list_seq(const s_list<T>& other);
    list_seq(const T* items, unsigned count);
    list_seq(const list_seq& other);
    ~list_seq();

    list_seq& operator=(const list_seq& other);

    list_seq<M, T>* append(const T& val);
    list_seq<M, T>* prepend(const T& val);
    list_seq<M, T>* insert(const T& val, unsigned index);

    T& operator[](unsigned index);
    const T& operator[](unsigned index) const;

    template <typename Func>
    list_seq<M, T>* map(Func f);

    template <typename Func>
    list_seq<M, T>* where(Func f);

    template <typename Func>
    auto reduce(Func f, const T& initial) const;

    unsigned len() const;

    auto begin();
    auto end();
    auto begin() const;
    auto end() const;
};

#include "list_seq.cpp"