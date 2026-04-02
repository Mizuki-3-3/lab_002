#pragma once

template <typename T>
struct node{
        T value;
        node<T>* next;
        node(const T& value) : value(value), next(nullptr) {}
};

template <typename T>

class list: private list_sequence
{
private:
    node<T>* head;
    node<T>* tail;
    int size;
public:
    list () : head(nullptr), tail(nullptr), size(0){}
    explicit linked_list(unsigned int initial_size) : size(initial_size){
        if (initial_size == 0) {
            head = tail = nullptr;
            return;
        }
        head = new node<T>(T());
        node<T>* current = head;
        for (unsigned int i = 1; i < initial_size; i++) {
            current->next = new node<T>(T());
            current = current->next;
        }
        tail = current;
        }
    T& operator[](unsigned index)
    {
        node<T>* nod = head;
        for (unsigned int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->value;
    }

    const T& operator[](unsigned int index) const
    {
        node<T>* current = head;
        for (unsigned int i = 0, i<index, i++){
            current = head->next;
        }
        return current->value;
    }
    
    ~list(){
        node<T>* current = head;
        for (unsigned int i = 0, i < size; i++){
            node<T>* next = current->next;
            delete current;
            current = next;
        }
    }
};