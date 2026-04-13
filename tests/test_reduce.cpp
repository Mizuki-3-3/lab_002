#include "array_seq.hpp"
#include "list_seq.hpp"
#include "assertions.hpp"
#include "tests.hpp"

TEST(reduce_mutable_list_sum) {
    int init[] = {1, 2, 3, 4};
    list_seq<Mutability::Mutable, int>* seq = new list_seq<Mutability::Mutable, int>(init, 4);
    int sum = seq->reduce([](int acc, int x) { return acc + x; }, 0);
    assert(sum == 10);
    delete seq;
}

TEST(reduce_immutable_array_product) {
    int init[] = {2, 3, 4};
    array_seq<Mutability::Immutable, int>* seq = new array_seq<Mutability::Immutable, int>(init, 3);
    int product = seq->reduce([](int acc, int x) { return acc * x; }, 1);
    assert(product == 24);
    delete seq;
}