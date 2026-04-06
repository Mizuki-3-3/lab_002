#pragma once

template<typename T>

class sequence{
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