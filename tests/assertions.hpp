#pragma once

#define assert(expr) \
    ((!!(expr)) \
    ? assert_success (#expr, __FILE__, __LINE__) \
    : assert_fail (#expr, __FILE__, __LINE__))

void int_success(void);
void int_fail(void);

int assert_success(const char* expr, const char* file, unsigned int line);
int assert_fail(const char* expr, const char* file, unsigned int line);
