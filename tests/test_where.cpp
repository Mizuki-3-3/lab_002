#include "array_seq.hpp"
#include "list_seq.hpp"
#include "assertions.hpp"
#include "tests.hpp"

TEST(where_mutable_array_even) {
    int init[] = {1, 2, 3, 4};
    array_seq<Mutability::Mutable, int>* seq = new array_seq<Mutability::Mutable, int>(init, 4);
    seq->where([](int x) { return x % 2 == 0; });
    int expected[] = {2, 4};
    assert(check_seq(seq, expected, 2));
    delete seq;
}

TEST(where_immutable_list_greater_than_two) {
    int init[] = {1, 3, 5, 2};
    list_seq<Mutability::Immutable, int>* seq = new list_seq<Mutability::Immutable, int>(init, 4);
    sequence<int>* new_seq = seq->where([](int x) { return x > 2; });
    int expected_orig[] = {1, 3, 5, 2};
    int expected_new[] = {3, 5};
    assert(check_seq(seq, expected_orig, 4));
    assert(check_seq(static_cast<list_seq<Mutability::Immutable, int>*>(new_seq), expected_new, 2));
    delete seq;
    delete new_seq;
}