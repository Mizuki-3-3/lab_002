#pragma once
#include "sequence.hpp"
#include "linked_list.hpp"
#include <stdexcept>

template <typename T>
class m_list_sequence: public sequence<T>
{
private:
    s_list<T>* list_s;
public:
    list_sequence() = default;
    explicit list_sequence(const s_list<T>& other) : list_s(other) {}
    explicit list_sequence(const std::initializer_list<T>& init) {
        for (const auto& v : init) append(v);
    }
    s_list<T>* append(const T& val) {
        node<T>* new_node = new node<T>(val);
        if (list_s->size == 0) {
            list_s->head = list_s->tail = new_node;
        } else {
            list_s->tail->next = new_node;
            list_s->tail = new_node;
        }
        ++list_s->size;
        return list_s;
    }
    s_list<T>*  prepend(const T& val_for_new) {
        node<T>* new_node = new node<T>(val_for_new);
        if (list_s->size == 0) {
            list_s->head = list_s->tail = new_node;
        } else {
            new_node->next = list_s->head;
            list_s->head = new_node;
        }
        ++list_s->size;
        return list_s;
    }

    s_list<T>* insert(const T& val, unsigned index) {
        if (index > list_s->size) throw std::out_of_range("index out of range");
        if (index == 0) { prepend(val); return; }
        if (index == list_s->size) { append(val); return; }
        node<T>* cur = list_s->head;
        for (unsigned i = 0; i < index - 1; ++i) cur = cur->next;
        node<T>* new_node = new node<T>(val);
        new_node->next = cur->next;
        cur->next = new_node;
        ++list_s->size;
        return list_s;
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

   template <typename Func>
    auto map(Func f) const -> list_sequence<decltype(f(std::declval<T>()))> {
        using ResultType = decltype(f(std::declval<T>()));
        list_sequence<ResultType> res;
        for (const auto& x : list_s) res.append(f(x));
        return res;
    }

    // 2. where – фильтрация
    template <typename Pred>
    list_sequence<T> where(Pred pred) const {
        list_sequence<T> res;
        for (const auto& x : list_s) if (pred(x)) res.append(x);
        return res;
    }

    // 3. reduce – свёртка (аккумулятор + бинарная операция)
    template <typename Acc, typename BinOp>
    Acc reduce(BinOp op, Acc init) const {
        for (const auto& x : list_s) init = op(init, x);
        return init;
    }

    // 4. zip – объединение двух последовательностей в пары
    template <typename U>
    list_sequence<std::pair<T, U>> zip(const list_sequence<U>& other) const {
        list_sequence<std::pair<T, U>> res;
        auto it1 = list_s.begin();
        auto it2 = other.list_s.begin();
        while (it1 != list_s.end() && it2 != other.list_s.end()) {
            res.append({*it1, *it2});
            ++it1; ++it2;
        }
        return res;
    }

    // 5. flatmap – map + flatten (например, для функции, возвращающей последовательность)
    template <typename Func>
    auto flatmap(Func f) const -> list_sequence<typename decltype(f(std::declval<T>()))::value_type> {
        using InnerSeq = decltype(f(std::declval<T>()));
        using ResultType = typename InnerSeq::value_type;
        list_sequence<ResultType> res;
        for (const auto& x : list_s) {
            InnerSeq sub = f(x);
            for (const auto& y : sub) res.append(y);
        }
        return res;
    }
};
template <typename T>
class im_list_sequence: public sequence<T>
{
private:
    s_list<T>* list_s;
public:
    list_sequence() = default;
    explicit list_sequence(const s_list<T>& other) : list_s(other) {}
    explicit list_sequence(const std::initializer_list<T>& init) {
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
        if (index == 0) { prepend(val); return; }
        if (index == list_s->size) { append(val); return; }
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