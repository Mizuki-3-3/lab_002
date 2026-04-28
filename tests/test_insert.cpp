#include "array_seq.hpp"
#include "list_seq.hpp"
#include "assertions.hpp"
#include "tests.hpp"
#include "errors.hpp"   // новый заголовок с классами исключений

TEST(insert_mutable_array_nonempty_begin) {
    int init[] = {1, 2, 3};
    array_seq<Mutability::Mutable, int>* seq = new array_seq<Mutability::Mutable, int>(init, 3);
    seq->insert(26, 0);
    assert(seq->size() == 4);
    assert(seq->get_first() == 26);
    delete seq;
}

TEST(insert_immmutable_array_nonempty_begin) {
    int init[] = {1, 2, 3};
    array_seq<Mutability::Immutable, int>* seq = new array_seq<Mutability::Immutable, int>(init, 3);
    sequence<int>* new_seq = new  array_seq<Mutability::Immutable, int>();
    new_seq = seq->insert(4, 0);
    assert(seq->size() == 3);
    assert(new_seq->size() == 4);
    assert(new_seq->get_first() == 4);
    delete seq;
    delete new_seq;
}

TEST(insert_mutable_list_nonempty_begin){
    int init[] = {1, 2, 3};
    list_seq<Mutability::Mutable, int>* seq = new list_seq<Mutability::Mutable, int>(init, 3);
    seq->insert(26, 0);
    assert(seq->size() == 4);
    assert(seq->get_first() == 26);
    delete seq;
}

TEST(insert_immmutable_list_nonempty_begin){
    int init[] = {1, 2, 3};
    list_seq<Mutability::Immutable, int>* seq = new list_seq<Mutability::Immutable, int>(init, 3);
    sequence<int>* new_seq = new list_seq<Mutability::Immutable, int>();
    new_seq = seq->insert(26, 0);
    assert(seq->size()==3);
    assert(new_seq->size() == 4);
    assert(new_seq->get_first() == 26);
    delete seq;
    delete new_seq;
}

TEST(insert_mutable_array_empty) {
    array_seq<Mutability::Mutable, int>* seq = new array_seq<Mutability::Mutable, int>();
    seq->insert(26, 0);
    assert(seq->size() == 1);
    assert(seq->get_first() == 26);
    assert(seq->get_last() == 26);
    delete seq;
}

TEST(insert_immmutable_array_empty) {
    array_seq<Mutability::Immutable, int>* seq = new array_seq<Mutability::Immutable, int>();
    sequence<int>* new_seq = new  array_seq<Mutability::Immutable, int>();
    new_seq = seq->insert(26, 0);
    assert(seq->size() == 0);
    assert(new_seq->size() == 1);
    assert(new_seq->get_first() == 26);
    assert(new_seq->get_last() == 26);
    delete seq;
    delete new_seq;
}

TEST(insert_mutable_list_empty){
    list_seq<Mutability::Mutable, int>* seq = new list_seq<Mutability::Mutable, int>();
    seq->insert(26, 0);
    assert(seq->size() == 1);
    assert(seq->get_first() == 26);
    assert(seq->get_last() == 26);
    delete seq;
}

TEST(insert_immmutable_list_empty){
    list_seq<Mutability::Immutable, int>* seq = new list_seq<Mutability::Immutable, int>();
    sequence<int>* new_seq = new list_seq<Mutability::Immutable, int>();
    new_seq = seq->insert(26, 0);
    assert(seq->size()==0);
    assert(new_seq->size() == 1);
    assert(new_seq->get_first() == 26);
    assert(new_seq->get_last() == 26);
    delete seq;
    delete new_seq;
}

TEST(insert_mutable_array_nonempty_2_index) {
    int init[] = {1, 2, 3};
    array_seq<Mutability::Mutable, int>* seq = new array_seq<Mutability::Mutable, int>(init, 3);
    seq->insert(26, 2);
    assert(seq->size() == 4);
    assert((*seq)[2] == 26);
    delete seq;
}

TEST(insert_immmutable_array_nonempty_2_index) {
    int init[] = {1, 2, 3};
    array_seq<Mutability::Immutable, int>* seq = new array_seq<Mutability::Immutable, int>(init, 3);
    sequence<int>* new_seq = new  array_seq<Mutability::Immutable, int>();
    new_seq = seq->insert(26, 2);
    assert(seq->size() == 3);
    assert(new_seq->size() == 4);
    assert((*new_seq)[2] == 26);
    delete seq;
    delete new_seq;
}

TEST(insert_mutable_list_nonempty_2_index){
    int init[] = {1, 2, 3};
    list_seq<Mutability::Mutable, int>* seq = new list_seq<Mutability::Mutable, int>(init, 3);
    seq->insert(26, 2);
    assert(seq->size() == 4);
    assert((*seq)[2] == 26);
    delete seq;
}

TEST(insert_immmutable_list_nonempty_2_index){
    int init[] = {1, 2, 3};
    list_seq<Mutability::Immutable, int>* seq = new list_seq<Mutability::Immutable, int>(init, 3);
    sequence<int>* new_seq = new list_seq<Mutability::Immutable, int>();
    new_seq = seq->insert(26, 2);
    assert(seq->size()==3);
    assert(new_seq->size() == 4);
    assert((*new_seq)[2] == 26);
    delete seq;
    delete new_seq;
}

