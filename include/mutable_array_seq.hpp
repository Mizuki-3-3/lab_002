#pragma once
#include "sequence.hpp"
#include "dyn_arr.hpp"
#include <stdexcept>

template<typename T>
class mutable_array_seq: public sequence<T>
{
private:
    dyn_arr<T>* arr;
    unsigned size_; ////(заполненность)
public:
    mutable_array_seq() : arr(new dyn_arr<T>()), size_(0)  {}

    explicit mutable_array_seq(const dyn_arr<T>& other) : arr(new dyn_arr<T>(other)), size_(other.size) {}

    mutable_array_seq(const T* items, unsigned count) : arr(new dyn_arr<T>(items, count)), size(sizeof(items)/sizeof(items[0])) {}

    mutable_array_seq(const mutable_array_seq& other) : arr(new dyn_arr<T>(*other.arr)) {}

    ~mutable_array_seq() {delete arr;}

    mutable_array_seq& operator=(const mutable_array_seq& other) {
        if (this != &other) {
            dyn_arr<T>* new_arr = new dyn_arr<T>(*other.arr);
            delete arr;
            arr = new_arr;
            size_=other.size_;
        }
        return *this;
    }

    mutable_array_seq<T>* append(T& val) {
        if (size_ == arr->len()) {
            arr->resize(size_+1);
        }
        arr->data[size_] = val;
        size_++;
        return this;
    }
    mutable_array_seq<T>* prepend(T& val) {
        if (size_ >= arr->len()) {
            arr->resize(size_+1);
            for (unsigned i = size_; i > 0; i--){
                arr->data[i] = arr->data[i-1];
            }
        }
        arr->data[0] = val;
        size_++;
        return this;
    }

    mutable_array_seq<T>* insert(const T& val, unsigned index){
        if (index >= arr->size) throw std::out_of_range("index out of range");
        if (index == 0) { return prepend(val); }
        if (index == arr->len()-1) {  return append(val); }
        for (int i = size_; i > index; i--){
            arr->data[i] = arr->data[i-1];
        }
        arr->data[index] = val;
        return this;
    }
};