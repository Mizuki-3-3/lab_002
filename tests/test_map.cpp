#include "array_seq.hpp"
#include "list_seq.hpp"
#include "assertions.hpp"
#include "tests.hpp"

TEST(map_mutable_list_double) {
    int init[] = {1, 2, 3};
    list_seq<Mutability::Mutable, int>* seq = new list_seq<Mutability::Mutable, int>(init, 3);
    seq->map([](int x) { return x * 2; });
    int expected[] = {2, 4, 6};
    assert(check_seq(seq, expected, 3));
    delete seq;
}

TEST(map_immutable_array_square) {
    int init[] = {2, 3};
    array_seq<Mutability::Immutable, int>* seq = new array_seq<Mutability::Immutable, int>(init, 2);
    sequence<int>* new_seq = seq->map([](int x) { return x * x; });
    int expected_orig[] = {2, 3};
    int expected_new[] = {4, 9};
    assert(check_seq(seq, expected_orig, 2));
    assert(check_seq(static_cast<array_seq<Mutability::Immutable, int>*>(new_seq), expected_new, 2));
    delete seq;
    delete new_seq;
}