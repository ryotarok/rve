#include "gtest/gtest.h"

extern "C" {
#include "core/environment.h"
}

TEST(environment, new_and_delete) {
  environment_t *env = environment_new();
  ASSERT_TRUE(env != NULL);
  environment_delete(env);
}

TEST(environment, read_and_write_to_reg0) {
  environment_t *env = environment_new();
  environment_writereg(env, 0, 1);
  ASSERT_EQ(0, environment_readreg(env, 0));
  environment_delete(env);
}

TEST(environment, read_and_write_to_regs_without_reg0) {
  environment_t *env = environment_new();
  for (int32_t i = 1; i < ENVIRONMENT_XREGISTER_NUM; ++i) {
    uint64_t value = i * 0x1000;
    environment_writereg(env, i, value);
    ASSERT_EQ(value, environment_readreg(env, i));
  }
  environment_delete(env);
}

TEST(environment, read_and_write_using_nonexisted_regid) {
  environment_t *env = environment_new();
  uint8_t regid = ENVIRONMENT_XREGISTER_NUM;
  environment_writereg(env, regid, 1);
  ASSERT_EQ(0, environment_readreg(env, regid));
  environment_delete(env);
}

TEST(environment, read_and_write_using_null_object) {
  environment_writereg(NULL, 1, 1);
  ASSERT_EQ(0, environment_readreg(NULL, 1));
}

TEST(environment, load) {}

TEST(environment, store) {}
