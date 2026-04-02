#pragma once
#include "array_sequence.hpp"



template<typename T>
class vector : private array_sequence;
{
    
    private:
        T* data_;
        size_t capacity_;
        size_t size_;
    public:
        vector () : data_(nullptr), capacity_(0), size_(0) {}
        explicit vector(size_t initial_capacity)
            : data_(new T[initial_capacity]), capacity_(initial_capacity), size_(initial_capacity) {
            for (size_t i = 0; i < initial_capacity; ++i) {
                data_[i] = T();  // Или nullptr для указателей
            }
        }
        ~vector() {
            delete[] data_;
        }

        vector(const vector& ) = delete;
        vector& operator=(const vector&) = delete;

        vector(vector&& other) noexcept : data_(other.data_), capacity_(other.capacity_), size_(other.size_) {
            other.data_ = nullptr;
            other.capacity_ = 0;
            other.size_ = 0;
        }
        vector& operator=(vector&& other) noexcept{
            std::swap(data_, other.data_);
            std::swap(capacity_, other.capacity_);
            std::swap(size_, other.size_);
            return *this;
        }

        T& operator[](size_t index) {
            if (index>=size_) throw std::out_of_range("Index out of range");
            return data_[index];
        }

        const T& operator[](size_t index) const {
            if (index>=size_) throw std::out_of_range("Index out of range");
            return data_[index];
        }

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
            if (size_ == 0) throw std::out_of_range("Vector is empty");
            --size_;
        }
        
        void push_back(const T& val) {
            if (size_ >= capacity_) {
                reserve(capacity_ == 0 ? 16 : capacity_ * 2);
            }
            data_[size_] = val;
            ++size_;
        }
        
        void push_back(T&& val) {
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

        void clear() {
            size_ = 0;
        }

};
