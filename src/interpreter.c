#include "interpreter.h"
#include "error.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Interpreter* interpreter_create(void) {
    Interpreter* interpreter = malloc(sizeof(Interpreter));
    if (!interpreter) return NULL;

    interpreter->memory = memory_create(MEMORY_SIZE);
    interpreter->program = program_create();

    if (!interpreter->memory || !interpreter->program) {
        interpreter_destroy(interpreter);
        return NULL;
    }

    return interpreter;
}

void interpreter_destroy(Interpreter* interpreter) {
    if (interpreter) {
        memory_destroy(interpreter->memory);
        program_destroy(interpreter->program);
        free(interpreter);
    }
}

bool interpreter_execute(const Interpreter* interpreter) {
    Program* prog = interpreter->program;
    Memory* mem = interpreter->memory;
    int bracket_count;

    // this loop be cleaned up by using computed gotos
    while (prog->pc < prog->size) {
        const Token current = prog->instructions[prog->pc];

        switch (current.instruction) {
            case '>':
                if (!memory_bounds_check(mem, mem->pointer + 1)) {
                    error_runtime("Memory pointer out of bounds", &current.pos);
                    return false;
                }
                mem->pointer++;
                break;

            case '<':
                if (!memory_bounds_check(mem, mem->pointer - 1)) {
                    error_runtime("Memory pointer out of bounds", &current.pos);
                    return false;
                }
                mem->pointer--;
                break;

            case '+':
                mem->cells[mem->pointer]++;
                break;

            case '-':
                mem->cells[mem->pointer]--;
                break;

            case '.':
                putchar(mem->cells[mem->pointer]);
                break;

            case ',':
                mem->cells[mem->pointer] = getchar();
                break;

            case '[':
                if (mem->cells[mem->pointer] == 0) {
                    bracket_count = 1;
                    while (bracket_count > 0) {
                        prog->pc++;
                        if (prog->instructions[prog->pc].instruction == '[') bracket_count++;
                        if (prog->instructions[prog->pc].instruction == ']') bracket_count--;
                    }
                }
                break;

            case ']':
                if (mem->cells[mem->pointer] != 0) {
                    bracket_count = 1;
                    while (bracket_count > 0) {
                        prog->pc--;
                        if (prog->instructions[prog->pc].instruction == '[') bracket_count--;
                        if (prog->instructions[prog->pc].instruction == ']') bracket_count++;
                    }
                }
                break;
            default: break;
        }
        prog->pc++;
    }
    return true;
}
