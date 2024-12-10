#ifndef MEMORY_H
#define MEMORY_H

#include <stdbool.h>
#include <stddef.h>

typedef struct memory_t {
    char* cells;
    size_t size;
    int pointer;
} Memory;

Memory* memory_create(size_t size);
void memory_destroy(Memory* mem);
bool memory_bounds_check(const Memory* mem, int pointer);

#endif
