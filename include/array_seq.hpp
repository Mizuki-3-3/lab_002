#pragma once
#include "sequence.hpp"
#include "dyn_arr.hpp"

template<typename T>

class array_sequence: private sequence
{
private:
    dyn_arr<T> arr;
    unsigned size_; ////(capacity)
public:
        
    void append(T& val) {
        if (size >= arr.len()) {
            reserve(capacity_ == 0 ? 16 : capacity_ * 2);
        }
        data_[size_] = std::move(val);
        ++size_;
    }

    void reserve(unsigned new_size) {
        if (new_size > arr.len()) {
            T* new_data = new T[new_size];

            for (unsigned i = 0; i < new_size; ++i) {
                new_data[i] = std::move(data_[i]);
            }
            delete[] arr.;
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
            for (unsigned i = size_; i < new_size; ++i) {
                new (data_ + i) T(value);
            }
        } else if (new_size < size_) {

            for (unsigned i = new_size; i < size_; ++i) {
                (data_ + i)->~T();
            }
        }

        size_ = new_size;
    }
};