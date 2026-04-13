#include "array_seq.hpp"
#include "list_seq.hpp"
#include "assertions.hpp"
#include "tests.hpp"

TEST(append_mutable_array_nonempty) {
    int init[] = {1, 2, 3};
    array_seq<Mutability::Mutable, int>* seq = new array_seq<Mutability::Mutable, int>(init, 3);
    seq->append(4);
    assert(seq->size() == 4);
    assert((*seq)[3] == 4);
    delete seq;
}

TEST(append_immutable_list_empty) {
    list_seq<Mutability::Immutable, int>* seq = new list_seq<Mutability::Immutable, int>();
    assert(seq->size() == 0);
    sequence<int>* new_seq = seq->append(42);
    assert(seq->size() == 0);               
    assert(new_seq->size() == 1);
    assert(new_seq->get_first() == 42);
    delete seq;
    delete new_seq;
}