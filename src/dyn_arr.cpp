#include "dyn_arr.hpp"
#include "errors.hpp"
#include <utility>

template<typename T>
dyn_arr<T>::iterator::iterator(T* ptr) : current(ptr) {}

template<typename T>
typename dyn_arr<T>::iterator& dyn_arr<T>::iterator::operator++() {
    ++current;
    return *this;
}

template<typename T>
typename dyn_arr<T>::iterator dyn_arr<T>::iterator::operator++(int) {
    iterator tmp = *this;
    ++current;
    return tmp;
}

template<typename T>
T& dyn_arr<T>::iterator::operator*() { return *current; }

template<typename T>
const T& dyn_arr<T>::iterator::operator*() const { return *current; }

template<typename T>
int dyn_arr<T>::iterator::operator!=(iterator& other) const { return current != other.current; }

template<typename T>
int dyn_arr<T>::iterator::operator==(iterator& other) const { return current == other.current; }

template<typename T>
dyn_arr<T>::const_iterator::const_iterator(const T* ptr) : current(ptr) {}

template<typename T>
typename dyn_arr<T>::const_iterator& dyn_arr<T>::const_iterator::operator++() {
    ++current;
    return *this;
}

template<typename T>
typename dyn_arr<T>::const_iterator dyn_arr<T>::const_iterator::operator++(int) {
    const_iterator tmp = *this;
    ++current;
    return tmp;
}

template<typename T>
const T& dyn_arr<T>::const_iterator::operator*() const { return *current; }

template<typename T>
int dyn_arr<T>::const_iterator::operator!=(const const_iterator& other) const { return current != other.current; }

template<typename T>
int dyn_arr<T>::const_iterator::operator==(const const_iterator& other) const { return current == other.current; }

template<typename T>
dyn_arr<T>::dyn_arr() : data(nullptr), size(0) {}

template<typename T>
dyn_arr<T>::dyn_arr(unsigned initial_size) : data(new T[initial_size]), size(initial_size) {
    if (data == nullptr) THROW(ERR_MEMORY);
    for (unsigned i = 0; i < size; ++i)
        data[i] = T();
}

template<typename T>
dyn_arr<T>::dyn_arr(const T* items, unsigned initial_size) : data(new T[initial_size]), size(initial_size) {
    if (data == nullptr) THROW(ERR_MEMORY);
    if (items == nullptr && initial_size > 0) THROW(ERR_NULL);
    for (unsigned i = 0; i < size; ++i)
        data[i] = items[i];
}

template<typename T>
dyn_arr<T>::dyn_arr(const dyn_arr& other) : data(new T[other.size]), size(other.size) {
    if (data == nullptr) THROW(ERR_MEMORY);
    for (unsigned i = 0; i < size; ++i)
        data[i] = other.data[i];
}

template<typename T>
dyn_arr<T>::~dyn_arr() { delete[] data; }

template<typename T>
T& dyn_arr<T>::operator[](unsigned index) {
    if (index >= size) THROW(ERR_INCORRECT_INDEX);
    return data[index];
}

template<typename T>
const T& dyn_arr<T>::operator[](unsigned index) const {
    if (index >= size) THROW(ERR_INCORRECT_INDEX);
    return data[index];
}

template<typename T>
typename dyn_arr<T>::iterator dyn_arr<T>::begin() { return iterator(data); }

template<typename T>
typename dyn_arr<T>::const_iterator dyn_arr<T>::begin() const { return const_iterator(data); }

template<typename T>
typename dyn_arr<T>::iterator dyn_arr<T>::end() { return iterator(data + size); }

template<typename T>
typename dyn_arr<T>::const_iterator dyn_arr<T>::end() const { return const_iterator(data + size); }

template<typename T>
T* dyn_arr<T>::data() { return data; }

template<typename T>
const T* dyn_arr<T>::data() const { return data; }

template<typename T>
unsigned dyn_arr<T>::len() const { return size; }

template<typename T>
dyn_arr<T>& dyn_arr<T>::operator=(dyn_arr other) {
    std::swap(data, other.data);
    std::swap(size, other.size);
    return *this;
}

template<typename T>
void dyn_arr<T>::resize(unsigned new_size) {
    T* new_data = new T[new_size];
    if (new_data == nullptr) THROW(ERR_MEMORY);
    unsigned copy_size = (new_size < size) ? new_size : size;
    for (unsigned i = 0; i < copy_size; ++i)
        new_data[i] = data[i];
    for (unsigned i = copy_size; i < new_size; ++i)
        new_data[i] = T();
    delete[] data;
    data = new_data;
    size = new_size;
}