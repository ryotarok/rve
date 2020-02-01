#include "gtest/gtest.h"

extern "C" {
#include "common/memory.h"
}

TEST(memory, initialize_and_finalize) {
  memoryconfig_t config;
  memoryconfig_initialize(&config, MEMORYCONFIG_OPTION_NONE);

  memory_initialize(&config); // unabort check
  memory_initialize(NULL);    // unabort check
  memory_finalize();          // unabort check
}

TEST(memory, alloc_and_free) {
  memoryconfig_t config;
  memoryconfig_initialize(&config, MEMORYCONFIG_OPTION_NONE);
  memory_initialize(&config);

  int32_t *p0 = (int32_t *)memory_alloc(sizeof(int32_t));
  ASSERT_FALSE(p0 == NULL);
  memory_free(p0);

  int32_t *p1 = (int32_t *)memory_alloc(sizeof(int32_t));
  ASSERT_FALSE(p1 == NULL);
  int64_t *p2 = (int64_t *)memory_alloc(sizeof(int64_t));
  ASSERT_FALSE(p2 == NULL);
  memory_free(p2);
  memory_free(p1);

  int8_t *p3 = (int8_t *)memory_alloc(0);
  ASSERT_TRUE(p3 == NULL);
  memory_free(p3);

  memory_finalize();
}

TEST(memory, leaks) {
  memoryconfig_t config;

  memoryconfig_initialize(&config, MEMORYCONFIG_OPTION_NONE);
  memory_initialize(&config);
  ASSERT_EQ(0, memory_leaks());
  int32_t *p0 = (int32_t *)memory_alloc(sizeof(int32_t));
  ASSERT_EQ(0, memory_leaks());
  memory_free(p0);
  ASSERT_EQ(0, memory_leaks());

  memoryconfig_initialize(&config, MEMORYCONFIG_OPTION_ENABLE_LEAKCHECK);
  memory_initialize(&config);
  ASSERT_EQ(0, memory_leaks());
  int32_t *p1 = (int32_t *)memory_alloc(sizeof(int32_t));
  ASSERT_EQ(1, memory_leaks());
  memory_free(p1);
  ASSERT_EQ(0, memory_leaks());

  memory_finalize();
}

// TEST(memory, dump_leask) {} // do not test
