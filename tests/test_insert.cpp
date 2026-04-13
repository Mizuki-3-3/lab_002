#include "array_seq.hpp"
#include "list_seq.hpp"
#include "assertions.hpp"
#include "tests.hpp"

TEST(insert_mutable_array_middle) {
    int init[] = {1, 2, 3};
    array_seq<Mutability::Mutable, int>* seq = new array_seq<Mutability::Mutable, int>(init, 3);
    seq->insert(99, 1);
    int expected[] = {1, 99, 2, 3};
    assert(check_seq(seq, expected, 4));
    delete seq;
}

TEST(insert_immutable_list_begin) {
    int init[] = {5, 6};
    list_seq<Mutability::Immutable, int>* seq = new list_seq<Mutability::Immutable, int>(init, 2);
    sequence<int>* new_seq = seq->insert(0, 0);
    assert(seq->size() == 2);
    assert(seq->get_first() == 5);
    assert(new_seq->size() == 3);
    assert(new_seq->get_first() == 0);
    assert(new_seq->get(1) == 5);
    assert(new_seq->get(2) == 6);
    delete seq;
    delete new_seq;
}