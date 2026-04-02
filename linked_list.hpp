#pragma once
#include "list_sequence.hpp"

template <typename T>
struct node{
        T value;
        node<T>* next;
        node(const T& value) : value(value), next(nullptr) {}
};
template <typename T>
class linked_list: private list_sequence
{
private:
    node<T>* head;
    node<T>* tail;
    int size;
public:
    
    linked_list () : head(nullptr), tail(nullptr), size(0){}
    explicit linked_list(unsigned int initial_size) : size(initial_size){
            for (unsigned int i = 0; i< initial_size; i++){
                
            };
        }
    T& operator[](unsigned index)
    {
        node<T>* nod = head;
        for (unsigned i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->value;
    }

    


};
