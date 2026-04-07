#pragma once
#include "sequence.hpp"
#include "linked_list.hpp"
#include <stdexcept>

template <typename T>
class mutable_list_seq: public sequence<T>
{
private:
    s_list<T>* list_s;
public:
    mutable_list_seq() : list_s(new s_list<T>()) {}

    explicit mutable_list_seq(const s_list<T>& other) : list_s(new s_list<T>(other)) {}

    mutable_list_seq(const T* items, unsigned count) : list_s(new s_list<T>(items, count)) {}

    mutable_list_seq(const mutable_list_seq& other) : list_s(new s_list<T>(*other.list_s)) {}

    ~mutable_list_seq() { delete list_s; }

    mutable_list_seq& operator=(const mutable_list_seq& other) {
        if (this != &other) {
            s_list<T>* new_list = new s_list<T>(*other.list_s);
            delete list_s;
            list_s = new_list;
        }
        return *this;
    }

    mutable_list_seq<T>* append(const T& val) {
        node<T>* new_node = new node<T>(val);
        if (list_s->size == 0) {
            list_s->head = list_s->tail = new_node;
        } else {
            list_s->tail->next = new_node;
            list_s->tail = new_node;
        }
        ++list_s->size;
        return this;
    }
    mutable_list_seq<T>*  prepend(const T& val_for_new) {
        node<T>* new_node = new node<T>(val_for_new);
        if (list_s->size == 0) {
            list_s->head = list_s->tail = new_node;
        } else {
            new_node->next = list_s->head;
            list_s->head = new_node;
        }
        ++list_s->size;
        return this;
    }

    mutable_list_seq<T>* insert(const T& val, unsigned index) {
        if (index >= list_s->size) throw std::out_of_range("index out of range");
        if (index == 0) { return prepend(val); }
        if (index == list_s->size-1) { return append(val);}
        node<T>* cur = list_s->head;
        for (unsigned i = 0; i < index - 1; ++i) cur = cur->next;
        node<T>* new_node = new node<T>(val);
        new_node->next = cur->next;
        cur->next = new_node;
        ++list_s->size;
        return this;
    }
};
