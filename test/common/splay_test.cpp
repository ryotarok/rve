#include "gtest/gtest.h"

extern "C" {
#include "common/splay.h"
}

// helper

static void initialize_bintreenodes(bintreenode_t *nodes,
                                    int32_t nodes_length) {
  for (int32_t i = 0; i < nodes_length; ++i) {
    bintreenode_initialize(&nodes[i]);
  }
}

static void finalize_bintreenodes(bintreenode_t *nodes, int32_t nodes_length) {
  for (int32_t i = 0; i < nodes_length; ++i) {
    bintreenode_finalize(&nodes[i]);
  }
}

static void assert_bintreenode(bintreenode_t *node,
                               bintreenode_t *expected_parent,
                               bintreenode_t *expected_left,
                               bintreenode_t *expected_right) {
  ASSERT_EQ(expected_parent, node->parent);
  ASSERT_EQ(expected_left, node->left);
  ASSERT_EQ(expected_right, node->right);
}

static void build_tree_basic(bintreenode_t n[]) {
  /*
   *  n3
   *  + n1
   *    + n0
   *    + n2
   *  + n5
   *    + n4
   *    + n6
   */
  bintreenode_chain_child_left(&n[3], &n[1]);
  bintreenode_chain_child_right(&n[3], &n[5]);
  bintreenode_chain_child_left(&n[1], &n[0]);
  bintreenode_chain_child_right(&n[1], &n[2]);
  bintreenode_chain_child_left(&n[5], &n[4]);
  bintreenode_chain_child_right(&n[5], &n[6]);
}

static void build_tree_left_side_deeply(bintreenode_t n[]) {
  /*
   *  n7
   *  + n3
   *    + n1
   *      + n0
   *      + n2
   *    + n5
   *      + n4
   *      + n6
   *  + n9
   *    + n8
   *    + n10
   */
  bintreenode_chain_child_left(&n[7], &n[3]);
  bintreenode_chain_child_right(&n[7], &n[9]);
  bintreenode_chain_child_left(&n[3], &n[1]);
  bintreenode_chain_child_right(&n[3], &n[5]);
  bintreenode_chain_child_left(&n[1], &n[0]);
  bintreenode_chain_child_right(&n[1], &n[2]);
  bintreenode_chain_child_left(&n[5], &n[4]);
  bintreenode_chain_child_right(&n[5], &n[6]);
  bintreenode_chain_child_left(&n[9], &n[8]);
  bintreenode_chain_child_right(&n[9], &n[10]);
}

static void build_tree_right_side_deeply(bintreenode_t n[]) {
  /*
   *  n3
   *  + n1
   *    + n0
   *    + n2
   *  + n7
   *    + n5
   *      + n4
   *      + n6
   *    + n9
   *      + n8
   *      + n10
   */
  bintreenode_chain_child_left(&n[3], &n[1]);
  bintreenode_chain_child_right(&n[3], &n[7]);
  bintreenode_chain_child_left(&n[1], &n[0]);
  bintreenode_chain_child_right(&n[1], &n[2]);
  bintreenode_chain_child_left(&n[7], &n[5]);
  bintreenode_chain_child_right(&n[7], &n[9]);
  bintreenode_chain_child_left(&n[5], &n[4]);
  bintreenode_chain_child_right(&n[5], &n[6]);
  bintreenode_chain_child_left(&n[9], &n[8]);
  bintreenode_chain_child_right(&n[9], &n[10]);
}

// test

