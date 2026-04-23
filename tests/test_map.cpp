#include "array_seq.hpp"
#include "list_seq.hpp"
#include "assertions.hpp"
#include "tests.hpp"

static int double_it(int x) { return x * 2; }
static int square(int x) { return x * x; }

TEST(map_mutable_array_empty) {
    array_seq<Mutability::Mutable, int>* seq = new array_seq<Mutability::Mutable, int>();
    seq->map(double_it);
    assert(seq->size() == 0);
    delete seq;
}

TEST(map_mutable_array_single) {
    int init[] = {5};
    array_seq<Mutability::Mutable, int>* seq = new array_seq<Mutability::Mutable, int>(init, 1);
    seq->map(double_it);
    int expected[] = {10};
    assert(check_seq(seq, expected, 1));
    delete seq;
}

TEST(map_mutable_array_multiple) {
    int init[] = {1,2,3,4};
    array_seq<Mutability::Mutable, int>* seq = new array_seq<Mutability::Mutable, int>(init, 4);
    seq->map(double_it);
    int expected[] = {2,4,6,8};
    assert(check_seq(seq, expected, 4));
    delete seq;
}

TEST(map_mutable_array_negative) {
    int init[] = {0, -3, 7};
    array_seq<Mutability::Mutable, int>* seq = new array_seq<Mutability::Mutable, int>(init, 3);
    seq->map(double_it);
    int expected[] = {0, -6, 14};
    assert(check_seq(seq, expected, 3));
    delete seq;
}


TEST(map_immutable_array_empty) {
    array_seq<Mutability::Immutable, int>* seq = new array_seq<Mutability::Immutable, int>();
    sequence<int>* new_seq = seq->map(double_it);
    assert(seq->size() == 0);
    assert(new_seq->size() == 0);
    delete seq;
    delete new_seq;
}

TEST(map_immutable_array_single) {
    int init[] = {5};
    array_seq<Mutability::Immutable, int>* seq = new array_seq<Mutability::Immutable, int>(init, 1);
    sequence<int>* new_seq = seq->map(double_it);
    int expected_orig[] = {5};
    int expected_new[] = {10};
    assert(check_seq(seq, expected_orig, 1));
    assert(check_seq(static_cast<array_seq<Mutability::Immutable, int>*>(new_seq), expected_new, 1));
    delete seq;
    delete new_seq;
}

TEST(map_immutable_array_multiple) {
    int init[] = {1,2,3,4};
    array_seq<Mutability::Immutable, int>* seq = new array_seq<Mutability::Immutable, int>(init, 4);
    sequence<int>* new_seq = seq->map(square);
    int expected_orig[] = {1,2,3,4};
    int expected_new[] = {1,4,9,16};
    assert(check_seq(seq, expected_orig, 4));
    assert(check_seq(static_cast<array_seq<Mutability::Immutable, int>*>(new_seq), expected_new, 4));
    delete seq;
    delete new_seq;
}

TEST(map_immutable_array_negative) {
    int init[] = {0, -3, 7};
    array_seq<Mutability::Immutable, int>* seq = new array_seq<Mutability::Immutable, int>(init, 3);
    sequence<int>* new_seq = seq->map(double_it);
    int expected_orig[] = {0, -3, 7};
    int expected_new[] = {0, -6, 14};
    assert(check_seq(seq, expected_orig, 3));
    assert(check_seq(static_cast<array_seq<Mutability::Immutable, int>*>(new_seq), expected_new, 3));
    delete seq;
    delete new_seq;
}


TEST(map_mutable_list_empty) {
    list_seq<Mutability::Mutable, int>* seq = new list_seq<Mutability::Mutable, int>();
    seq->map(double_it);
    assert(seq->size() == 0);
    delete seq;
}

TEST(map_mutable_list_single) {
    int init[] = {5};
    list_seq<Mutability::Mutable, int>* seq = new list_seq<Mutability::Mutable, int>(init, 1);
    seq->map(double_it);
    int expected[] = {10};
    assert(check_seq(seq, expected, 1));
    delete seq;
}

TEST(map_mutable_list_multiple) {
    int init[] = {1,2,3,4};
    list_seq<Mutability::Mutable, int>* seq = new list_seq<Mutability::Mutable, int>(init, 4);
    seq->map(double_it);
    int expected[] = {2,4,6,8};
    assert(check_seq(seq, expected, 4));
    delete seq;
}

TEST(map_mutable_list_negative) {
    int init[] = {0, -3, 7};
    list_seq<Mutability::Mutable, int>* seq = new list_seq<Mutability::Mutable, int>(init, 3);
    seq->map(double_it);
    int expected[] = {0, -6, 14};
    assert(check_seq(seq, expected, 3));
    delete seq;
}


TEST(map_immutable_list_empty) {
    list_seq<Mutability::Immutable, int>* seq = new list_seq<Mutability::Immutable, int>();
    sequence<int>* new_seq = seq->map(double_it);
    assert(seq->size() == 0);
    assert(new_seq->size() == 0);
    delete seq;
    delete new_seq;
}

TEST(map_immutable_list_single) {
    int init[] = {5};
    list_seq<Mutability::Immutable, int>* seq = new list_seq<Mutability::Immutable, int>(init, 1);
    sequence<int>* new_seq = seq->map(double_it);
    int expected_orig[] = {5};
    int expected_new[] = {10};
    assert(check_seq(seq, expected_orig, 1));
    assert(check_seq(static_cast<list_seq<Mutability::Immutable, int>*>(new_seq), expected_new, 1));
    delete seq;
    delete new_seq;
}

TEST(map_immutable_list_multiple) {
    int init[] = {1,2,3,4};
    list_seq<Mutability::Immutable, int>* seq = new list_seq<Mutability::Immutable, int>(init, 4);
    sequence<int>* new_seq = seq->map(square);
    int expected_orig[] = {1,2,3,4};
    int expected_new[] = {1,4,9,16};
    assert(check_seq(seq, expected_orig, 4));
    assert(check_seq(static_cast<list_seq<Mutability::Immutable, int>*>(new_seq), expected_new, 4));
    delete seq;
    delete new_seq;
}

TEST(map_immutable_list_negative) {
    int init[] = {0, -3, 7};
    list_seq<Mutability::Immutable, int>* seq = new list_seq<Mutability::Immutable, int>(init, 3);
    sequence<int>* new_seq = seq->map(double_it);
    int expected_orig[] = {0, -3, 7};
    int expected_new[] = {0, -6, 14};
    assert(check_seq(seq, expected_orig, 3));
    assert(check_seq(static_cast<list_seq<Mutability::Immutable, int>*>(new_seq), expected_new, 3));
    delete seq;
    delete new_seq;
}