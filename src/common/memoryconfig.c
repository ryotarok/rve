#include "memoryconfig.h"
#include "util.h"

void memoryconfig_initialize(memoryconfig_t *config, int32_t options) {
  if (config == NULL) {
    return;
  }

  config->debug = BITFLAG_TO_BOOL(options, MEMORYCONFIG_OPTION_ENABLE_DEBUG);
  config->verbose =
      BITFLAG_TO_BOOL(options, MEMORYCONFIG_OPTION_ENABLE_VERBOSE);
  config->leakcheck =
      BITFLAG_TO_BOOL(options, MEMORYCONFIG_OPTION_ENABLE_LEAKCHECK);
}

void memoryconfig_finalize(memoryconfig_t *config) {
  UNREF(config);
  // do nothing
}
