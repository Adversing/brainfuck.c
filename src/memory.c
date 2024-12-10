#include "memory.h"

#include <stdbool.h>
#include <stdlib.h>

Memory* memory_create(const size_t size) {
    Memory* mem = malloc(sizeof(Memory));
    if (!mem) return NULL;

    mem->cells = calloc(size, sizeof(char));
    if (!mem->cells) {
        free(mem);
        return NULL;
    }

    mem->size = size;
    mem->pointer = 0;
    return mem;
}

void memory_destroy(Memory* mem) {
    if (mem) {
        free(mem->cells);
        free(mem);
    }
}

bool memory_bounds_check(const Memory* mem, const int pointer) {
    return pointer >= 0 && pointer < mem->size;
}
