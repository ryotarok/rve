#include "gtest/gtest.h"

extern "C" {
#include "common/bintreenode.h"
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

// test

TEST(bintreenode, initialize_and_finalize) {
  bintreenode_t n[1];
  initialize_bintreenodes(n, NUMBER_OF(n));
  assert_bintreenode(&n[0], NULL, NULL, NULL);
  finalize_bintreenodes(n, NUMBER_OF(n));

  bintreenode_initialize(NULL); // unabort checkt
  bintreenode_finalize(NULL);   // unabort check
}

TEST(bintreenode, is_root) {
  bintreenode_t n[3];
  initialize_bintreenodes(n, NUMBER_OF(n));
  n[0].left = &n[1];
  n[0].right = &n[2];
  n[1].parent = &n[0];
  n[2].parent = &n[0];

  ASSERT_TRUE(bintreenode_is_root(&n[0]));
  ASSERT_FALSE(bintreenode_is_root(&n[1]));
  ASSERT_FALSE(bintreenode_is_root(&n[2]));

  ASSERT_FALSE(bintreenode_is_root(NULL));

  finalize_bintreenodes(n, NUMBER_OF(n));
}

TEST(bintreenode, is_parent) {
  bintreenode_t n[3];
  initialize_bintreenodes(n, NUMBER_OF(n));
  n[0].left = &n[1];
  n[0].right = &n[2];
  n[1].parent = &n[0];
  n[2].parent = &n[0];

  ASSERT_TRUE(bintreenode_is_parent(&n[1], &n[0]));
  ASSERT_FALSE(bintreenode_is_parent(&n[1], &n[1]));
  ASSERT_FALSE(bintreenode_is_parent(&n[1], &n[2]));

  ASSERT_TRUE(bintreenode_is_parent(&n[0], NULL));
  ASSERT_FALSE(bintreenode_is_parent(NULL, &n[0]));

  finalize_bintreenodes(n, NUMBER_OF(n));
}

TEST(bintreenode, is_left) {
  bintreenode_t n[3];
  initialize_bintreenodes(n, NUMBER_OF(n));
  n[0].left = &n[1];
  n[0].right = &n[2];
  n[1].parent = &n[0];
  n[2].parent = &n[0];

  ASSERT_FALSE(bintreenode_is_left(&n[0], &n[0]));
  ASSERT_TRUE(bintreenode_is_left(&n[0], &n[1]));
  ASSERT_FALSE(bintreenode_is_left(&n[0], &n[2]));

  ASSERT_TRUE(bintreenode_is_left(&n[1], NULL));
  ASSERT_FALSE(bintreenode_is_left(NULL, &n[0]));

  finalize_bintreenodes(n, NUMBER_OF(n));
}

TEST(bintreenode, is_right) {
  bintreenode_t n[3];
  initialize_bintreenodes(n, NUMBER_OF(n));
  n[0].left = &n[1];
  n[0].right = &n[2];
  n[1].parent = &n[0];
  n[2].parent = &n[0];

  ASSERT_FALSE(bintreenode_is_right(&n[0], &n[0]));
  ASSERT_FALSE(bintreenode_is_right(&n[0], &n[1]));
  ASSERT_TRUE(bintreenode_is_right(&n[0], &n[2]));

  ASSERT_TRUE(bintreenode_is_right(&n[2], NULL));
  ASSERT_FALSE(bintreenode_is_right(NULL, &n[0]));

  finalize_bintreenodes(n, NUMBER_OF(n));
}

TEST(bintreenode, chain_child_left) {
  bintreenode_t n[3];
  initialize_bintreenodes(n, NUMBER_OF(n));

  bintreenode_chain_child_left(&n[0], &n[1]);
  assert_bintreenode(&n[0], NULL, &n[1], NULL);
  assert_bintreenode(&n[1], &n[0], NULL, NULL);

  bintreenode_chain_child_left(&n[0], &n[2]);
  assert_bintreenode(&n[0], NULL, &n[1], NULL);
  assert_bintreenode(&n[2], NULL, NULL, NULL);

  bintreenode_chain_child_left(&n[2], &n[1]);
  assert_bintreenode(&n[2], NULL, NULL, NULL);

  bintreenode_chain_child_left(&n[2], NULL);
  assert_bintreenode(&n[2], NULL, NULL, NULL);

  bintreenode_chain_child_left(NULL, &n[0]); // unabort check
  bintreenode_chain_child_left(NULL, NULL);  // unabort check

  finalize_bintreenodes(n, NUMBER_OF(n));
}

TEST(bintreenode, chain_child_right) {
  bintreenode_t n[3];
  initialize_bintreenodes(n, NUMBER_OF(n));

  bintreenode_chain_child_right(&n[0], &n[1]);
  assert_bintreenode(&n[0], NULL, NULL, &n[1]);
  assert_bintreenode(&n[1], &n[0], NULL, NULL);

  bintreenode_chain_child_right(&n[0], &n[2]);
  assert_bintreenode(&n[0], NULL, NULL, &n[1]);
  assert_bintreenode(&n[2], NULL, NULL, NULL);

  bintreenode_chain_child_right(&n[2], &n[1]);
  assert_bintreenode(&n[2], NULL, NULL, NULL);

  bintreenode_chain_child_right(&n[2], NULL);
  assert_bintreenode(&n[2], NULL, NULL, NULL);

  bintreenode_chain_child_right(NULL, &n[0]); // unabort check
  bintreenode_chain_child_right(NULL, NULL);  // unabort check

  finalize_bintreenodes(n, NUMBER_OF(n));
}

TEST(bintreenode, unchain) {
  bintreenode_t n[8];
  initialize_bintreenodes(n, NUMBER_OF(n));

  bintreenode_chain_child_left(&n[0], &n[1]);
  bintreenode_chain_child_left(&n[1], &n[2]);
  bintreenode_chain_child_right(&n[1], &n[3]);
  bintreenode_unchain(&n[1]);
  assert_bintreenode(&n[0], NULL, NULL, NULL);
  assert_bintreenode(&n[1], NULL, &n[2], &n[3]);
  assert_bintreenode(&n[2], &n[1], NULL, NULL);
  assert_bintreenode(&n[3], &n[1], NULL, NULL);

  bintreenode_chain_child_right(&n[4], &n[5]);
  bintreenode_chain_child_left(&n[5], &n[6]);
  bintreenode_chain_child_right(&n[5], &n[7]);
  bintreenode_unchain(&n[5]);
  assert_bintreenode(&n[4], NULL, NULL, NULL);
  assert_bintreenode(&n[6], &n[5], NULL, NULL);
  assert_bintreenode(&n[7], &n[5], NULL, NULL);

  bintreenode_unchain(&n[0]); // unabort check
  bintreenode_unchain(NULL);  // unabort check

  finalize_bintreenodes(n, NUMBER_OF(n));
}

TEST(bintreenode, unchain_child) {
  bintreenode_t n[9];
  initialize_bintreenodes(n, NUMBER_OF(n));

  bintreenode_chain_child_left(&n[0], &n[1]);
  bintreenode_chain_child_left(&n[1], &n[2]);
  bintreenode_chain_child_right(&n[1], &n[3]);
  bintreenode_unchain_child(&n[0], &n[1]);
  assert_bintreenode(&n[0], NULL, NULL, NULL);
  assert_bintreenode(&n[1], NULL, &n[2], &n[3]);
  assert_bintreenode(&n[2], &n[1], NULL, NULL);
  assert_bintreenode(&n[3], &n[1], NULL, NULL);

  bintreenode_chain_child_right(&n[4], &n[5]);
  bintreenode_chain_child_left(&n[5], &n[6]);
  bintreenode_chain_child_right(&n[5], &n[7]);
  bintreenode_unchain_child(&n[4], &n[5]);
  assert_bintreenode(&n[4], NULL, NULL, NULL);
  assert_bintreenode(&n[6], &n[5], NULL, NULL);
  assert_bintreenode(&n[7], &n[5], NULL, NULL);

  bintreenode_unchain_child(&n[1], &n[8]); // unabort check
  bintreenode_unchain_child(&n[1], NULL);  // unabort check
  bintreenode_unchain_child(NULL, &n[0]);  // unabort check
  bintreenode_unchain_child(NULL, NULL);   // unabort check

  finalize_bintreenodes(n, NUMBER_OF(n));
}

TEST(bintreenode, parent) {
  bintreenode_t n[2];
  initialize_bintreenodes(n, NUMBER_OF(n));
  bintreenode_chain_child_left(&n[0], &n[1]);
  ASSERT_EQ(NULL, bintreenode_parent(&n[0]));
  ASSERT_EQ(&n[0], bintreenode_parent(&n[1]));
  ASSERT_EQ(NULL, bintreenode_parent(NULL));
  finalize_bintreenodes(n, NUMBER_OF(n));
};

TEST(bintreenode, left) {
  bintreenode_t n[2];
  initialize_bintreenodes(n, NUMBER_OF(n));
  bintreenode_chain_child_left(&n[0], &n[1]);
  ASSERT_EQ(&n[1], bintreenode_left(&n[0]));
  ASSERT_EQ(NULL, bintreenode_left(&n[1]));
  ASSERT_EQ(NULL, bintreenode_left(NULL));
  finalize_bintreenodes(n, NUMBER_OF(n));
};

TEST(bintreenode, right) {
  bintreenode_t n[2];
  initialize_bintreenodes(n, NUMBER_OF(n));
  bintreenode_chain_child_right(&n[0], &n[1]);
  ASSERT_EQ(&n[1], bintreenode_right(&n[0]));
  ASSERT_EQ(NULL, bintreenode_right(&n[1]));
  ASSERT_EQ(NULL, bintreenode_right(NULL));
  finalize_bintreenodes(n, NUMBER_OF(n));
};

TEST(bintreenode, rotate_left) {
  bintreenode_t n[6];

  initialize_bintreenodes(n, NUMBER_OF(n));
  /*
   * n1
   *  + n0
   *  + n3 <- target
   *    + n2
   *    + n4
   */
  bintreenode_chain_child_left(&n[1], &n[0]);
  bintreenode_chain_child_right(&n[1], &n[3]);
  bintreenode_chain_child_left(&n[3], &n[2]);
  bintreenode_chain_child_right(&n[3], &n[4]);
  bintreenode_rotate_left(&n[3]);
  assert_bintreenode(&n[3], NULL, &n[1], &n[4]);
  assert_bintreenode(&n[1], &n[3], &n[0], &n[2]);
  assert_bintreenode(&n[4], &n[3], NULL, NULL);
  assert_bintreenode(&n[0], &n[1], NULL, NULL);
  assert_bintreenode(&n[2], &n[1], NULL, NULL);

  initialize_bintreenodes(n, NUMBER_OF(n));
  /*
   * n0
   *  + n2
   *    + n1
   *    + n4 <- target
   *      + n3
   *      + n5
   *  + NULL
   */
  bintreenode_chain_child_left(&n[0], &n[2]);
  bintreenode_chain_child_left(&n[2], &n[1]);
  bintreenode_chain_child_right(&n[2], &n[4]);
  bintreenode_chain_child_left(&n[4], &n[3]);
  bintreenode_chain_child_right(&n[4], &n[5]);
  bintreenode_rotate_left(&n[4]);
  assert_bintreenode(&n[0], NULL, &n[4], NULL);
  assert_bintreenode(&n[4], &n[0], &n[2], &n[5]);
  assert_bintreenode(&n[2], &n[4], &n[1], &n[3]);
  assert_bintreenode(&n[5], &n[4], NULL, NULL);
  assert_bintreenode(&n[1], &n[2], NULL, NULL);
  assert_bintreenode(&n[3], &n[2], NULL, NULL);

  initialize_bintreenodes(n, NUMBER_OF(n));
  /*
   * n0
   *  + NULL
   *  + n2
   *    + n1
   *    + n4 <- target
   *      + n3
   *      + n5
   */
  bintreenode_chain_child_right(&n[0], &n[2]);
  bintreenode_chain_child_left(&n[2], &n[1]);
  bintreenode_chain_child_right(&n[2], &n[4]);
  bintreenode_chain_child_left(&n[4], &n[3]);
  bintreenode_chain_child_right(&n[4], &n[5]);
  bintreenode_rotate_left(&n[4]);
  assert_bintreenode(&n[0], NULL, NULL, &n[4]);
  assert_bintreenode(&n[4], &n[0], &n[2], &n[5]);
  assert_bintreenode(&n[2], &n[4], &n[1], &n[3]);
  assert_bintreenode(&n[5], &n[4], NULL, NULL);
  assert_bintreenode(&n[1], &n[2], NULL, NULL);
  assert_bintreenode(&n[3], &n[2], NULL, NULL);

  initialize_bintreenodes(n, NUMBER_OF(n));
  /*
   *  + n1
   *    + n0
   *    + n3 <- target
   *      + NULL
   *      + n4
   */
  bintreenode_chain_child_left(&n[1], &n[0]);
  bintreenode_chain_child_right(&n[1], &n[3]);
  bintreenode_chain_child_right(&n[3], &n[4]);
  bintreenode_rotate_left(&n[3]);
  assert_bintreenode(&n[3], NULL, &n[1], &n[4]);
  assert_bintreenode(&n[1], &n[3], &n[0], NULL);
  assert_bintreenode(&n[4], &n[3], NULL, NULL);
  assert_bintreenode(&n[0], &n[1], NULL, NULL);

  initialize_bintreenodes(n, NUMBER_OF(n));
  /*
   *  + n1
   *    + n0
   *    + n3 <- target
   *      + n2
   *      + NULL
   */
  bintreenode_chain_child_left(&n[1], &n[0]);
  bintreenode_chain_child_right(&n[1], &n[3]);
  bintreenode_chain_child_left(&n[3], &n[2]);
  bintreenode_rotate_left(&n[3]);
  assert_bintreenode(&n[3], NULL, &n[1], NULL);
  assert_bintreenode(&n[1], &n[3], &n[0], &n[2]);
  assert_bintreenode(&n[0], &n[1], NULL, NULL);
  assert_bintreenode(&n[2], &n[1], NULL, NULL);

  finalize_bintreenodes(n, NUMBER_OF(n));
}

TEST(bintreenode, rotate_right) {
  bintreenode_t n[6];

  initialize_bintreenodes(n, NUMBER_OF(n));
  /*
   * n3
   *  + n1 <- target
   *    + n0
   *    + n2
   *  + n4
   */
  bintreenode_chain_child_left(&n[3], &n[1]);
  bintreenode_chain_child_right(&n[3], &n[4]);
  bintreenode_chain_child_left(&n[1], &n[0]);
  bintreenode_chain_child_right(&n[1], &n[2]);
  bintreenode_rotate_right(&n[1]);
  assert_bintreenode(&n[1], NULL, &n[0], &n[3]);
  assert_bintreenode(&n[0], &n[1], NULL, NULL);
  assert_bintreenode(&n[3], &n[1], &n[2], &n[4]);
  assert_bintreenode(&n[2], &n[3], NULL, NULL);
  assert_bintreenode(&n[4], &n[3], NULL, NULL);

  initialize_bintreenodes(n, NUMBER_OF(n));
  /*
   * n0
   *  + n4
   *    + n2 <- target
   *      + n1
   *      + n3
   *    + n5
   *  + NULL
   */
  bintreenode_chain_child_left(&n[0], &n[4]);
  bintreenode_chain_child_left(&n[4], &n[2]);
  bintreenode_chain_child_right(&n[4], &n[5]);
  bintreenode_chain_child_left(&n[2], &n[1]);
  bintreenode_chain_child_right(&n[2], &n[3]);
  bintreenode_rotate_right(&n[2]);
  assert_bintreenode(&n[0], NULL, &n[2], NULL);
  assert_bintreenode(&n[2], &n[0], &n[1], &n[4]);
  assert_bintreenode(&n[1], &n[2], NULL, NULL);
  assert_bintreenode(&n[4], &n[2], &n[3], &n[5]);
  assert_bintreenode(&n[3], &n[4], NULL, NULL);
  assert_bintreenode(&n[5], &n[4], NULL, NULL);

  initialize_bintreenodes(n, NUMBER_OF(n));
  /*
   * n0
   *  + NULL
   *  + n4
   *    + n2 <- target
   *      + n1
   *      + n3
   *    + n5
   */
  bintreenode_chain_child_right(&n[0], &n[4]);
  bintreenode_chain_child_left(&n[4], &n[2]);
  bintreenode_chain_child_right(&n[4], &n[5]);
  bintreenode_chain_child_left(&n[2], &n[1]);
  bintreenode_chain_child_right(&n[2], &n[3]);
  bintreenode_rotate_right(&n[2]);
  assert_bintreenode(&n[0], NULL, NULL, &n[2]);
  assert_bintreenode(&n[2], &n[0], &n[1], &n[4]);
  assert_bintreenode(&n[1], &n[2], NULL, NULL);
  assert_bintreenode(&n[4], &n[2], &n[3], &n[5]);
  assert_bintreenode(&n[3], &n[4], NULL, NULL);
  assert_bintreenode(&n[5], &n[4], NULL, NULL);

  initialize_bintreenodes(n, NUMBER_OF(n));
  /*
   * n3
   *  + n1 <- target
   *    + NULL
   *    + n2
   *  + n4
   */
  bintreenode_chain_child_left(&n[3], &n[1]);
  bintreenode_chain_child_right(&n[3], &n[4]);
  bintreenode_chain_child_right(&n[1], &n[2]);
  bintreenode_rotate_right(&n[1]);
  assert_bintreenode(&n[1], NULL, NULL, &n[3]);
  assert_bintreenode(&n[3], &n[1], &n[2], &n[4]);
  assert_bintreenode(&n[2], &n[3], NULL, NULL);
  assert_bintreenode(&n[4], &n[3], NULL, NULL);

  initialize_bintreenodes(n, NUMBER_OF(n));
  /*
   * n3
   *  + n1 <- target
   *    + n0
   *    + NULL
   *  + n4
   */
  bintreenode_chain_child_left(&n[3], &n[1]);
  bintreenode_chain_child_right(&n[3], &n[4]);
  bintreenode_chain_child_left(&n[1], &n[0]);
  bintreenode_rotate_right(&n[1]);
  assert_bintreenode(&n[1], NULL, &n[0], &n[3]);
  assert_bintreenode(&n[3], &n[1], NULL, &n[4]);
  assert_bintreenode(&n[4], &n[3], NULL, NULL);

  finalize_bintreenodes(n, NUMBER_OF(n));
}
