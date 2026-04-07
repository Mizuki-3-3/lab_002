#pragma once

#include <stdexcept>
#include <utility>

template <typename T>
struct node{
        T value;
        node<T>* next;
        node(const T& value) : value(value), next(nullptr) {}
};

template <typename T>
class s_list
{
private:
    node<T>* head;
    node<T>* tail;
    int size;
public:
    class iterator{
        node<T>* current;
    public:
        iterator(node<T>* ptr): current(ptr){}
        iterator& operator++(){
            if (current) current = current->next;
            return *this;
        }
        T& operator*(){return current->value;}
        const T& operator*() const {return current->value;}
        int operator!=(const iterator& other) const{ return current!=other.current;}
        int operator==(const iterator& other) const{ return current == other.current;}
    };
    class const_iterator{
        const node<T>* current;
    public:
        const_iterator(const node<T>* ptr): current(ptr){}
        const_iterator& operator++(){
            if (current) current = current->next;
            return *this;
        }
        const T& operator*() const {return current->value;}
        int operator!=(const const_iterator& other) const{ return current!=other.current;}
        int operator==(const const_iterator& other) const{ return current == other.current;}
    };
    s_list () : head(nullptr), tail(nullptr), size(0){}

    explicit s_list(unsigned initial_size) : size(initial_size){
        if (initial_size == 0) {
            head = nullptr;
            tail = nullptr;
            return;
        }
        head = new node<T>(T());
        node<T>* current = head;
        for (unsigned int i = 1; i < initial_size; i++) {
            current->next = new node<T>(T());
            current = current->next;
        }
        tail = current;
        tail->next = nullptr;
    }
    s_list (T* data, unsigned initial_size): size(initial_size){
        if (!initial_size){
            head = tail = nullptr;
            return;
        }
        head = new node<T>(data[0]);
        node<T>* current = head;
        for (unsigned int i = 1; i < initial_size; i++) {
            current->next = new node<T>(data[i]);
            current = current->next;
        }
        tail = current;
        tail->next = nullptr;
    }
    s_list(const s_list& other): size(other.size){
        if (!other.head){
            head = tail = nullptr;
            return;
        }
        head = new node<T>(other.head->value);
        node<T>* current = head;
        node<T>* other_current = other.head->next;
        while (other_current){
            current->next = new node<T>(other_current->value);
            current = current->next;
            other_current = other_current->next;
        }
        tail = current;
        tail->next = nullptr;
    }
    T& operator[](unsigned index)
    {
        if (index >= size) throw std::out_of_range("Index out of range");
        node<T>* current = head;
        for (unsigned int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->value;
    }

    const T& operator[](unsigned int index) const
    {
        if (index >= size) throw std::out_of_range("Index out of range");
        node<T>* current = head;
        for (unsigned int i = 0; i<index; i++){
            current = current->next;
        }
        return current->value;
    }

    s_list& operator=(s_list other){
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(size, other.size);
        return *this;
    }

    s_list operator+(const s_list& right) const {
        if (!size && !right.size()) {return s_list();}
        s_list<T> new_l(right.size() + size);
        node<T>* current = new_l.head;
        node<T>* old_current = head;
        while(old_current){
            current->value = old_current->value;
            current = current->next;
            old_current = old_current->next;
        }
        old_current = right.head;
        while(old_current){
            current->value = old_current->value;
            current = current->next;
            old_current = old_current->next;
        }
        return new_l;
    }

    
    ~s_list(){
        node<T>* current = head;
        while (current){
            node<T>* next = current->next;
            delete current;
            current = next;
        }
    }

    unsigned len() const { return size;}
    T get_first() {
        if (size == 0) throw std::out_of_range("list is empty");
        return head->value;
    }

    T get_last() {
        if (size == 0) throw std::out_of_range("list is empty");
        return tail->value;
    }

    const T get_first() const {
        if (size == 0) throw std::out_of_range("list is empty");
        return head->value;
    }

    const T get_last() const {
        if (size == 0) throw std::out_of_range("list is empty");
        return tail->value;
    }

    iterator begin(){return iterator(head);}

    iterator end(){return iterator(nullptr);}

    const_iterator begin() const {return const_iterator(head);}

    const_iterator end() const {return const_iterator(nullptr);}

    s_list<T> slice(unsigned start, unsigned end) const {
        if (start > end || end > size) throw std::out_of_range("slice: invalid indices");
        s_list<T> result{end-start};
        node<T>* cur = head;
        node<T>* cur_r = result.head;
        for (unsigned i = 0; i < start; ++i) cur = cur->next;
        for (unsigned i = start; i < end; ++i) {
            cur_r->value = cur->value;
            cur_r = cur_r->next;
            cur = cur->next;
        }
        return result;
    }
    template <typename U> friend class mutable_list_seq;
    template <typename U> friend class immutable_list_seq;
};