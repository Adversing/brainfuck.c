#include "error.h"

#include <stdio.h>

void error_syntax(const char* message, const Position *pos) {
    if (pos == NULL) {
        fprintf(stderr, "Syntax Error: %s\n", message);
        return;
    }
    fprintf(stderr, "Syntax Error: %s at line %d, column %d\n",
            message, pos->line, pos->column);
}

void error_runtime(const char* message, const Position *pos) {
    if (pos == NULL) {
        fprintf(stderr, "Runtime Error: %s\n", message);
        return;
    }
    fprintf(stderr, "Runtime Error: %s at line %d, column %d\n",
            message, pos->line, pos->column);
}
