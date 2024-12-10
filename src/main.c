#include <stdio.h>

#include "interpreter.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename.bf>\n", argv[0]);
        return 1;
    }

    Interpreter* interpreter = interpreter_create();
    if (!interpreter) {
        fprintf(stderr, "Failed to initialize interpreter\n");
        return 1;
    }

    if (!program_load(interpreter->program, argv[1])) {
        interpreter_destroy(interpreter);
        return 1;
    }

    bool success = interpreter_execute(interpreter);
    interpreter_destroy(interpreter);

    return success ? 0 : 1;
}
