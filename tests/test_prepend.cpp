#include "array_seq.hpp"
#include "list_seq.hpp"
#include "assertions.hpp"
#include "tests.hpp"

TEST(prepend_mutable_list_nonempty) {
    int init[] = {10, 20};
    list_seq<Mutability::Mutable, int>* seq = new list_seq<Mutability::Mutable, int>(init, 2);
    seq->prepend(5);
    assert(seq->size() == 3);
    assert(seq->get_first() == 5);
    assert((*seq)[1] == 10);
    delete seq;
}

TEST(prepend_immutable_array_nonempty) {
    int init[] = {2, 3};
    array_seq<Mutability::Immutable, int>* seq = new array_seq<Mutability::Immutable, int>(init, 2);
    sequence<int>* new_seq = seq->prepend(1);
    assert(seq->size() == 2);
    assert(seq->get_first() == 2);
    assert(new_seq->size() == 3);
    assert(new_seq->get_first() == 1);
    assert(new_seq->get(1) == 2);
    assert(new_seq->get(2) == 3);
    delete seq;
    delete new_seq;
}