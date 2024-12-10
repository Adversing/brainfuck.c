#ifndef ERROR_H
#define ERROR_H

#include "common.h"

void error_syntax(const char* message, const Position *pos);
void error_runtime(const char* message, const Position *pos);

#endif
