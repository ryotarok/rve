#ifndef COMMON_MEMORYCONFIG_H
#define COMMON_MEMORYCONFIG_H

#include "cstd.h"

typedef struct memoryconfig_rec memoryconfig_t;
struct memoryconfig_rec {
  bool debug;
  bool verbose;
  bool leakcheck;
};

enum memoryconfig_option_enum {
  MEMORYCONFIG_OPTION_NONE = 0x00,
  MEMORYCONFIG_OPTION_ENABLE_DEBUG = 0x01,
  MEMORYCONFIG_OPTION_ENABLE_VERBOSE = 0x02,
  MEMORYCONFIG_OPTION_ENABLE_LEAKCHECK = 0x04,
};
typedef enum memoryconfig_option_enum memoryconfig_option_t;

void memoryconfig_initialize(memoryconfig_t *config, int32_t options);
void memoryconfig_finalize(memoryconfig_t *config);

#endif // COMMON_MEMORYCONFIG_H
