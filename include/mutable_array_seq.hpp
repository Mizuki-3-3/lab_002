#pragma once
#include "sequence.hpp"
#include "dyn_arr.hpp"

template<typename T>
class m_array_sequence: public sequence<T>
{
private:
    dyn_arr<T>* arr;
    unsigned size_; ////(заполненность)
public:
    dyn_arr<T>* append(T& val) {
        if (size_ == arr->len()) {
            arr->resize(size_+1);
        }
        arr->data[size_] = val;
        size_++;
        return arr;
    }
    dyn_arr<T>* prepend(T& val) {
        if (size_ >= arr->len()) {
            arr->resize(size_+1);
            for (unsigned i = size_; i > 0; i--){
                arr[i] = arr[i-1];
            }
        }
        arr->data[0] = val;
        size_++;
        return arr;
    }

    dyn_arr<T>* insert(const T& val, unsigned index){
        if (index >= arr->size) throw std::out_of_range("index out of range");
        if (index == 0) { return prepend(val); }
        if (index == arr->len()) {  return append(val); }
        for (int i = size_; i > index; i--){
            arr->data[i] = arr->data[i-1];
        }
        arr->data[index] = val;
        return arr;
    }

    unsigned find(){}
};