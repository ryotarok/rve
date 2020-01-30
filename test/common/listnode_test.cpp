#include "gtest/gtest.h"

extern "C" {
#include "common/listnode.h"
}

static void initialize_listnodes(listnode_t *nodes, int32_t nodes_length) {
  for (int32_t i = 0; i < nodes_length; ++i) {
    listnode_initialize(&nodes[i]);
  }
}

static void finalize_listnodes(listnode_t *nodes, int32_t nodes_length) {
  for (int32_t i = 0; i < nodes_length; ++i) {
    listnode_finalize(&nodes[i]);
  }
}

static void assert_listnode(listnode_t *node, listnode_t *expected_prev,
                            listnode_t *expected_next) {
  ASSERT_EQ(expected_prev, node->prev);
  ASSERT_EQ(expected_next, node->next);
}

TEST(listnode, initialize_and_finalize) {
  listnode_t n[1];
  initialize_listnodes(n, NUMBER_OF(n));
  assert_listnode(&n[0], &n[0], &n[0]);
  finalize_listnodes(n, NUMBER_OF(n));
}

TEST(listnode, is_alone) {
  listnode_t n[2];
  initialize_listnodes(n, NUMBER_OF(n));

  ASSERT_TRUE(listnode_is_alone(&n[0]));

  n[0].prev = &n[1];
  n[0].next = &n[1];
  n[1].prev = &n[0];
  n[1].next = &n[0];
  ASSERT_FALSE(listnode_is_alone(&n[0]));
  ASSERT_FALSE(listnode_is_alone(&n[1]));

  finalize_listnodes(n, NUMBER_OF(n));
}

TEST(listnode, is_prev_and_is_next) {
  listnode_t n[3];
  initialize_listnodes(n, NUMBER_OF(n));
  listnode_insert_before(&n[0], &n[1]);
  listnode_insert_before(&n[0], &n[2]);

  ASSERT_TRUE(listnode_is_prev(&n[1], &n[0]));
  ASSERT_FALSE(listnode_is_prev(&n[1], &n[2]));

  ASSERT_FALSE(listnode_is_next(&n[1], &n[0]));
  ASSERT_TRUE(listnode_is_next(&n[1], &n[2]));

  finalize_listnodes(n, NUMBER_OF(n));
}

TEST(listnode, insert_before) {
  listnode_t n[3];
  initialize_listnodes(n, NUMBER_OF(n));

  listnode_insert_before(&n[0], &n[1]);
  assert_listnode(&n[0], &n[1], &n[1]);
  assert_listnode(&n[1], &n[0], &n[0]);

  listnode_insert_before(&n[0], &n[2]);
  assert_listnode(&n[0], &n[2], &n[1]);
  assert_listnode(&n[1], &n[0], &n[2]);
  assert_listnode(&n[2], &n[1], &n[0]);

  finalize_listnodes(n, NUMBER_OF(n));
}

TEST(listnode, insert_after) {
  listnode_t n[3];
  initialize_listnodes(n, NUMBER_OF(n));

  listnode_insert_after(&n[0], &n[1]);
  assert_listnode(&n[0], &n[1], &n[1]);
  assert_listnode(&n[1], &n[0], &n[0]);

  listnode_insert_after(&n[0], &n[2]);
  assert_listnode(&n[0], &n[1], &n[2]);
  assert_listnode(&n[1], &n[2], &n[0]);
  assert_listnode(&n[2], &n[0], &n[1]);

  finalize_listnodes(n, NUMBER_OF(n));
}

TEST(listnode, remove) {
  listnode_t n[3];
  initialize_listnodes(n, NUMBER_OF(n));
  listnode_insert_before(&n[0], &n[1]);
  listnode_insert_before(&n[0], &n[2]);

  listnode_remove(&n[1]);
  assert_listnode(&n[0], &n[2], &n[2]);
  assert_listnode(&n[1], &n[1], &n[1]);
  assert_listnode(&n[2], &n[0], &n[0]);

  listnode_remove(&n[2]);
  assert_listnode(&n[0], &n[0], &n[0]);
  assert_listnode(&n[1], &n[1], &n[1]);
  assert_listnode(&n[2], &n[2], &n[2]);

  finalize_listnodes(n, NUMBER_OF(n));
}

TEST(listnode, prev_and_next) {
  listnode_t n[3];
  initialize_listnodes(n, NUMBER_OF(n));
  listnode_insert_before(&n[0], &n[1]);
  listnode_insert_before(&n[0], &n[2]);

  ASSERT_EQ(&n[0], listnode_prev(&n[1]));
  ASSERT_EQ(&n[2], listnode_next(&n[1]));

  finalize_listnodes(n, NUMBER_OF(n));
}