TEST(splay, zig) {
  bintreenode_t n[7];
  initialize_bintreenodes(n, NUMBER_OF(n));
  build_tree_basic(n);
  bintreenode_t *root0 = splay(&n[1]);
  /*
   *  n1
   *  + n0
   *  + n3
   *    + n2
   *    + n5
   *      + n4
   *      + n6
   */
  ASSERT_EQ(root0, &n[1]);
  assert_bintreenode(&n[1], NULL, &n[0], &n[3]);
  assert_bintreenode(&n[0], &n[1], NULL, NULL);
  assert_bintreenode(&n[3], &n[1], &n[2], &n[5]);
  assert_bintreenode(&n[2], &n[3], NULL, NULL);
  assert_bintreenode(&n[5], &n[3], &n[4], &n[6]);
  assert_bintreenode(&n[4], &n[5], NULL, NULL);
  assert_bintreenode(&n[6], &n[5], NULL, NULL);
  finalize_bintreenodes(n, NUMBER_OF(n));

  initialize_bintreenodes(n, NUMBER_OF(n));
  build_tree_basic(n);
  bintreenode_t *root1 = splay(&n[5]);
  /*
   *  n5
   *  + n3
   *    + n1
   *      + n0
   *      + n2
   *    + n4
   *  + n6
   */
  ASSERT_EQ(root1, &n[5]);
  assert_bintreenode(&n[5], NULL, &n[3], &n[6]);
  assert_bintreenode(&n[3], &n[5], &n[1], &n[4]);
  assert_bintreenode(&n[1], &n[3], &n[0], &n[2]);
  assert_bintreenode(&n[0], &n[1], NULL, NULL);
  assert_bintreenode(&n[2], &n[1], NULL, NULL);
  assert_bintreenode(&n[4], &n[3], NULL, NULL);
  assert_bintreenode(&n[6], &n[5], NULL, NULL);
  finalize_bintreenodes(n, NUMBER_OF(n));
}

TEST(splay, zig_zig) {
  bintreenode_t n[11];

  initialize_bintreenodes(n, NUMBER_OF(n));
  build_tree_left_side_deeply(n);
  bintreenode_t *root0 = splay(&n[1]);
  /*
   *  n1
   *  + n0
   *  + n3
   *    + n2
   *    + n7
   *      + n5
   *        + n4
   *        + n6
   *      + n9
   *        + n8
   *        + n10
   */
  ASSERT_EQ(root0, &n[1]);
  assert_bintreenode(&n[1], NULL, &n[0], &n[3]);
  assert_bintreenode(&n[0], &n[1], NULL, NULL);
  assert_bintreenode(&n[3], &n[1], &n[2], &n[7]);
  assert_bintreenode(&n[2], &n[3], NULL, NULL);
  assert_bintreenode(&n[7], &n[3], &n[5], &n[9]);
  assert_bintreenode(&n[5], &n[7], &n[4], &n[6]);
  assert_bintreenode(&n[4], &n[5], NULL, NULL);
  assert_bintreenode(&n[6], &n[5], NULL, NULL);
  assert_bintreenode(&n[9], &n[7], &n[8], &n[10]);
  assert_bintreenode(&n[8], &n[9], NULL, NULL);
  assert_bintreenode(&n[10], &n[9], NULL, NULL);
  finalize_bintreenodes(n, NUMBER_OF(n));

  initialize_bintreenodes(n, NUMBER_OF(n));
  build_tree_right_side_deeply(n);
  bintreenode_t *root1 = splay(&n[9]);
  /*
   *  n9
   *  + n7
   *    + n3
   *      + n1
   *        + n0
   *        + n2
   *      + n5
   *        + n4
   *        + n6
   *    + n8
   *  + n10
   */
  ASSERT_EQ(root1, &n[9]);
  assert_bintreenode(&n[9], NULL, &n[7], &n[10]);
  assert_bintreenode(&n[7], &n[9], &n[3], &n[8]);
  assert_bintreenode(&n[10], &n[9], NULL, NULL);
  assert_bintreenode(&n[3], &n[7], &n[1], &n[5]);
  assert_bintreenode(&n[8], &n[7], NULL, NULL);
  assert_bintreenode(&n[1], &n[3], &n[0], &n[2]);
  assert_bintreenode(&n[0], &n[1], NULL, NULL);
  assert_bintreenode(&n[2], &n[1], NULL, NULL);
  assert_bintreenode(&n[5], &n[3], &n[4], &n[6]);
  assert_bintreenode(&n[4], &n[5], NULL, NULL);
  assert_bintreenode(&n[6], &n[5], NULL, NULL);
  finalize_bintreenodes(n, NUMBER_OF(n));
}

