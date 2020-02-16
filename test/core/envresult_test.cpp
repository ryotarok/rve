#include "gtest/gtest.h"

extern "C" {
#include "core/envresult.h"
}

TEST(envresult, success) {
  envresult_t r;
  envresult_t *pr = envresult_set_success(&r);
  ASSERT_EQ(&r, pr);
  ASSERT_TRUE(r.success);
  ASSERT_EQ(ENVERROR_NONE, r.error);
}

TEST(envresult, success_to_null_object) {
  envresult_t *null_pr = envresult_set_success(NULL);
  ASSERT_TRUE(null_pr == NULL);
}

TEST(envresult, set_readmemory_error) {
  envresult_t r;
  envresult_t *pr = envresult_set_error(&r, ENVERROR_READMEMORY);
  ASSERT_EQ(&r, pr);
  ASSERT_FALSE(r.success);
  ASSERT_EQ(ENVERROR_READMEMORY, r.error);
}

TEST(envresult, set_readmemory_error_to_null_object) {
  envresult_t *null_pr = envresult_set_error(NULL, ENVERROR_READMEMORY);
  ASSERT_TRUE(null_pr == NULL);
}

TEST(envresult, set_writememory_error) {
  envresult_t r;
  envresult_t *pr = envresult_set_error(&r, ENVERROR_WRITEMEMORY);
  ASSERT_EQ(&r, pr);
  ASSERT_FALSE(r.success);
  ASSERT_EQ(ENVERROR_WRITEMEMORY, r.error);
}

TEST(envresult, set_writememory_error_to_null_object) {
  envresult_t *null_pr = envresult_set_error(NULL, ENVERROR_WRITEMEMORY);
  ASSERT_TRUE(null_pr == NULL);
}

TEST(envresult, is_success) {
  envresult_t r;

  envresult_set_success(&r);
  ASSERT_TRUE(envresult_is_success(&r));

  envresult_set_error(&r, ENVERROR_READMEMORY);
  ASSERT_FALSE(envresult_is_success(&r));

  envresult_set_error(&r, ENVERROR_WRITEMEMORY);
  ASSERT_FALSE(envresult_is_success(&r));
}

TEST(envresult, is_success_to_null_object) {
  ASSERT_FALSE(envresult_is_success(NULL));
}

TEST(envresult, error) {
  envresult_t r;

  envresult_set_success(&r);
  ASSERT_EQ(ENVERROR_NONE, envresult_error(&r));

  envresult_set_error(&r, ENVERROR_READMEMORY);
  ASSERT_EQ(ENVERROR_READMEMORY, envresult_error(&r));

  envresult_set_error(&r, ENVERROR_WRITEMEMORY);
  ASSERT_EQ(ENVERROR_WRITEMEMORY, envresult_error(&r));
}

TEST(envresult, error_to_null_object) {
  ASSERT_EQ(ENVERROR_NONE, envresult_error(NULL));
}
