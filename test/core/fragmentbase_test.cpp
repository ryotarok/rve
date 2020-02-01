#include "gtest/gtest.h"

extern "C" {
#include "core/fragmentbase.h"
}

// helper

static void initialize_fragmentbases(fragmentbase_t *bases,
                                     int32_t bases_length) {
  for (int32_t i = 0; i < bases_length; ++i) {
    fragmentbase_initialize(&bases[i], i * 0x1000);
  }
}

static void finalize_fragmentbases(fragmentbase_t *bases,
                                   int32_t bases_length) {
  for (int32_t i = 0; i < bases_length; ++i) {
    fragmentbase_finalize(&bases[i]);
  }
}

static void assert_fragmentbase(fragmentbase_t *base,
                                fragmentbase_t *expected_parent,
                                fragmentbase_t *expected_left,
                                fragmentbase_t *expected_right) {
  ASSERT_EQ(expected_parent, (fragmentbase_t *)base->node.parent);
  ASSERT_EQ(expected_left, (fragmentbase_t *)base->node.left);
  ASSERT_EQ(expected_right, (fragmentbase_t *)base->node.right);
}

static fragmentbase_t *build_tree_balanced(fragmentbase_t b[]) {
  /*
   *  n3
   *  + n1
   *    + n0
   *    + n2
   *  + n5
   *    + n4
   *    + n6
   */
  int32_t indexes[] = {3, 1, 0, 2, 5, 4, 6};
  fragmentbase_t *root = &b[3];
  for (size_t i = 1; i < NUMBER_OF(indexes); ++i) {
    fragmentbase_insert(root, &b[indexes[i]]);
  }
  return root;
}

static fragmentbase_t *build_tree_unbalanced(fragmentbase_t b[]) {
  /*
   *  n
   *  + n
   *    + NULL
   *    + n
   *      + NULL
   *      + n
   *  + n
   *    + NULL
   *    + n
   *      + n
   *      + n
   */
  int32_t indexes[] = {3, 1, 0, 2, 5, 4, 6};
  fragmentbase_t *root = &b[3];
  for (size_t i = 1; i < NUMBER_OF(indexes); ++i) {
    fragmentbase_insert(root, &b[indexes[i]]);
  }
  return root;
}

// test

TEST(fragmentbase, initialize_and_finalize) {
  fragmentbase_t base;
  fragmentbase_initialize(&base, 0x1000);
  ASSERT_TRUE(NULL == bintreenode_parent(&base.node));
  ASSERT_TRUE(NULL == bintreenode_left(&base.node));
  ASSERT_TRUE(NULL == bintreenode_right(&base.node));
  fragmentbase_finalize(&base);
}

TEST(fragmentbase, insert) {
  fragmentbase_t b[7];
  initialize_fragmentbases(b, NUMBER_OF(b));
  build_tree_balanced(b);
  assert_fragmentbase(&b[3], NULL, &b[1], &b[5]);
  assert_fragmentbase(&b[1], &b[3], &b[0], &b[2]);
  assert_fragmentbase(&b[0], &b[1], NULL, NULL);
  assert_fragmentbase(&b[2], &b[1], NULL, NULL);
  assert_fragmentbase(&b[5], &b[3], &b[4], &b[6]);
  assert_fragmentbase(&b[4], &b[5], NULL, NULL);
  assert_fragmentbase(&b[6], &b[5], NULL, NULL);
  finalize_fragmentbases(b, NUMBER_OF(b));
}

TEST(fragmentbase, find) {
  fragmentbase_t b[7];
  initialize_fragmentbases(b, NUMBER_OF(b));
  fragmentbase_t *root = build_tree_balanced(b);
  ASSERT_EQ(fragmentbase_find(root, 0x3000), &b[3]);
  ASSERT_EQ(fragmentbase_find(root, 0x1000), &b[1]);
  ASSERT_EQ(fragmentbase_find(root, 0x0000), &b[0]);
  ASSERT_EQ(fragmentbase_find(root, 0x2000), &b[2]);
  ASSERT_EQ(fragmentbase_find(root, 0x5000), &b[5]);
  ASSERT_EQ(fragmentbase_find(root, 0x4000), &b[4]);
  ASSERT_EQ(fragmentbase_find(root, 0x6000), &b[6]);
  ASSERT_TRUE(fragmentbase_find(root, 0x0001) == NULL);
  ASSERT_TRUE(fragmentbase_find(root, 0x6001) == NULL);
  finalize_fragmentbases(b, NUMBER_OF(b));
}

