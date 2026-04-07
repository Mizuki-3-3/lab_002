#pragma once
#include "sequence.hpp"
#include "linked_list.hpp"
#include <stdexcept>

template <typename T>
class im_list_sequence: public sequence<T>
{
private:
    s_list<T>* list_s;
public:
    im_list_sequence() = default;
    explicit im_list_sequence(const s_list<T>& other) : list_s(other) {}
    explicit im_list_sequence(const std::initializer_list<T>& init) {
        for (const auto& v : init) append(v);
    }

    s_list<T>*  append(const T& val) {
        s_list<T>* new_l = new s_list<T>(*list_s);
        node<T>* new_node = new node<T>(val);
        if (new_l->size == 0) {
            new_l->head = new_l->tail = new_node;
        } else {
            new_l->tail->next = new_node;
            new_l->tail = new_node;
        }
        ++new_l->size;
        return new_l;
    }
    s_list<T>*  prepend(const T& val_for_new) {
        s_list<T>* new_l = new s_list<T>(*list_s);
        node<T>* new_node = new node<T>(val_for_new);
        if (new_l->size == 0) {
            new_l->head = new_l->tail = new_node;
        } else {
            new_node->next = new_l->head;
            new_l->head = new_node;
        }
        ++new_l->size;
        return new_l;
    }

    s_list<T>* insert(const T& val, unsigned index) {
        if (index > list_s->size) throw std::out_of_range("index out of range");
        if (index == 0) { return prepend(val); }
        if (index == list_s->size) { return append(val);  }
        node<T>* cur = list_s->head;

        for (unsigned i = 0; i < index - 1; ++i) cur = cur->next;
        node<T>* new_node = new node<T>(val);
        new_node->next = cur->next;
        cur->next = new_node;
        ++list_s->size;
        return new_l;
    }
    unsigned find(T wanted){
        node<T>* current = list_s->head;
        for (unsigned i = 0; i < list_s->size();i++){
            if (current->value == wanted){
                return i;
            }
            current = current->next;
        }
        throw std::out_of_range("not_found")
    }
};