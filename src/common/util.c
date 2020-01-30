#include "util.h"

void util_trace(const char *file, const char *func, int32_t line) {
  printf("[TRACE] %s %s:%d\n", func, file, line);
}
