#include "array_seq.hpp"
#include "list_seq.hpp"
#include "assertions.hpp"
#include "tests.hpp"

TEST(prepend_mutable_array_nonempty) {
    int init[] = {1, 2, 3};
    array_seq<Mutability::Mutable, int>* seq = new array_seq<Mutability::Mutable, int>(init, 3);
    seq->prepend(26);
    assert(seq->size() == 4);
    assert(seq->get_first() == 26);
    delete seq;
}

TEST(prepend_immmutable_array_nonempty) {
    int init[] = {1, 2, 3};
    array_seq<Mutability::Immutable, int>* seq = new array_seq<Mutability::Immutable, int>(init, 3);
    sequence<int>* new_seq = new  array_seq<Mutability::Immutable, int>(init, 3);
    new_seq = seq->prepend(4);
    assert(seq->size() == 3);
    assert(new_seq->size() == 4);
    assert(new_seq->get_first() == 4);
    delete seq;
    delete new_seq;
}

TEST(prepend_mutable_list_nonempty){
    int init[] = {1, 2, 3};
    list_seq<Mutability::Mutable, int>* seq = new list_seq<Mutability::Mutable, int>(init, 3);
    seq->prepend(26);
    assert(seq->size() == 4);
    assert(seq->get_first() == 26);
    delete seq;
}

TEST(prepend_immmutable_list_nonempty){
    int init[] = {1, 2, 3};
    list_seq<Mutability::Immutable, int>* seq = new list_seq<Mutability::Immutable, int>(init, 3);
    sequence<int>* new_seq = new list_seq<Mutability::Immutable, int>();
    new_seq = seq->prepend(26);
    assert(new_seq->size() == 4);
    assert(new_seq->get_first() == 26);
    delete seq;
    delete new_seq;
}

TEST(prepend_mutable_array_empty){
    array_seq<Mutability::Mutable, int>* seq = new array_seq<Mutability::Mutable, int>();
    assert(seq->size() == 0);
    seq->prepend(26);
    assert(seq->size() == 1);
    assert(seq->get_first() == 26 && seq->get_last() == 26);
    delete seq;
}

TEST(prepend_immmutable_array_empty){
    array_seq<Mutability::Immutable, int>* seq = new array_seq<Mutability::Immutable, int>();
    sequence<int>* new_seq = new array_seq<Mutability::Immutable, int>();
    new_seq = seq->prepend(26);
    assert(seq->size() == 0);
    assert(new_seq->size() == 1);
    assert(new_seq->get_first() == 26 && new_seq->get_last() == 26);
    delete seq;
    delete new_seq;
}

TEST(prepend_mutable_list_empty) {
    list_seq<Mutability::Mutable, int>* seq = new list_seq<Mutability::Mutable, int>();
    assert(seq->size() == 0);
    seq->prepend(26);
    assert(seq->size() == 1);
    assert(seq->get_first() == 26 && seq->get_last() == 26);
    delete seq;
}

TEST(prepend_immutable_list_empty) {
    list_seq<Mutability::Immutable, int>* seq = new list_seq<Mutability::Immutable, int>();
    sequence<int>* new_seq = seq->prepend(42);
    assert(seq->size() == 0);               
    assert(new_seq->size() == 1);
    assert(new_seq->get_first() == 42 && new_seq->get_last() == 42);
    delete seq;
    delete new_seq;
}

TEST(prepend_mutable_array_one_element){
    int init[] = {32};
    array_seq<Mutability::Mutable, int>* seq = new array_seq<Mutability::Mutable, int>(init, 1);
    assert(seq->size() == 1);
    seq->prepend(26);
    assert(seq->size() == 2);
    assert(seq->get_first() == 26);
    assert(seq->get_last() == 32);
    delete seq;
}

TEST(prepend_immmutable_array_one_element){
    int init[] = {32};
    array_seq<Mutability::Immutable, int>* seq = new array_seq<Mutability::Immutable, int>(init, 1);
    sequence<int>* new_seq = new array_seq<Mutability::Immutable, int>();
    new_seq = seq->prepend(26);
    assert(seq->size() == 1);
    assert(new_seq->size() == 2);
    assert(new_seq->get_first() ==26);
    assert(new_seq->get_last() == 32);
    delete seq;
    delete new_seq;
}

TEST(prepend_mutable_list_one_element) {
    int init[] = {32};
    list_seq<Mutability::Mutable, int>* seq = new list_seq<Mutability::Mutable, int>(init, 1);
    assert(seq->size() == 1);
    seq->prepend(42);
    assert(seq->size() == 2);
    assert(seq->get_first() == 42);
    assert(seq->get_last() == 32);
    delete seq;
}

TEST(prepend_immutable_list_one_element) {
    int init[] = {32};
    list_seq<Mutability::Immutable, int>* seq = new list_seq<Mutability::Immutable, int>(init, 1);
    sequence<int>* new_seq = seq->prepend(42);
    assert(seq->size() == 1);               
    assert(new_seq->size() == 2);
    assert(new_seq->get_first() == 42);
    assert(new_seq->get_last() == 32);
    delete seq;
    delete new_seq;
}
