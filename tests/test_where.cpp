#include "array_seq.hpp"
#include "list_seq.hpp"
#include "assertions.hpp"
#include "tests.hpp"

static bool is_even(int x) { return x % 2 == 0; }
static bool greater_than_two(int x) { return x > 2; }

TEST(where_mutable_array_empty) {
    array_seq<Mutability::Mutable, int>* seq = new array_seq<Mutability::Mutable, int>();
    seq->where(is_even);
    assert(seq->size() == 0);
    delete seq;
}

TEST(where_mutable_array_all_filtered) {
    int init[] = {1,3,5,7};
    array_seq<Mutability::Mutable, int>* seq = new array_seq<Mutability::Mutable, int>(init, 4);
    seq->where(is_even);
    assert(seq->size() == 0);
    delete seq;
}

TEST(where_mutable_array_none_filtered) {
    int init[] = {2,4,6,8};
    array_seq<Mutability::Mutable, int>* seq = new array_seq<Mutability::Mutable, int>(init, 4);
    seq->where(is_even);
    int expected[] = {2,4,6,8};
    assert(check_seq(seq, expected, 4));
    delete seq;
}

TEST(where_mutable_array_partial) {
    int init[] = {1,2,3,4,5,6};
    array_seq<Mutability::Mutable, int>* seq = new array_seq<Mutability::Mutable, int>(init, 6);
    seq->where(is_even);
    int expected[] = {2,4,6};
    assert(check_seq(seq, expected, 3));
    delete seq;
}

TEST(where_immutable_array_empty) {
    array_seq<Mutability::Immutable, int>* seq = new array_seq<Mutability::Immutable, int>();
    sequence<int>* new_seq = seq->where(is_even);
    assert(seq->size() == 0);
    assert(new_seq->size() == 0);
    delete seq;
    delete new_seq;
}

TEST(where_immutable_array_all_filtered) {
    int init[] = {1,3,5};
    array_seq<Mutability::Immutable, int>* seq = new array_seq<Mutability::Immutable, int>(init, 3);
    sequence<int>* new_seq = seq->where(is_even);
    int expected_orig[] = {1,3,5};
    assert(check_seq(seq, expected_orig, 3));
    assert(new_seq->size() == 0);
    delete seq;
    delete new_seq;
}

TEST(where_immutable_array_none_filtered) {
    int init[] = {2,4,6};
    array_seq<Mutability::Immutable, int>* seq = new array_seq<Mutability::Immutable, int>(init, 3);
    sequence<int>* new_seq = seq->where(is_even);
    int expected_orig[] = {2,4,6};
    int expected_new[] = {2,4,6};
    assert(check_seq(seq, expected_orig, 3));
    assert(check_seq(static_cast<array_seq<Mutability::Immutable, int>*>(new_seq), expected_new, 3));
    delete seq;
    delete new_seq;
}

TEST(where_immutable_array_partial) {
    int init[] = {1,2,3,4,5,6};
    array_seq<Mutability::Immutable, int>* seq = new array_seq<Mutability::Immutable, int>(init, 6);
    sequence<int>* new_seq = seq->where(greater_than_two);
    int expected_orig[] = {1,2,3,4,5,6};
    int expected_new[] = {3,4,5,6};
    assert(check_seq(seq, expected_orig, 6));
    assert(check_seq(static_cast<array_seq<Mutability::Immutable, int>*>(new_seq), expected_new, 4));
    delete seq;
    delete new_seq;
}

TEST(where_mutable_list_empty) {
    list_seq<Mutability::Mutable, int>* seq = new list_seq<Mutability::Mutable, int>();
    seq->where(is_even);
    assert(seq->size() == 0);
    delete seq;
}

TEST(where_mutable_list_all_filtered) {
    int init[] = {1,3,5};
    list_seq<Mutability::Mutable, int>* seq = new list_seq<Mutability::Mutable, int>(init, 3);
    seq->where(is_even);
    assert(seq->size() == 0);
    delete seq;
}

TEST(where_mutable_list_none_filtered) {
    int init[] = {2,4,6};
    list_seq<Mutability::Mutable, int>* seq = new list_seq<Mutability::Mutable, int>(init, 3);
    seq->where(is_even);
    int expected[] = {2,4,6};
    assert(check_seq(seq, expected, 3));
    delete seq;
}

TEST(where_mutable_list_partial) {
    int init[] = {1,2,3,4,5,6};
    list_seq<Mutability::Mutable, int>* seq = new list_seq<Mutability::Mutable, int>(init, 6);
    seq->where(is_even);
    int expected[] = {2,4,6};
    assert(check_seq(seq, expected, 3));
    delete seq;
}

TEST(where_immutable_list_empty) {
    list_seq<Mutability::Immutable, int>* seq = new list_seq<Mutability::Immutable, int>();
    sequence<int>* new_seq = seq->where(is_even);
    assert(seq->size() == 0);
    assert(new_seq->size() == 0);
    delete seq;
    delete new_seq;
}

TEST(where_immutable_list_all_filtered) {
    int init[] = {1,3,5};
    list_seq<Mutability::Immutable, int>* seq = new list_seq<Mutability::Immutable, int>(init, 3);
    sequence<int>* new_seq = seq->where(is_even);
    int expected_orig[] = {1,3,5};
    assert(check_seq(seq, expected_orig, 3));
    assert(new_seq->size() == 0);
    delete seq;
    delete new_seq;
}

TEST(where_immutable_list_none_filtered) {
    int init[] = {2,4,6};
    list_seq<Mutability::Immutable, int>* seq = new list_seq<Mutability::Immutable, int>(init, 3);
    sequence<int>* new_seq = seq->where(is_even);
    int expected_orig[] = {2,4,6};
    int expected_new[] = {2,4,6};
    assert(check_seq(seq, expected_orig, 3));
    assert(check_seq(static_cast<list_seq<Mutability::Immutable, int>*>(new_seq), expected_new, 3));
    delete seq;
    delete new_seq;
}

TEST(where_immutable_list_partial) {
    int init[] = {1,2,3,4,5,6};
    list_seq<Mutability::Immutable, int>* seq = new list_seq<Mutability::Immutable, int>(init, 6);
    sequence<int>* new_seq = seq->where(greater_than_two);
    int expected_orig[] = {1,2,3,4,5,6};
    int expected_new[] = {3,4,5,6};
    assert(check_seq(seq, expected_orig, 6));
    assert(check_seq(static_cast<list_seq<Mutability::Immutable, int>*>(new_seq), expected_new, 4));
    delete seq;
    delete new_seq;
}