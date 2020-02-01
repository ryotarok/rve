#include "gtest/gtest.h"

extern "C" {
#include "common/memoryconfig.h"
}

TEST(memoryconfig, initialize_and_finalize) {
  memoryconfig_t config;

  memoryconfig_initialize(&config, MEMORYCONFIG_OPTION_NONE);
  ASSERT_FALSE(config.debug);
  ASSERT_FALSE(config.verbose);
  ASSERT_FALSE(config.leakcheck);
  memoryconfig_finalize(&config);

  memoryconfig_initialize(&config, MEMORYCONFIG_OPTION_ENABLE_DEBUG);
  ASSERT_TRUE(config.debug);
  ASSERT_FALSE(config.verbose);
  ASSERT_FALSE(config.leakcheck);
  memoryconfig_finalize(&config);

  memoryconfig_initialize(&config, MEMORYCONFIG_OPTION_ENABLE_VERBOSE);
  ASSERT_FALSE(config.debug);
  ASSERT_TRUE(config.verbose);
  ASSERT_FALSE(config.leakcheck);
  memoryconfig_finalize(&config);

  memoryconfig_initialize(&config, MEMORYCONFIG_OPTION_ENABLE_LEAKCHECK);
  ASSERT_FALSE(config.debug);
  ASSERT_FALSE(config.verbose);
  ASSERT_TRUE(config.leakcheck);
  memoryconfig_finalize(&config);

  memoryconfig_initialize(&config, MEMORYCONFIG_OPTION_ENABLE_DEBUG |
                                       MEMORYCONFIG_OPTION_ENABLE_VERBOSE |
                                       MEMORYCONFIG_OPTION_ENABLE_LEAKCHECK);
  ASSERT_TRUE(config.debug);
  ASSERT_TRUE(config.verbose);
  ASSERT_TRUE(config.leakcheck);
  memoryconfig_finalize(&config);

  memoryconfig_initialize(NULL, MEMORYCONFIG_OPTION_NONE); // unabort check
  memoryconfig_finalize(NULL);                             // unabort check
}
