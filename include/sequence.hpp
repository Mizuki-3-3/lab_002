#pragma once
#include "array_seq.hpp"
#include "list_seq.hpp"
template<typename T>

class sequence:public array_seq<T>, public list_seq<T>
{
private:
    mutable_array_seq<T> m_arr;
    immutable_array_seq<T> im_arr;
    mutable_list_seq<T> m_list;
    immutable_list_seq<T> im_list;
public:
    virtual T get_first() = 0;
    virtual T get_last() = 0;
    virtual T* append(T) = 0;
    virtual T* prepend(T) = 0;
    virtual T* insert(T, unsigned) = 0;
    virtual T from(T) = 0;
    virtual T* map() = 0;
    virtual T* flatmap() = 0;
    virtual T* reduce() = 0;
    virtual unsigned find(T) = 0;
    virtual zip() = 0;
};