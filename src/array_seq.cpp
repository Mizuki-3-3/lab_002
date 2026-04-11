#include "array_seq.hpp"
#include "errors.hpp"

template <Mutability M, typename T>
array_seq<M,T>::array_seq() : arr(new dyn_arr<T>()) {
    if (arr == nullptr) THROW(ERR_MEMORY);
}

template <Mutability M, typename T>
array_seq<M,T>::array_seq(const dyn_arr<T>& other) : arr(new dyn_arr<T>(other)) {
    if (arr == nullptr) THROW(ERR_MEMORY);
}

template <Mutability M, typename T>
array_seq<M,T>::array_seq(const T* items, unsigned count) : arr(new dyn_arr<T>(items, count)) {
    if (arr == nullptr) THROW(ERR_MEMORY);
}

template <Mutability M, typename T>
array_seq<M,T>::array_seq(const array_seq& other) : arr(new dyn_arr<T>(*other.arr)) {
    if (arr == nullptr) THROW(ERR_MEMORY);
}

template <Mutability M, typename T>
array_seq<M,T>::~array_seq() { delete arr; }

template <Mutability M, typename T>
array_seq<M,T>& array_seq<M,T>::operator=(const array_seq& other) {
    if (this != &other) {
        dyn_arr<T>* new_arr = new dyn_arr<T>(*other.arr);
        if (new_arr == nullptr) THROW(ERR_MEMORY);
        delete arr;
        arr = new_arr;
    }
    return *this;
}

template <Mutability M, typename T>
array_seq<M, T>* array_seq<M,T>::append(const T val) {
    if constexpr (M == Mutability::Mutable) {
        arr->resize(arr->len() + 1);
        arr->data[arr->len() - 1] = val;
        return this;
    } else {
        array_seq<Mutability::Immutable, T>* new_dyn_arr = 
            new array_seq<Mutability::Immutable, T>(arr->data(), arr->len() + 1);
        if (new_dyn_arr == nullptr) THROW(ERR_MEMORY);
        new_dyn_arr->arr->data[arr->len()] = val;
        return new_dyn_arr;
    }
}

template <Mutability M, typename T>
array_seq<M, T>* array_seq<M,T>::prepend(const T val) {
    if constexpr (M == Mutability::Mutable) {
        arr->resize(arr->len() + 1);
        for (unsigned i = arr->len() - 1; i > 0; --i)
            arr->data[i] = arr->data[i - 1];
        arr->data[0] = val;
        return this;
    } else {
        dyn_arr<T>* new_arr = new dyn_arr<T>(arr->len() + 1);
        if (new_arr == nullptr) THROW(ERR_MEMORY);
        new_arr->data[0] = val;
        for (unsigned i = 0; i < arr->len(); ++i)
            new_arr->data[i + 1] = arr->data[i];
        array_seq<Mutability::Immutable, T>* result = new array_seq<Mutability::Immutable, T>(*new_arr);
        if (result == nullptr) THROW(ERR_MEMORY);
        delete new_arr; // больше не нужен, т.к. result хранит свою копию
        return result;
    }
}

template <Mutability M, typename T>
array_seq<M, T>* array_seq<M,T>::insert(const T val, unsigned index) {
    if (index > arr->len()) {
        THROW(ERR_INCORRECT_INDEX);
    }
    if (index == 0) {
        return prepend(val);
    }
    if (index == arr->len()) {
        return append(val);
    }

    if constexpr (M == Mutability::Mutable) {
        arr->resize(arr->len() + 1);
        for (unsigned i = arr->len() - 1; i > index; --i)
            arr->data[i] = arr->data[i - 1];
        arr->data[index] = val;
        return this;
    } else {
        dyn_arr<T>* new_arr = new dyn_arr<T>(arr->len() + 1);
        if (new_arr == nullptr) THROW(ERR_MEMORY);
        for (unsigned i = 0; i < index; ++i)
            new_arr->data[i] = arr->data[i];
        new_arr->data[index] = val;
        for (unsigned i = index; i < arr->len(); ++i)
            new_arr->data[i + 1] = arr->data[i];
        array_seq<Mutability::Immutable, T>* result = new array_seq<Mutability::Immutable, T>(*new_arr);
        if (result == nullptr) THROW(ERR_MEMORY);
        delete new_arr;
        return result;
    }
}

template <Mutability M, typename T>
template <typename Func>
array_seq<M,T>* array_seq<M,T>::map(Func f) {
    if constexpr (M == Mutability::Mutable) {
        for (auto& x : *arr)
            x = f(x);
        return this;
    } else {
        array_seq<Mutability::Immutable, T>* new_arr = 
            new array_seq<Mutability::Immutable, T>(*arr);
        if (new_arr == nullptr) THROW(ERR_MEMORY);
        for (auto& x : *(new_arr->arr))
            x = f(x);
        return new_arr;
    }
}

template <Mutability M, typename T>
template <typename Func>
array_seq<M,T>* array_seq<M,T>::where(Func f) {
    if constexpr (M == Mutability::Mutable) {
        unsigned wr_i = 0;
        for (unsigned r_i = 0; r_i < arr->len(); ++r_i) {
            if (f(arr->data[r_i])) {
                if (wr_i != r_i)
                    arr->data[wr_i] = arr->data[r_i];
                ++wr_i;
            }
        }
        arr->resize(wr_i);
        return this;
    } else {
        unsigned count = 0;
        for (unsigned i = 0; i < arr->len(); ++i)
            if (f(arr->data[i])) ++count;
        dyn_arr<T>* new_data = new dyn_arr<T>(count);
        if (new_data == nullptr) THROW(ERR_MEMORY);
        unsigned pos = 0;
        for (unsigned i = 0; i < arr->len(); ++i)
            if (f(arr->data[i]))
                new_data->data[pos++] = arr->data[i];
        array_seq<Mutability::Immutable, T>* result = new array_seq<Mutability::Immutable, T>(*new_data);
        if (result == nullptr) THROW(ERR_MEMORY);
        delete new_data;
        return result;
    }
}

template <Mutability M, typename T>
template <typename Func>
auto array_seq<M,T>::reduce(Func f, T first) const {
    if (arr->len() == 0)
        THROW(ERR_INCORRECT_INDEX);
    auto temp = f(arr->data[0], first);
    for (unsigned i = 1; i < arr->len(); ++i)
        temp = f(arr->data[i], temp);
    return temp;
}

template <Mutability M, typename T>
unsigned array_seq<M,T>::size() const { return arr->len(); }

template <Mutability M, typename T>
T& array_seq<M,T>::operator[](unsigned index) {
    if (index >= arr->len()) THROW(ERR_INCORRECT_INDEX);
    return arr->data[index];
}

template <Mutability M, typename T>
const T& array_seq<M,T>::operator[](unsigned index) const {
    if (index >= arr->len()) THROW(ERR_INCORRECT_INDEX);
    return arr->data[index];
}

template <Mutability M, typename T>
auto array_seq<M,T>::begin() { return arr->begin(); }

template <Mutability M, typename T>
auto array_seq<M,T>::end() { return arr->end(); }

template <Mutability M, typename T>
auto array_seq<M,T>::begin() const { return arr->begin(); }

template <Mutability M, typename T>
auto array_seq<M,T>::end() const { return arr->end(); }