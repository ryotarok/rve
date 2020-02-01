#ifndef COMMON_MEMORY_H
#define COMMON_MEMORY_H

#include "common.h"

#include "memoryconfig.h"

void memory_initialize(memoryconfig_t *config);
void memory_finalize(void);
void *memory_alloc(size_t bytes);
void memory_free(void *ptr);
int32_t memory_leaks(void);
void memory_dump_leaks(void);

#endif // COMMON_MEMORY_H
