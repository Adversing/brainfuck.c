#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "memory.h"
#include "program.h"

#include <stdbool.h>

typedef struct interpreter_t {
    Memory* memory;
    Program* program;
} Interpreter;

Interpreter* interpreter_create(void);
void interpreter_destroy(Interpreter* interpreter);
bool interpreter_execute(const Interpreter* interpreter);

#endif
