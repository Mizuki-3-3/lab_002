#pragma once
#include "sequence.hpp"
#include "dyn_arr.hpp"

template<typename T>

class array_sequence: private sequence
{
private:
    dyn_arr<T> arr;
    unsigned size_;
public:

    T& back() {
        if (size_ == 0 || arr.size() == 0) throw std::out_of_range("dynamic array is empty");
        return arr.data()[size_ - 1];
    }

    const T& back() const {
        if (size_ == 0 || arr.size() == 0) throw std::out_of_range("dynamic array is empty");
        return arr.data()[size_ - 1];
    }
        
    void append(T&& val) {
        if (size >= arr.size()) {
            reserve(capacity_ == 0 ? 16 : capacity_ * 2);
        }
        data_[size_] = std::move(val);
        ++size_;
    }

    void reserve(unsigned new_capacity) {
        if (new_capacity > size_) {
            T* new_data = new T[new_capacity];

            for (unsigned i = 0; i < size_; ++i) {
                new_data[i] = std::move(data_[i]);
            }

            delete[] data_;
            data_ = new_data;
            size_ = new_capacity;
        }
    }
    void resize(unsigned new_size, const T& value = T()) {
        if (new_size > size_) {

            unsigned new_size = size_ == 0 ? new_size : capacity_ * 2;
            if (new_capacity < new_size) {
                    new_capacity = new_size;
            }
            reserve(new_capacity);
        }
        if (new_size > size_) {
            for (size_t i = size_; i < new_size; ++i) {
                new (data_ + i) T(value);
            }
        } else if (new_size < size_) {

            for (size_t i = new_size; i < size_; ++i) {
                (data_ + i)->~T();
            }
        }

        size_ = new_size;
    }
};