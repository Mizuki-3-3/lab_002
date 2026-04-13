#include "list_seq.hpp"
#include "errors.hpp"

template<Mutability M, typename T>
list_seq<M,T>::list_seq() : list(new s_list<T>()) {
    if (list == nullptr) THROW(ERR_MEMORY);
}

template<Mutability M, typename T>
list_seq<M,T>::list_seq(const s_list<T>& other) : list(new s_list<T>(other)) {
    if (list == nullptr) THROW(ERR_MEMORY);
}

template<Mutability M, typename T>
list_seq<M,T>::list_seq(const T* items, unsigned count) : list(new s_list<T>(items, count)) {
    if (list == nullptr) THROW(ERR_MEMORY);
}

template<Mutability M, typename T>
list_seq<M,T>::list_seq(const list_seq& other) : list(new s_list<T>(*other.list)) {
    if (list == nullptr) THROW(ERR_MEMORY);
}

template<Mutability M, typename T>
list_seq<M,T>::~list_seq() { delete list; }

template<Mutability M, typename T>
list_seq<M,T>& list_seq<M,T>::operator=(const list_seq& other) {
    if (this != &other) {
        s_list<T>* new_list = new s_list<T>(*other.list);
        if (new_list == nullptr) THROW(ERR_MEMORY);
        delete list;
        list = new_list;
    }
    return *this;
}

template<Mutability M, typename T>
T list_seq<M,T>::get_first() const {
    return list->get_first();
}

template<Mutability M, typename T>
T list_seq<M,T>::get_last() const {
    return list->get_last();
}

template<Mutability M, typename T>
T list_seq<M,T>::get(unsigned index) const {
    return (*list)[index];
}

template<Mutability M, typename T>
unsigned list_seq<M,T>::size() const {
    return list->len();
}

template<Mutability M, typename T>
sequence<T>* list_seq<M,T>::append(const T& item) {
    if constexpr (M == Mutability::Mutable) {
        node<T>* new_node = new node<T>(item);
        if (new_node == nullptr) THROW(ERR_MEMORY);
        if (list->len() == 0) {
            list->head = list->tail = new_node;
        } else {
            list->tail->next = new_node;
            list->tail = new_node;
        }
        ++list->size;
        return this;
    } else {
        list_seq<Mutability::Immutable, T>* new_l =
            new list_seq<Mutability::Immutable, T>(*list);
        if (new_l == nullptr) THROW(ERR_MEMORY);
        node<T>* new_node = new node<T>(item);
        if (new_node == nullptr) THROW(ERR_MEMORY);
        if (new_l->list->len() == 0) {
            new_l->list->head = new_l->list->tail = new_node;
        } else {
            new_l->list->tail->next = new_node;
            new_l->list->tail = new_node;
        }
        ++new_l->list->size;
        return new_l;
    }
}

template<Mutability M, typename T>
sequence<T>* list_seq<M,T>::prepend(const T& item) {
    if constexpr (M == Mutability::Mutable) {
        node<T>* new_node = new node<T>(item);
        if (new_node == nullptr) THROW(ERR_MEMORY);
        if (list->len() == 0) {
            list->head = list->tail = new_node;
        } else {
            new_node->next = list->head;
            list->head = new_node;
        }
        ++list->size;
        return this;
    } else {
        list_seq<Mutability::Immutable, T>* new_l =
            new list_seq<Mutability::Immutable, T>(*list);
        if (new_l == nullptr) THROW(ERR_MEMORY);
        node<T>* new_node = new node<T>(item);
        if (new_node == nullptr) THROW(ERR_MEMORY);
        if (new_l->list->len() == 0) {
            new_l->list->head = new_l->list->tail = new_node;
        } else {
            new_node->next = new_l->list->head;
            new_l->list->head = new_node;
        }
        ++new_l->list->size;
        return new_l;
    }
}

