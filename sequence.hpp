#pragma once

template<typename T>

class sequence{
    virtual T get_first();
    virtual T get_last();
    virtual T* add(T);
    virtual T get(unsigned index);
    virtual unsigned int get_length();
    virtual T* append(T);
    virtual T* prepend(T);
    virtual T* insert(T);
    virtual T* map();

};