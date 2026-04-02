#pragma once
#include "sequence.hpp"
#include "dyn_arr.hpp"

template<typename T>

class array_sequence: private sequence
{
private:
    dyn_arr ;
    unsigned size_;
public:

    T& back() {
        if (size_ == 0) throw std::out_of_range("Vector is empty");
        return data_[size_ - 1];
    }

    const T& back() const {
        if (size_ == 0) throw std::out_of_range("Vector is empty");
        return data_[size_ - 1];
    }
    [[nodiscard]] size_t size() const { return size_;}

    [[nodiscard]] size_t capacity() const { return capacity_;}
        
    [[nodiscard]] bool empty() const { return size_ == 0;}

    T* data() { return data_; }

    const T* data() const { return data_; }

    T* begin() { return data_; }

    T* end() { return data_ + size_; }

    const T* end() const { return data_ + size_; }
    void pop_back() {
        if (size_ == 0) throw std::out_of_range("dynamic array is empty");
        --size_;
    }
        
    void push_back(const T& val) {
        if (size_ >= capacity_) {
            reserve(capacity_ == 0 ? 16 : capacity_ * 2);
        }
        data_[size_] = val;
        size_++;
    }
        
    void append(T&& val) {
        if (size_ >= capacity_) {
            reserve(capacity_ == 0 ? 16 : capacity_ * 2);
        }
        data_[size_] = std::move(val);
        ++size_;
    }

    void reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            T* new_data = new T[new_capacity];

            for (size_t i = 0; i < size_; ++i) {
                new_data[i] = std::move(data_[i]);
            }

            delete[] data_;
            data_ = new_data;
            capacity_ = new_capacity;
        }
    }
    void resize(size_t new_size, const T& value = T()) {
        if (new_size > capacity_) {

            size_t new_capacity = capacity_ == 0 ? new_size : capacity_ * 2;
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