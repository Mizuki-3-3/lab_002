#pragma once

enum class Mutability {
    M,
    I
};

template<Mutability M, typename T>

class array_seq {
    dyn_arr<T>* arr;
    
public:
    array_seq() : arr(new dyn_arr<T>()), size_(0) {}

    explicit array_seq(const dyn_arr<T>& other) : arr(new dyn_arr<T>(other)), size_(other.len()) {}

    array_seq(const T* items, unsigned count) : arr(new dyn_arr<T>(items, count)), size(sizeof(items)/sizeof(items[0])){}

    array_seq(const array_seq& other) : arr(new dyn_arr<T>(*other.arr)), size_(other.size_) {}

    ~array_seq() { delete arr; }

    array_seq& operator=(const array_seq& other) {
        if (this != &other) {
            dyn_arr<T>* new_arr = new dyn_arr<T>(*other.arr);
            delete arr;
            arr = new_arr;
            size_ = other.size_;
        }
        return *this;
    }

    array_seq<M, T>* append(const T& val) {
        if constexpr (M == Mutability::M) {
            if (size_ == arr->len()) {
                arr->resize(size_ + 1);
            }
            arr->data[size_] = val;
            size_++;
            return this;
        } else {
            if (size_==arr->len()){
                array_seq<Mutability::I, T>* new_dyn_arr = new array_seq(*arr, size_+1);
                new_dyn_arr->arr->data[size_] = val;
                return new_dyn_arr;
            }
            array_seq<Mutability::I, T>* new_dyn_arr = new immutable_array_seq(*this);
            new_dyn_arr->size_++;
            new_dyn_arr->arr->data[size_] = val;
            return new_dyn_arr;
        }
    }
    array_seq<M, T>* prepend(const T& val) {
        if constexpr (M == Mutability::Mutable) {
            if (size_ == arr->len()) { arr->resize(size_ + 1);}
            for (unsigned i = size_; i > 0; --i) {
                arr->data[i] = arr->data[i - 1];
            }
            arr->data[0] = val;
            size_++;
            return this;
        } else {
            dyn_arr<T>* new_arr = new dyn_arr<T>(size_ + 1);
            new_arr->data[0] = val;
            for (unsigned i = 0; i < size_; ++i) {
                new_arr->data[i + 1] = arr->data[i];
            }
            return new array_seq<Mutability::Immutable, T>(new_arr, size_ + 1);
        }
    }

    array_seq<M, T>* insert(const T& val, unsigned index) {
        if (index > size_) {
            throw std::out_of_range("index out of range");
        }
        if (index == 0) {
            return prepend(val);
        }
        if (index == size_) {
            return append(val);
        }

        if constexpr (M == Mutability::Mutable) {
            if (size_ == arr->len()) {
                arr->resize(size_ + 1);
            }
            for (unsigned i = size_; i > index; --i) {
                arr->data[i] = arr->data[i - 1];
            }
            arr->data[index] = val;
            ++size_;
            return this;
        } else {
            dyn_arr<T>* new_arr = new dyn_arr<T>(size_ + 1);
            for (unsigned i = 0; i < index; ++i) {
                new_arr->data[i] = arr->data[i];
            }
            new_arr->data[index] = val;
            for (unsigned i = index; i < size_; ++i) {
                new_arr->data[i + 1] = arr->data[i];
            }
            return new array_seq<Mutability::Immutable, T>(new_arr, size_ + 1);
        }
    }

    unsigned size() const { return size_; }
    T& operator[](unsigned index) {
        if (index >= size_) throw std::out_of_range("index out of range");
        return arr->data[index];
    }
    const T& operator[](unsigned index) const {
        if (index >= size_) throw std::out_of_range("index out of range");
        return arr->data[index];
    }

    auto begin() { return arr->begin(); }
    auto end()   { return arr->end(); }
    auto begin() const { return arr->begin(); }
    auto end()   const { return arr->end(); }
};