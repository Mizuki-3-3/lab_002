#pragma once

#include <stdexcept>
#include <utility>

template<typename T>
class dyn_arr{
private:
    T* data;
    unsigned size;
public:
    class iterator{
        T* current;
    public:
        iterator(T* ptr): current(ptr){}

        iterator& operator++(){
            current++;
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            current++;
            return tmp;
        }

        T& operator*() {return *current;}

        const T& operator*() const {return *current;}

        int operator!=(const iterator& other) const { return current != other.current;}
    
        int operator==(const iterator& other) const { return current == other.current;}
    };

    class const_iterator{
        const T* current;
    public:
        const_iterator(const T* ptr): current(ptr){}

        const_iterator& operator++(){
            current++;
            return *this;
        }

        const_iterator operator++(int){
            const_iterator tmp = *this;
            current++;
            return tmp;
        }

        const T& operator*() const {return *current;}

        int operator!=(const const_iterator& other) const { return current != other.current;}
    
        int operator==(const const_iterator& other) const { return current == other.current;}
    };
    dyn_arr () : data(nullptr), size(0) {}
    explicit dyn_arr(unsigned initial_size): data(new T[initial_size]), size(initial_size) {
        for (unsigned i = 0; i < initial_size; i++) {
            data[i] = T();  // или nullptr для указателей
        }
    }
    dyn_arr(T* items, unsigned initial_size): size(initial_size), data(new T[sizeof(items)/sizeof(items[0])]){
        if (sizeof(data)/sizeof(data[0])>initial_size){
            for (unsigned i = 0; i<initial_size; i++){
                data[i] = items[i];
            }
            for (unsigned i = initial_size; i<sizeof(data)/sizeof(data[0]); i++){
                data[i] = T();
            }
        };
        for (unsigned i = 0; i < initial_size; ++i) data[i] = items[i];
    }
    dyn_arr(const dyn_arr& other) : size(other.size), data(new T[other.size]){
        for (unsigned i = 0; i < size; ++i) data[i] = other.data[i];
    }
    ~dyn_arr() {
        delete[] data;
    }

    T& operator[](unsigned index){
    if (index >= size) throw std::out_of_range("Index out of range");
    return data[index];
    }

    const T& operator[](unsigned index) const{
        if (index >= size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    iterator begin(){return iterator(data);}

    const_iterator begin() const {return const_iterator(data);}

    iterator end(){return iterator(data+size);}

    const_iterator end() const {return const_iterator(data+size);}

    dyn_arr& operator=(const dyn_arr&) = delete;

    dyn_arr& operator=(dyn_arr other){
        std::swap(data, other.data);
        std::swap(size, other.size);
        return *this;
    }

    T* data() { return data;}

    const T* data() const { return data;}
        
    unsigned len() const { return size;}

    void resize(unsigned new_size) {
        T* new_data = new T[new_size];
        for (unsigned i = 0; i < new_size; ++i) {
            if (i < size) new_data[i] = data[i];
            else new_data[i] = T();
        }
        delete[] data;
        data = new_data;
        size = new_size;
    }
    template <typename U> friend class mutable_array_seq;
    template <typename U> friend class immutable_array_seq;
};
