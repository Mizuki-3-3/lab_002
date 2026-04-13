#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "errors.hpp"

jmp_buf buf;
int exc_active = 0;
Exceptions current = {};  

const char* err_get_message(errors err){
    switch (err) {
        case ERR_NULL:
            return "Нулевой указатель\n";
        case ERR_MEMORY:
            return "Не удалось выделить память\n";
        case ERR_INCORRECT_INDEX:
            return "Неправильные размер матрицы\n";
        case ERR_TYPE_MISMATCH:
            return "Несовместимые типы\n";
        default:
            return "Ошибка\n";
    }
}

void err_set(errors err, const char* file, int line){
    current.err = err;
    if (current.stack_depth < 10) {
        current.stack_files[current.stack_depth] = file;
        current.stack_lines[current.stack_depth] = line;
        current.stack_depth++;
    }
}

void print_err_and_stack(Exceptions* exc){

    fprintf(stderr,"НЕПОЙМАННОЕ ИСКЛЮЧЕНИЕ:\n");
    fprintf(stderr,"Код: %d\n", exc->err);
    fprintf(stderr,"Сообщение: %s\n",err_get_message(exc->err));

    if (exc->stack_depth > 0 && exc->stack_depth <= 10) {
        fprintf(stderr," Стек:\n");
        for (int i = 0; i < exc->stack_depth; i++) {
            fprintf(stderr,"  [%d] %s:%d\n", i, exc->stack_files[i], exc->stack_lines[i]);
        }
    }

    fprintf(stderr,"\nПрограмма аварийно завершена\n");
    fflush(stdout);
    fflush(stderr);

    abort();
}

errors err_get(){
    return current.err;
}

void err_clear(){
    current.err = NO_ERR;
    current.stack_depth = 0;
    for (int i = 0; i < 10; i++) {
        current.stack_files[i] = NULL;
        current.stack_lines[i] = 0;
    }
}