TEST(fragmentbase, find_minnode) {
  fragmentbase_t b[7];
  initialize_fragmentbases(b, NUMBER_OF(b));
  build_tree_balanced(b);
  ASSERT_EQ(fragmentbase_find_minnode(&b[3]), &b[0]);
  ASSERT_EQ(fragmentbase_find_minnode(&b[5]), &b[4]);
  ASSERT_EQ(fragmentbase_find_minnode(&b[0]), &b[0]);
  ASSERT_TRUE(fragmentbase_find_minnode(NULL) == NULL);
  finalize_fragmentbases(b, NUMBER_OF(b));
}

TEST(fragmentbase, find_maxnode) {
  fragmentbase_t b[7];
  initialize_fragmentbases(b, NUMBER_OF(b));
  build_tree_balanced(b);
  ASSERT_EQ(fragmentbase_find_maxnode(&b[3]), &b[6]);
  ASSERT_EQ(fragmentbase_find_maxnode(&b[1]), &b[2]);
  ASSERT_EQ(fragmentbase_find_maxnode(&b[4]), &b[4]);
  ASSERT_TRUE(fragmentbase_find_maxnode(NULL) == NULL);
  finalize_fragmentbases(b, NUMBER_OF(b));
}

TEST(fragmentbase, root) {
  fragmentbase_t b[7];
  initialize_fragmentbases(b, NUMBER_OF(b));
  build_tree_balanced(b);
  ASSERT_EQ(&b[3], fragmentbase_root(&b[0]));
  ASSERT_EQ(&b[3], fragmentbase_root(&b[1]));
  ASSERT_EQ(&b[3], fragmentbase_root(&b[2]));
  ASSERT_EQ(&b[3], fragmentbase_root(&b[3]));
  ASSERT_EQ(&b[3], fragmentbase_root(&b[4]));
  ASSERT_EQ(&b[3], fragmentbase_root(&b[5]));
  ASSERT_EQ(&b[3], fragmentbase_root(&b[6]));
  ASSERT_EQ(NULL, fragmentbase_root(NULL));
  finalize_fragmentbases(b, NUMBER_OF(b));
}

TEST(fragmentbase, remove_leaf) {
  fragmentbase_t b[7];

  initialize_fragmentbases(b, NUMBER_OF(b));
  fragmentbase_t *root = build_tree_balanced(b);
  fragmentbase_t *target = fragmentbase_find(root, 0x0000);
  fragmentbase_remove(target);
  assert_fragmentbase(&b[3], NULL, &b[1], &b[5]);
  assert_fragmentbase(&b[1], &b[3], NULL, &b[2]);
  assert_fragmentbase(&b[0], NULL, NULL, NULL);
  assert_fragmentbase(&b[2], &b[1], NULL, NULL);
  assert_fragmentbase(&b[5], &b[3], &b[4], &b[6]);
  assert_fragmentbase(&b[4], &b[5], NULL, NULL);
  assert_fragmentbase(&b[6], &b[5], NULL, NULL);
  finalize_fragmentbases(b, NUMBER_OF(b));
}

TEST(fragmentbase, remove_one_child_node) {
  fragmentbase_t b[7];
  initialize_fragmentbases(b, NUMBER_OF(b));
  fragmentbase_t *root = build_tree_unbalanced(b);
  fragmentbase_t *target = fragmentbase_find(root, 0x0000);
  fragmentbase_remove(target);
  assert_fragmentbase(&b[3], NULL, &b[1], &b[5]);
  assert_fragmentbase(&b[1], &b[3], NULL, &b[2]);
  assert_fragmentbase(&b[0], NULL, NULL, NULL);
  assert_fragmentbase(&b[2], &b[1], NULL, NULL);
  assert_fragmentbase(&b[5], &b[3], &b[4], &b[6]);
  assert_fragmentbase(&b[4], &b[5], NULL, NULL);
  assert_fragmentbase(&b[6], &b[5], NULL, NULL);
  finalize_fragmentbases(b, NUMBER_OF(b));
}
