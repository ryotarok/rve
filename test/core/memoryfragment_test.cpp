#include "gtest/gtest.h"

extern "C" {
#include "core/memoryfragment.h"
}

// helper

static memoryfragment_t *build_memoryfragment_tree(memoryfragment_t *m[],
                                                   size_t m_len) {

  int32_t indexes[] = {3, 2, 0, 1, 5, 4, 6};
  if (NUMBER_OF(indexes) != m_len) {
    return NULL;
  }

  memoryfragment_t *root = m[indexes[0]];
  for (size_t i = 1; i < m_len; ++i) {
    root = memoryfragment_insert(root, m[indexes[i]]);
  }
  return root;
}

static void delete_memoryfragment_all(memoryfragment_t *m[], size_t m_len) {
  for (size_t i = 0; i < m_len; ++i) {
    memoryfragment_delete(m[i]);
  }
}

static void assert_memoryfragment(memoryfragment_t *m,
                                  memoryfragment_t *expected_m) {
  ASSERT_EQ(expected_m, m);
}

// test

TEST(memoryfragment, new_and_delete) {
  memoryfragment_t *m = memoryfragment_new(0x1000);
  ASSERT_TRUE(m != NULL);
  memoryfragment_delete(m);
}

TEST(memoryfragment, find) {
  memoryfragment_t *m[7];
  for (size_t i = 0; i < NUMBER_OF(m); ++i) {
    m[i] = memoryfragment_new(i * 0x1000);
  }
  memoryfragment_t *root = build_memoryfragment_tree(m, NUMBER_OF(m));
  assert_memoryfragment(memoryfragment_find(root, 0x0000), m[0]);
  assert_memoryfragment(memoryfragment_find(root, 0x1000), m[1]);
  assert_memoryfragment(memoryfragment_find(root, 0x2000), m[2]);
  assert_memoryfragment(memoryfragment_find(root, 0x3000), m[3]);
  assert_memoryfragment(memoryfragment_find(root, 0x4000), m[4]);
  assert_memoryfragment(memoryfragment_find(root, 0x5000), m[5]);
  assert_memoryfragment(memoryfragment_find(root, 0x6000), m[6]);
  delete_memoryfragment_all(m, NUMBER_OF(m));
}
