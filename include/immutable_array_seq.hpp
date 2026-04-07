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

    explicit immutable_array_seq(const dyn_arr<T>& other) : arr(new dyn_arr<T>(other)), size_(other.size) {}

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

    dyn_arr<T>* append(T& val) {
        if (size_==arr->len()){
            dyn_arr<T>* new_dyn_arr = new dyn_arr(arr->data, size_+1);
            new_dyn_arr->data[size_] = val;
            return new_dyn_arr;
        }
        dyn_arr<T>* new_dyn_arr = new dyn_arr(*arr);
        new_dyn_arr[size_] = val;
        return new_dyn_arr;
    }

    dyn_arr<T>* prepend(T& val) {
        if (size_==arr->size){
            dyn_arr<T>* new_dyn_arr = new dyn_arr(arr->data, size_+1);
            for (unsigned i = size_; i > 0; i--){
                new_dyn_arr->data[i] = new_dyn_arr->data[i-1];
            }
            new_dyn_arr->data[0] = val;
            return new_dyn_arr;
        }
        dyn_arr<T>* new_dyn_arr = new dyn_arr(*arr);
        new_dyn_arr->data[0] = val;
        return new_dyn_arr;
    }
    dyn_arr<T>* insert(const T& val, unsigned index){
        if (index >= arr->size) throw std::out_of_range("index out of range");
        if (index == 0) { return prepend(val); }
        if (index == arr->len()) {  return append(val); }
        dyn_arr<T>* new_dyn_arr = new dyn_arr<T>(arr->data);
        for (int i = size_; i > index; i--){
            new_dyn_arr->data[i] = new_dyn_arr->data[i-1];
        }
        new_dyn_arr->data[index] = val;
        return new_dyn_arr;
    }
    unsigned find(const T& val){
        for (unsigned i = 0; i < size_; i++){
            if (arr[i] == val) return i;
        }
        throw std::out_of_range("not found");
    }
};