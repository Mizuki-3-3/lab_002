#pragma once
#include "sequence.hpp"
#include "linked_list.hpp"
#include <stdexcept>

template <typename T>
class immutable_list_seq: public sequence<T>
{
private:
    s_list<T>* list_s;
public:
    immutable_list_seq() : list_s(new s_list<T>()) {}

    explicit immutable_list_seq(const s_list<T>& other) : list_s(new s_list<T>(other)) {}

    immutable_list_seq(const T* items, unsigned count) : list_s(new s_list<T>(items, count)) {}

    immutable_list_seq(const immutable_list_seq& other) : list_s(new s_list<T>(*other.list_s)) {}

    ~immutable_list_seq() { delete list_s; }

    immutable_list_seq& operator=(const immutable_list_seq& other) {
        if (this != &other) {
            s_list<T>* new_list = new s_list<T>(*other.list_s);
            delete list_s;
            list_s = new_list;
        }
        return *this;
    }

    immutable_list_seq<T>*  append(const T& val) {
        immutable_list_seq<T>* new_l = new immutable_list_seq<T>(*list_s);
        node<T>* new_node = new node<T>(val);
        if (list_s->size == 0) {
            new_l->list_s->head = new_l->list_s->tail = new_node;
        } else {
            new_l->list_s->tail->next = new_node;
            new_l->list_s->tail = new_node;
        }
        new_l->list_s->size++;
        return new_l;
    }
    immutable_list_seq<T>*  prepend(const T& val) {
        immutable_list_seq<T>* new_l = new immutable_list_seq<T>(*list_s);
        node<T>* new_node = new node<T>(val);
        if (list_s->size == 0) {
            new_l->list_s->head = new_l->list_s->tail = new_node;
        } else {
            new_node->next = new_l->list_s->head;
            new_l->list_s->head = new_node;
        }
        new_l->list_s->size++;
        return new_l;
    }

    immutable_list_seq<T>* insert(const T& val, unsigned index) {
        if (index > list_s->size) throw std::out_of_range("index out of range");
        if (index == 0) { return prepend(val); }
        if (index == list_s->size) { return append(val);  }
        immutable_list_seq<T>* new_l = new immutable_list_seq<T>(*list_s);
        node<T>* curr = new_l->list_s->head;
        for (unsigned i = 0; i < index - 1; ++i) curr = curr->next;
        node<T>* new_node = new node<T>(val);
        new_node->next = curr->next;
        curr->next = new_node;
        new_l->list_s->size++;
        return new_l;
    }
};