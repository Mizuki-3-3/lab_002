#pragma once

template<typename T>
class dyn_arr :
{
    private:
        T* data_;
        unsigned size_;
    public:
        dyn_arr () : data_(nullptr), capacity_(0), size_(0) {}
        explicit dyn_arr(size_t initial_size)
            : data_(new T[initial_size]), size_(initial_size) {
            for (size_t i = 0; i < initial_size; ++i) {
                data_[i] = T();  // или nullptr для указателей
            }
        }
        ~dyn_arr() {
            delete[] data_;
        }

        dyn_arr(const vector& ) = delete;

        dyn_arr& operator=(const vector&) = delete;

        dyn_arr(dyn_arr&& other) noexcept : data_(other.data_), size_(other.size_) {
            other.data_ = nullptr;
            other.size_ = 0;
        }
        dyn_arr& operator=(r&& other) noexcept{
            std::swap(data_, other.data_);
            std::swap(size_, other.size_);
            return *this;
        }

        T& operator[](unsigned index) {
            if (index>=size_) throw std::out_of_range("Index out of range");
            return data_[index];
        }

        const T& operator[](unsigned index) const {
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
        
        [[nodiscard]] unsigned size() const { return size_;}

        T* data() { return data_; }

        const T* data() const { return data_; }

        const T* end() const { return data_ + size_; }
};
