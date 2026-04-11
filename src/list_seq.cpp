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
list_seq<M, T>* list_seq<M,T>::append(const T& val) {
    if constexpr (M == Mutability::Mutable) {
        node<T>* new_node = new node<T>(val);
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
        node<T>* new_node = new node<T>(val);
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
T& list_seq<M,T>::operator[](unsigned index) {
    if (index >= list->len()) THROW(ERR_INCORRECT_INDEX);
    return (*list)[index];
}

template<Mutability M, typename T>
const T& list_seq<M,T>::operator[](unsigned index) const {
    if (index >= list->len()) THROW(ERR_INCORRECT_INDEX);
    return (*list)[index];
}

template<Mutability M, typename T>
list_seq<M, T>* list_seq<M,T>::prepend(const T& val) {
    if constexpr (M == Mutability::Mutable) {
        node<T>* new_node = new node<T>(val);
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
        node<T>* new_node = new node<T>(val);
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
list_seq<M, T>* list_seq<M,T>::insert(const T& val, unsigned index) {
    if (index > list->len()) THROW(ERR_INCORRECT_INDEX);
    if (index == 0) return prepend(val);
    if (index == list->len()) return append(val);

    if constexpr (M == Mutability::Mutable) {
        node<T>* cur = list->head;
        for (unsigned i = 0; i < index - 1; ++i) cur = cur->next;
        node<T>* new_node = new node<T>(val);
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
        node<T>* new_node = new node<T>(val);
        if (new_node == nullptr) THROW(ERR_MEMORY);
        new_node->next = cur->next;
        cur->next = new_node;
        ++new_l->list->size;
        return new_l;
    }
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
            if (f(x)) new_list->append(x);
        }
        delete list;
        list = new_list;
        return this;
    } else {
        list_seq<Mutability::Immutable, T>* new_l =
            new list_seq<Mutability::Immutable, T>();
        if (new_l == nullptr) THROW(ERR_MEMORY);
        for (auto& x : *list) {
            if (f(x)) new_l->append(x);
        }
        return new_l;
    }
}

template<Mutability M, typename T>
template <typename Func>
auto list_seq<M,T>::reduce(Func f, const T& initial) const {
    if (list->len() == 0) THROW(ERR_INCORRECT_INDEX);
    auto result = f((*list)[0], initial);
    for (unsigned i = 1; i < list->len(); ++i) {
        result = f((*list)[i], result);
    }
    return result;
}

template<Mutability M, typename T>
unsigned list_seq<M,T>::len() const { return list->len(); }

template<Mutability M, typename T>
auto list_seq<M,T>::begin() { return list->begin(); }

template<Mutability M, typename T>
auto list_seq<M,T>::end() { return list->end(); }

template<Mutability M, typename T>
auto list_seq<M,T>::begin() const { return list->begin(); }

template<Mutability M, typename T>
auto list_seq<M,T>::end() const { return list->end(); }