TEST(insert_mutable_array_nonempty_size_index) {
    int init[] = {1, 2, 3};
    array_seq<Mutability::Mutable, int>* seq = new array_seq<Mutability::Mutable, int>(init, 3);
    seq->insert(26, seq->size());
    assert(seq->size() == 4);
    assert((*seq)[(seq->size()-1)] == 26);
    delete seq;
}

TEST(insert_immmutable_array_nonempty_size_index) {
    int init[] = {1, 2, 3};
    array_seq<Mutability::Immutable, int>* seq = new array_seq<Mutability::Immutable, int>(init, 3);
    sequence<int>* new_seq = new  array_seq<Mutability::Immutable, int>();
    new_seq = seq->insert(26, seq->size());
    assert(seq->size() == 3);
    assert(new_seq->size() == 4);
    assert((*new_seq)[seq->size()] == 26);
    delete seq;
    delete new_seq;
}

TEST(insert_mutable_list_nonempty_size_index){
    int init[] = {1, 2, 3};
    list_seq<Mutability::Mutable, int>* seq = new list_seq<Mutability::Mutable, int>(init, 3);
    seq->insert(26, seq->size());
    assert(seq->size() == 4);
    assert((*seq)[(seq->size()-1)] == 26);
    delete seq;
}

TEST(insert_immmutable_list_nonempty_size_index){
    int init[] = {1, 2, 3};
    list_seq<Mutability::Immutable, int>* seq = new list_seq<Mutability::Immutable, int>(init, 3);
    sequence<int>* new_seq = new list_seq<Mutability::Immutable, int>();
    new_seq = seq->insert(26, seq->size());
    assert(seq->size()==3);
    assert(new_seq->size() == 4);
    assert((*new_seq)[seq->size()] == 26);
    delete seq;
    delete new_seq;
}

// ----- Новые версии тестов с исключениями -----

TEST(insert_immmutable_list_incorrect_index_test){
    list_seq<Mutability::Immutable, int>* seq = new list_seq<Mutability::Immutable, int>();
    sequence<int>* new_seq = nullptr;
    try {
        new_seq = seq->insert(2947, 1);
        assert(false && "Expected index_out_of_range exception");
    }
    catch (const index_out_of_range& e) {
        // ожидаемое исключение
    }
    assert(seq->size() == 0);
    delete new_seq;
    delete seq;
}

TEST(insert_mmutable_list_incorrect_index_test){
    list_seq<Mutability::Mutable, int>* seq = new list_seq<Mutability::Mutable, int>();
    try {
        seq->insert(2947, 1);
        assert(false && "Expected index_out_of_range exception");
    }
    catch (const index_out_of_range& e) {
        // ожидаемое исключение
    }
    assert(seq->size() == 0);
    delete seq;
}

TEST(insert_immmutable_array_incorrect_index_test){
    array_seq<Mutability::Immutable, int>* seq = new array_seq<Mutability::Immutable, int>();
    sequence<int>* new_seq = nullptr;
    try {
        new_seq = seq->insert(2947, 1);
        assert(false && "Expected index_out_of_range exception");
    }
    catch (const index_out_of_range& e) {
        // OK
    }
    assert(seq->size() == 0);
    delete new_seq;
    delete seq;
}

TEST(insert_mmutable_array_incorrect_index_test){
    array_seq<Mutability::Mutable, int>* seq = new array_seq<Mutability::Mutable, int>();
    try {
        seq->insert(2947, 1);
        assert(false && "Expected index_out_of_range exception");
    }
    catch (const index_out_of_range& e) {
        // OK
    }
    assert(seq->size() == 0);
    delete seq;
}

TEST(insert_immmutable_list_negative_index_test){
    list_seq<Mutability::Immutable, int>* seq = new list_seq<Mutability::Immutable, int>();
    sequence<int>* new_seq = nullptr;
    try {
        new_seq = seq->insert(2947, -1231);
        assert(false && "Expected index_out_of_range exception");
    }
    catch (const index_out_of_range& e) {
        // OK
    }
    assert(seq->size() == 0);
    delete new_seq;
    delete seq;
}

TEST(insert_mmutable_list_negative_index_test){
    list_seq<Mutability::Mutable, int>* seq = new list_seq<Mutability::Mutable, int>();
    try {
        seq->insert(2947, -21);
        assert(false && "Expected index_out_of_range exception");
    }
    catch (const index_out_of_range& e) {
        // OK
    }
    assert(seq->size() == 0);
    delete seq;
}

TEST(insert_immmutable_array_negative_index_test){
    array_seq<Mutability::Immutable, int>* seq = new array_seq<Mutability::Immutable, int>();
    sequence<int>* new_seq = nullptr;
    try {
        new_seq = seq->insert(2947, -23);
        assert(false && "Expected index_out_of_range exception");
    }
    catch (const index_out_of_range& e) {
        // OK
    }
    assert(seq->size() == 0);
    delete new_seq;
    delete seq;
}

TEST(insert_mmutable_array_negative_index_test){
    array_seq<Mutability::Mutable, int>* seq = new array_seq<Mutability::Mutable, int>();
    try {
        seq->insert(2947, -24);
        assert(false && "Expected index_out_of_range exception");
    }
    catch (const index_out_of_range& e) {
        // OK
    }
    assert(seq->size() == 0);
    delete seq;
}

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
    assert((*new_seq)[1] == 5);
    assert((*new_seq)[2] == 6);
    delete seq;
    delete new_seq;
}