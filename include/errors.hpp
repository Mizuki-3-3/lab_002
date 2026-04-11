#pragma onсe
#include <setjmp.h>

typedef enum{
    NO_ERR = 0,
    ERR_NULL,
    ERR_MEMORY,
    ERR_INCORRECT_INDEX,
    ERR_TYPE_MISMATCH,
}errors;

typedef struct {
    errors err;
    char* stack_files[10];
    int stack_lines[10];
    int stack_depth;
}Exceptions;

errors err_get();

void print_err_and_stack(Exceptions* exc);

char* err_get_message(errors err);

void err_clear();

void err_set(errors err, char* file, int line);

extern jmp_buf buf;
extern int exc_active;
extern Exceptions current;

#define TRY \
    do { \
        exc_active = 1; \
        current.stack_depth = 0; \
        switch (setjmp(buf)) { \
            case 0:
    

#define CATCH(err_var) \
            break; \
            default: \
                err_var = current.err; \
                exc_active = 0;
    
#define CATCH_TESTS \
            break; \
            default: \
                exc_active = 0;

#define ETRY \
        } \
    } while (0)

#define THROW(err_code) \
    do { \
        current.err = err_code; \
        if (current.stack_depth < 10) { \
            current.stack_files[current.stack_depth] = __FILE__; \
            current.stack_lines[current.stack_depth] = __LINE__; \
            current.stack_depth++; \
        } \
        if (exc_active == 1) { \
            longjmp(buf, 1); \
        } else { \
            print_err_and_stack(&current); \
        } \
    } while (0)
    

/**
 * @brief Макрос для возврата из void функции при возникновении ошибки
 * 
 */
#define RETURN_ON_ERROR(cond, err_code) \
    do { \
        if (cond) { \
            THROW(err_code); \
            return; \
        } \
    } while (0)

/**
 * @brief Макрос для возврата значения из функции при возникновении ошибки
 * 
 */
#define RETURN_VAL_ON_ERROR(cond, err_code, ret) \
    do { \
        if (cond) { \
            THROW(err_code); \
            return ret; \
        } \
    } while (0)