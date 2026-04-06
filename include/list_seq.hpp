#pragma once
#include "sequence.hpp"
#include "linked_list.hpp"

template <typename T>
class list_sequence: private sequence, private s_list
{
private:
    s_list<T> list_s;
public:
    void append(T val_for_new){
        list_s.size++;
        list_s.tail->next = new node<T>(val_for_new);
        list_s.tail = list_s.tail->next;
    }
    void prepend(T val_for_new){
        list_s.size++;
        list_s.tail->next = new node<T>(val_for_new);
        list_s.tail->next->next = list_s.head;
        list_s.head = list_s.tail->next; //закольцевали и разорвали
        list_s.tail->next = nullptr;
    }

    void insert(T value, unsigned index){
        node<T>* current = list_s.head;
        for (unsigned i = 0; i < index-1; i++){current = current->next;}
        node<T>* temp = current->next;
        current->next = new node<T>(T());
        current = current->next;
        current->value = value;
        current->next = temp;
    }
    unsigned find(T wanted){
        node<T>* current = list_s.head;
        for (unsigned i = 0; i < list_s.size();i++){
            if (current->value == wanted){
                return i;
            }
            current = current->next
        }
        throw std::out_of_range("not_found")
    }
};