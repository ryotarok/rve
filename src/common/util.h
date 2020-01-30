#ifndef COMMON_UTIL_H
#define COMMON_UTIL_H

#include "cstd.h"

#define UNREF(var) ((void)var)

#define OFFSET_OF(type, member) ((int32_t)(&(((type *)0)->member)))
#define NUMBER_OF(array) (sizeof(array) / sizeof(array[0]))

void util_trace(const char *file, const char *func, int32_t line);
#define TRACE() util_trace(__FILE__, __func__, __LINE__);

#endif // COMMON_UTIL_H
