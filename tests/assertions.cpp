#include "assertions.hpp"
#include <iostream>

static int success_count = 0;
static int fail_count = 0;
static int success_count_local = 0;
static int fail_count_local = 0;

void int_success(){
    success_count++;success_count_local++;
}

void int_fail(){
    fail_count++;fail_count_local++;
}

int assert_fail(const char* expr, const char* file, unsigned int lineno) {
    fprintf(stderr, "\033[0;31m%s:%u:\t %s FAILED \033[0m\n", file, lineno, expr);
    int_fail();
    return 0;
}

int assert_success(const char* expr, const char* file, unsigned int lineno) {
    fprintf(stderr, "\033[0;32m%s:%u:\t %s PASSED \033[0m\n", file, lineno, expr);
    int_success();
    return 0;
}