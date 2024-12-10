cmake_minimum_required(VERSION 3.30)
project(brainfuck C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(brainfuck
        src/common.h
        src/error.c
        src/error.h
        src/interpreter.c
        src/interpreter.h
        src/main.c
        src/memory.c
        src/memory.h
        src/program.c
        src/program.h
)
