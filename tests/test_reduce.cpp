#include "array_seq.hpp"
#include "list_seq.hpp"
#include "assertions.hpp"
#include "tests.hpp"
#include "errors.hpp"

static int sum(int acc, int x) { return acc + x; }
static int mult(int acc, int x) { return acc * x; }
static int subtract(int acc, int x) { return acc - x; }

TEST(reduce_mutable_array_sum) {
    int init[] = {1,2,3,4};
    array_seq<Mutability::Mutable, int>* seq = new array_seq<Mutability::Mutable, int>(init, 4);
    int result = seq->reduce(sum, 0);
    assert(result == 10);
    delete seq;
}

TEST(reduce_mutable_array_mult) {
    int init[] = {2,3,4};
    array_seq<Mutability::Mutable, int>* seq = new array_seq<Mutability::Mutable, int>(init, 3);
    int result = seq->reduce(mult, 1);
    assert(result == 24);
    delete seq;
}

TEST(reduce_mutable_array_with_initial) {
    int init[] = {1,2,3};
    array_seq<Mutability::Mutable, int>* seq = new array_seq<Mutability::Mutable, int>(init, 3);
    int result = seq->reduce(sum, 10);
    assert(result == 16);
    delete seq;
}

TEST(reduce_mutable_array_negative) {
    int init[] = {-1, -2, -3};
    array_seq<Mutability::Mutable, int>* seq = new array_seq<Mutability::Mutable, int>(init, 3);
    int result = seq->reduce(sum, 0);
    assert(result == -6);
    delete seq;
}

TEST(reduce_mutable_array_noncommutative) {
    int init[] = {1,2,3};
    array_seq<Mutability::Mutable, int>* seq = new array_seq<Mutability::Mutable, int>(init, 3);
    int result = seq->reduce(subtract, 0);
    assert(result == -6);
    delete seq;
}

TEST(reduce_immutable_array_sum) {
    int init[] = {1,2,3,4};
    array_seq<Mutability::Immutable, int>* seq = new array_seq<Mutability::Immutable, int>(init, 4);
    int result = seq->reduce(sum, 0);
    assert(result == 10);
    delete seq;
}

TEST(reduce_immutable_array_mult) {
    int init[] = {2,3,4};
    array_seq<Mutability::Immutable, int>* seq = new array_seq<Mutability::Immutable, int>(init, 3);
    int result = seq->reduce(mult, 1);
    assert(result == 24);
    delete seq;
}

TEST(reduce_immutable_array_with_initial) {
    int init[] = {1,2,3};
    array_seq<Mutability::Immutable, int>* seq = new array_seq<Mutability::Immutable, int>(init, 3);
    int result = seq->reduce(sum, 10);
    assert(result == 16);
    delete seq;
}

TEST(reduce_immutable_array_negative) {
    int init[] = {-1, -2, -3};
    array_seq<Mutability::Immutable, int>* seq = new array_seq<Mutability::Immutable, int>(init, 3);
    int result = seq->reduce(sum, 0);
    assert(result == -6);
    delete seq;
}

TEST(reduce_mutable_list_sum) {
    int init[] = {1,2,3,4};
    list_seq<Mutability::Mutable, int>* seq = new list_seq<Mutability::Mutable, int>(init, 4);
    int result = seq->reduce(sum, 0);
    assert(result == 10);
    delete seq;
}

TEST(reduce_mutable_list_mult) {
    int init[] = {2,3,4};
    list_seq<Mutability::Mutable, int>* seq = new list_seq<Mutability::Mutable, int>(init, 3);
    int result = seq->reduce(mult, 1);
    assert(result == 24);
    delete seq;
}


TEST(reduce_immutable_list_sum) {
    int init[] = {1,2,3,4};
    list_seq<Mutability::Immutable, int>* seq = new list_seq<Mutability::Immutable, int>(init, 4);
    int result = seq->reduce(sum, 0);
    assert(result == 10);
    delete seq;
}

TEST(reduce_immutable_list_mult) {
    int init[] = {2,3,4};
    list_seq<Mutability::Immutable, int>* seq = new list_seq<Mutability::Immutable, int>(init, 3);
    int result = seq->reduce(mult, 1);
    assert(result == 24);
    delete seq;
}


TEST(reduce_empty_array_throws) {
    array_seq<Mutability::Mutable, int>* seq = new array_seq<Mutability::Mutable, int>();
    errors err = NO_ERR;
    TRY {
        seq->reduce(sum, 0);
    }
    CATCH(err) {
        assert(err == ERR_INCORRECT_INDEX);
    }
    ETRY;
    delete seq;
}

TEST(reduce_empty_list_throws) {
    list_seq<Mutability::Immutable, int>* seq = new list_seq<Mutability::Immutable, int>();
    errors err = NO_ERR;
    TRY {
        seq->reduce(sum, 0);
    }
    CATCH(err) {
        assert(err == ERR_INCORRECT_INDEX);
    }
    ETRY;
    delete seq;
}