TEST(splay, zig_zag) {
  bintreenode_t n[11];

  initialize_bintreenodes(n, NUMBER_OF(n));
  build_tree_left_side_deeply(n);
  bintreenode_t *root0 = splay(&n[5]);
  /*
   *  n5
   *  + n3
   *    + n1
   *      + n0
   *      + n2
   *    + n4
   *  + n7
   *    + n6
   *    + n9
   *      + n8
   *      + n10
   */
  ASSERT_EQ(root0, &n[5]);
  assert_bintreenode(&n[5], NULL, &n[3], &n[7]);
  assert_bintreenode(&n[3], &n[5], &n[1], &n[4]);
  assert_bintreenode(&n[7], &n[5], &n[6], &n[9]);
  assert_bintreenode(&n[1], &n[3], &n[0], &n[2]);
  assert_bintreenode(&n[0], &n[1], NULL, NULL);
  assert_bintreenode(&n[2], &n[1], NULL, NULL);
  assert_bintreenode(&n[4], &n[3], NULL, NULL);
  assert_bintreenode(&n[6], &n[7], NULL, NULL);
  assert_bintreenode(&n[9], &n[7], &n[8], &n[10]);
  assert_bintreenode(&n[8], &n[9], NULL, NULL);
  assert_bintreenode(&n[10], &n[9], NULL, NULL);
  finalize_bintreenodes(n, NUMBER_OF(n));

  initialize_bintreenodes(n, NUMBER_OF(n));
  build_tree_right_side_deeply(n);
  bintreenode_t *root1 = splay(&n[5]);
  /*
   *  n5
   *  + n3
   *    + n1
   *      + n0
   *      + n2
   *    + n4
   *  + n7
   *    + n6
   *    + n9
   *      + n8
   *      + n10
   */
  ASSERT_EQ(root1, &n[5]);
  assert_bintreenode(&n[5], NULL, &n[3], &n[7]);
  assert_bintreenode(&n[3], &n[5], &n[1], &n[4]);
  assert_bintreenode(&n[7], &n[5], &n[6], &n[9]);
  assert_bintreenode(&n[1], &n[3], &n[0], &n[2]);
  assert_bintreenode(&n[0], &n[1], NULL, NULL);
  assert_bintreenode(&n[2], &n[1], NULL, NULL);
  assert_bintreenode(&n[4], &n[3], NULL, NULL);
  assert_bintreenode(&n[6], &n[7], NULL, NULL);
  assert_bintreenode(&n[9], &n[7], &n[8], &n[10]);
  assert_bintreenode(&n[8], &n[9], NULL, NULL);
  assert_bintreenode(&n[10], &n[9], NULL, NULL);
  finalize_bintreenodes(n, NUMBER_OF(n));
}

TEST(splay, combinations) {
  bintreenode_t n[11];

  initialize_bintreenodes(n, NUMBER_OF(n));
  build_tree_left_side_deeply(n);
  bintreenode_t *root0 = splay(&n[4]);
  /*
   *  n4
   *  + n3
   *    + n1
   *      + n0
   *      + n2
   *    + NULL
   *  + n7
   *    + n5
   *      + NULL
   *      + n6
   *    + n9
   *      + n8
   *      + n10
   */
  ASSERT_EQ(root0, &n[4]);
  assert_bintreenode(&n[4], NULL, &n[3], &n[7]);
  assert_bintreenode(&n[3], &n[4], &n[1], NULL);
  assert_bintreenode(&n[1], &n[3], &n[0], &n[2]);
  assert_bintreenode(&n[0], &n[1], NULL, NULL);
  assert_bintreenode(&n[2], &n[1], NULL, NULL);
  assert_bintreenode(&n[7], &n[4], &n[5], &n[9]);
  assert_bintreenode(&n[5], &n[7], NULL, &n[6]);
  assert_bintreenode(&n[6], &n[5], NULL, NULL);
  assert_bintreenode(&n[9], &n[7], &n[8], &n[10]);
  assert_bintreenode(&n[8], &n[9], NULL, NULL);
  assert_bintreenode(&n[10], &n[9], NULL, NULL);
  finalize_bintreenodes(n, NUMBER_OF(n));
}
