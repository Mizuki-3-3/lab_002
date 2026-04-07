#pragma once

#include "sequence.hpp"
#include "dyn_arr.hpp"
#include <stdexcept>

template<typename T>
class immutable_array_seq: public sequence<T>
{
private:
    dyn_arr<T>* arr;
    unsigned size_; ////(заполненность)
public:
    immutable_array_seq(): arr(new dyn_arr<T>()), size_(0) {}

    explicit immutable_array_seq(const dyn_arr<T>& other, unsigned size) : arr(new dyn_arr<T>(other->data, size)), size_(size) {}

    immutable_array_seq(const immutable_array_seq& other) : arr(new dyn_arr<T>(*other.arr)), size_(other.size_) {}
    ~immutable_array_seq() { delete arr;}

    immutable_array_seq& operator=(const immutable_array_seq& other) {
        if (this != &other) {
            dyn_arr<T>* new_arr = new dyn_arr<T>(*other.arr);
            delete arr;
            arr = new_arr;
            size_ = other.size_;
        }
        return *this;
    }

    immutable_array_seq<T>* append(T& val) {
        if (size_==arr->len()){
            immutable_array_seq<T>* new_dyn_arr = new immutable_array_seq(*arr, size_+1);
            new_dyn_arr->data[size_] = val;
            return new_dyn_arr;
        }
        immutable_array_seq<T>* new_dyn_arr = new immutable_array_seq(*this);
        new_dyn_arr->size_++;
        new_dyn_arr->arr->data[size_] = val;
        return new_dyn_arr;
    }

    immutable_array_seq<T>* prepend(T& val) {
        if (size_==arr->size){
            immutable_array_seq<T>* new_dyn_arr = new immutable_array_seq(*arr, size_+1);
            for (unsigned i = size_; i > 0; i--){
                new_dyn_arr->arr->data[i] = new_dyn_arr->arr->data[i-1];
            }
            new_dyn_arr->arr->data[0] = val;
            return new_dyn_arr;
        }
        immutable_array_seq<T>* new_dyn_arr = new immutable_array_seq(*arr, size_+1)
        new_dyn_arr->arr->data[0] = val;
        return new_dyn_arr;
    }
    immutable_array_seq<T>* insert(const T& val, unsigned index){
        if (index >= arr->size) throw std::out_of_range("index out of range");
        if (index == 0) { return prepend(val); }
        if (index == arr->size) {  return append(val); }
        immutable_array_seq<T>* new_dyn_arr = new immutable_array_seq<T>(*arr, size_+1);
        for (int i = size_; i > index; i--){
            new_dyn_arr->arr->data[i] = new_dyn_arr->arr->data[i-1];
        }
        new_dyn_arr->arr->data[index] = val;
        return new_dyn_arr;
    }
};