#pragma once
#include "sequence.hpp"
#include "linked_list.hpp"

template <typename T>
class list_sequence: private sequence private list
{
private:
    unsigned size;
    list list_;
public:
    T get_first(){return head->value;}

    T get_last(){return tail->value;}

    void add(T val_for_new){
        size++;
        node<T>* temp = new node<T>(T());
        temp->value = 
        tail->next = temp;
        tail = temp; 
    };
    [[nodiscard]] size_t size() const { return size_;}
        
    [[nodiscard]] bool empty() const { return size_ == 0;}

};