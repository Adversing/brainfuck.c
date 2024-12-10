#ifndef PROGRAM_H
#define PROGRAM_H

#include "common.h"

#include <stdbool.h>
#include <stddef.h>

typedef struct token_t {
    char instruction;
    Position pos;
} Token;

typedef struct program_t {
    Token* instructions;
    size_t size;
    int pc;
} Program;

Program* program_create(void);
void program_destroy(Program* prog);
bool program_load(Program* prog, const char* filename);

#endif