template<Mutability M, typename T>
sequence<T>* list_seq<M,T>::insert(const T& item, unsigned index) {
    if (index > list->len()) THROW(ERR_INCORRECT_INDEX);
    if (index == 0) return prepend(item);
    if (index == list->len()) return append(item);

    if constexpr (M == Mutability::Mutable) {
        node<T>* cur = list->head;
        for (unsigned i = 0; i < index - 1; ++i) cur = cur->next;
        node<T>* new_node = new node<T>(item);
        if (new_node == nullptr) THROW(ERR_MEMORY);
        new_node->next = cur->next;
        cur->next = new_node;
        ++list->size;
        return this;
    } else {
        list_seq<Mutability::Immutable, T>* new_l =
            new list_seq<Mutability::Immutable, T>(*list);
        if (new_l == nullptr) THROW(ERR_MEMORY);
        node<T>* cur = new_l->list->head;
        for (unsigned i = 0; i < index - 1; ++i) cur = cur->next;
        node<T>* new_node = new node<T>(item);
        if (new_node == nullptr) THROW(ERR_MEMORY);
        new_node->next = cur->next;
        cur->next = new_node;
        ++new_l->list->size;
        return new_l;
    }
}

template<Mutability M, typename T>
sequence<T>* list_seq<M,T>::concat(sequence<T>* other) {
    if (other == nullptr) THROW(ERR_NULL);
    list_seq<Mutability::Immutable, T>* result =
        new list_seq<Mutability::Immutable, T>(*list);
    if (result == nullptr) THROW(ERR_MEMORY);
    for (unsigned i = 0; i < other->size(); ++i) {
        result = static_cast<list_seq<Mutability::Immutable, T>*>(
            result->append(other->get(i))
        );
    }
    return result;
}

template<Mutability M, typename T>
sequence<T>* list_seq<M,T>::get_subsequence(unsigned start, unsigned end) const {
    if (start > end || end > size()) THROW(ERR_INCORRECT_INDEX);
    list_seq<Mutability::Immutable, T>* sub =
        new list_seq<Mutability::Immutable, T>();
    if (sub == nullptr) THROW(ERR_MEMORY);
    for (unsigned i = start; i < end; ++i) {
        sub = static_cast<list_seq<Mutability::Immutable, T>*>(
            sub->append((*list)[i])
        );
    }
    return sub;
}

template<Mutability M, typename T>
unsigned list_seq<M,T>::find(const T& value) const {
    unsigned idx = 0;
    for (auto it = list->begin(); it != list->end(); ++it, ++idx) {
        if (*it == value) return idx;
    }
    THROW(ERR_INCORRECT_INDEX);
    return 0;
}

template<Mutability M, typename T>
T& list_seq<M,T>::operator[](unsigned index) {
    return (*list)[index];
}

template<Mutability M, typename T>
const T& list_seq<M,T>::operator[](unsigned index) const {
    return (*list)[index];
}

template<Mutability M, typename T>
template <typename Func>
list_seq<M,T>* list_seq<M,T>::map(Func f) {
    if constexpr (M == Mutability::Mutable) {
        for (auto& x : *list) x = f(x);
        return this;
    } else {
        list_seq<Mutability::Immutable, T>* new_l =
            new list_seq<Mutability::Immutable, T>(*list);
        if (new_l == nullptr) THROW(ERR_MEMORY);
        for (auto& x : *(new_l->list)) x = f(x);
        return new_l;
    }
}

template<Mutability M, typename T>
template <typename Func>
list_seq<M,T>* list_seq<M,T>::where(Func f) {
    if constexpr (M == Mutability::Mutable) {
        s_list<T>* new_list = new s_list<T>();
        if (new_list == nullptr) THROW(ERR_MEMORY);
        for (auto& x : *list) {
            if (f(x)) {
                node<T>* new_node = new node<T>(x);
                if (new_node == nullptr) THROW(ERR_MEMORY);
                if (new_list->len() == 0) {
                    new_list->head = new_list->tail = new_node;
                } else {
                    new_list->tail->next = new_node;
                    new_list->tail = new_node;
                }
                ++new_list->size;
            }
        }
        delete list;
        list = new_list;
        return this;
    } else {
        list_seq<Mutability::Immutable, T>* new_l =
            new list_seq<Mutability::Immutable, T>();
        if (new_l == nullptr) THROW(ERR_MEMORY);
        for (auto& x : *list) {
            if (f(x)) {
                new_l = static_cast<list_seq<Mutability::Immutable, T>*>(
                    new_l->append(x)
                );
            }
        }
        return new_l;
    }
}

template<Mutability M, typename T>
template <typename Func, typename U>
U list_seq<M,T>::reduce(Func f, U initial) const {
    if (list->len() == 0) THROW(ERR_INCORRECT_INDEX);
    U acc = f(initial, (*list)[0]);
    for (unsigned i = 1; i < list->len(); ++i) {
        acc = f(acc, (*list)[i]);
    }
    return acc;
}