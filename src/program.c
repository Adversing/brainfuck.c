#include "program.h"

#include "error.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool has_bf_extension(const char* filename) {
    const char* dot = strrchr(filename, '.');
    return dot && strcmp(dot, ".bf") == 0;
}

Program* program_create(void) {
    Program* prog = malloc(sizeof(Program));
    if (!prog) return NULL;

    prog->instructions = malloc(MAX_PROGRAM_SIZE * sizeof(Token));
    if (!prog->instructions) {
        free(prog);
        return NULL;
    }

    prog->size = 0;
    prog->pc = 0;
    return prog;
}

void program_destroy(Program* prog) {
    if (prog) {
        free(prog->instructions);
        free(prog);
    }
}

bool program_load(Program* prog, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        error_runtime("Cannot open file", NULL);
        return false;
    }

    if (!has_bf_extension(filename)) {
        error_runtime("File must have .bf extension", NULL);
        return false;
    }

    int c;
    int line = 1, column = 0;
    int bracket_balance = 0;

    while ((c = fgetc(file)) != EOF && prog->size < MAX_PROGRAM_SIZE) {
        column++;

        if (c == '\n') {
            line++;
            column = 0;
            continue;
        }

        if (strchr("><+-.,[]", c)) {
            const Token token = {
                .instruction = c,
                .pos = (Position){line, column}
            };

            if (c == '[') bracket_balance++;
            if (c == ']') {
                bracket_balance--;
                if (bracket_balance < 0) {
                    error_syntax("Unmatched ']'", &token.pos);
                    fclose(file);
                    return false;
                }
            }

            prog->instructions[prog->size++] = token;
        }
    }

    if (bracket_balance > 0) {
        error_syntax("Unmatched '['", &(Position){line, column});
        fclose(file);
        return false;
    }

    fclose(file);
    return true;
}
