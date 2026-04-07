#pragma once
#include "sequence.hpp"
#include "dyn_arr.hpp"

template<typename T>
class immutable_array_seq: public sequence<T>
{
private:
    dyn_arr<T>* arr;
    unsigned size_; ////(заполненность)
public:
    immutable_array_seq(T* items, unsigned count): arr(items, count), size_(count){}
    immutable_array_seq(): arr(nullptr), size_(0){}
    immutable_array_seq(dyn_arr<T>& other const){arr=other->data, other->}



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
            new_dyn_arr->data[size_] = val;
            return new_dyn_arr;
        }
        dyn_arr<T>* new_dyn_arr = new dyn_arr(*arr);
        new_dyn_arr[size_] = val;
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
};