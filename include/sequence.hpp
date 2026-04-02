#pragma once

template<typename T>

class sequence{
    virtual T get_first() = 0;
    virtual T get_last() = 0;
    virtual void add(T) = 0;
    virtual T get(unsigned index) = 0;
    virtual unsigned int len() = 0;
    virtual void append(T) = 0;
    virtual T* prepend(T) = 0;
    virtual T* insert(T) = 0;
    virtual T* map() = 0;
};