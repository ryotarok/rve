#ifndef COMMON_UTIL_H
#define COMMON_UTIL_H

#define UNREF(var) ((void)var)

#define OFFSET_OF(type, member) ((int32_t)(&(((type *)0)->member)))
#define NUMBER_OF(array) (sizeof(array) / sizeof(array[0]))

#endif // COMMON_UTIL_H
