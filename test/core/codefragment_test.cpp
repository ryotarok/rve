#include "gtest/gtest.h"

extern "C" {
#include "core/codefragment.h"
}

// helper

static codefragment_t *build_codefragment_tree(codefragment_t *m[],
                                               size_t m_len) {

  int32_t indexes[] = {3, 2, 0, 1, 5, 4, 6};
  if (NUMBER_OF(indexes) != m_len) {
    return NULL;
  }

  codefragment_t *root = m[indexes[0]];
  for (size_t i = 1; i < m_len; ++i) {
    root = codefragment_insert(root, m[indexes[i]]);
  }
  return root;
}

static void delete_codefragment_all(codefragment_t *m[], size_t m_len) {
  for (size_t i = 0; i < m_len; ++i) {
    codefragment_delete(m[i]);
  }
}

static void assert_codefragment(codefragment_t *m, codefragment_t *expected_m) {
  ASSERT_EQ(expected_m, m);
}

// test

TEST(codefragment, new_and_delete) {
  codefragment_t *m = codefragment_new(0x1000);
  ASSERT_TRUE(m != NULL);
  codefragment_delete(m);
}

TEST(codefragment, find) {
  codefragment_t *m[7];
  for (size_t i = 0; i < NUMBER_OF(m); ++i) {
    m[i] = codefragment_new(i * 0x1000);
  }
  codefragment_t *root = build_codefragment_tree(m, NUMBER_OF(m));
  assert_codefragment(codefragment_find(root, 0x0000), m[0]);
  assert_codefragment(codefragment_find(root, 0x1000), m[1]);
  assert_codefragment(codefragment_find(root, 0x2000), m[2]);
  assert_codefragment(codefragment_find(root, 0x3000), m[3]);
  assert_codefragment(codefragment_find(root, 0x4000), m[4]);
  assert_codefragment(codefragment_find(root, 0x5000), m[5]);
  assert_codefragment(codefragment_find(root, 0x6000), m[6]);
  delete_codefragment_all(m, NUMBER_OF(m));
}
