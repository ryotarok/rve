#include "bintreenode.h"

void bintreenode_initialize(bintreenode_t *node) {
  if (node == NULL) {
    return;
  }
  node->parent = NULL;
  node->left = NULL;
  node->right = NULL;
}

void bintreenode_finalize(bintreenode_t *node) {
  UNREF(node);
  // do nothing
}

bool bintreenode_is_root(bintreenode_t *node) {
  if (node == NULL) {
    return false;
  }
  return (node->parent == NULL);
}

bool bintreenode_is_parent(bintreenode_t *node, bintreenode_t *other) {
  if (node == NULL) {
    return false;
  }
  return (node->parent == other);
}

bool bintreenode_is_left(bintreenode_t *node, bintreenode_t *other) {
  if (node == NULL) {
    return false;
  }
  return (node->left == other);
}

bool bintreenode_is_right(bintreenode_t *node, bintreenode_t *other) {
  if (node == NULL) {
    return false;
  }
  return (node->right == other);
}

void bintreenode_chain_child_left(bintreenode_t *node, bintreenode_t *other) {
  if ((node == NULL) || (other == NULL)) {
    return;
  }
  if ((node->left != NULL) || (other->parent != NULL)) {
    return;
  }
  other->parent = node;
  node->left = other;
}

void bintreenode_chain_child_right(bintreenode_t *node, bintreenode_t *other) {
  if ((node == NULL) || (other == NULL)) {
    return;
  }
  if ((node->right != NULL) || (other->parent != NULL)) {
    return;
  }
  other->parent = node;
  node->right = other;
}

void bintreenode_unchain(bintreenode_t *node) {
  if ((node == NULL) || (node->parent == NULL)) {
    return;
  }
  bintreenode_unchain_child(node->parent, node);
}

void bintreenode_unchain_child(bintreenode_t *node, bintreenode_t *other) {
  if ((node == NULL) || (other == NULL)) {
    return;
  }
  if (node->left == other) {
    node->left = NULL;
  } else if (node->right == other) {
    node->right = NULL;
  } else {
    return;
  }
  other->parent = NULL;
}

bintreenode_t *bintreenode_parent(bintreenode_t *node) {
  if (node == NULL) {
    return NULL;
  }
  return node->parent;
}

bintreenode_t *bintreenode_left(bintreenode_t *node) {
  if (node == NULL) {
    return NULL;
  }
  return node->left;
}

bintreenode_t *bintreenode_right(bintreenode_t *node) {
  if (node == NULL) {
    return NULL;
  }
  return node->right;
}

void bintreenode_rotate_left(bintreenode_t *node) {
  bintreenode_t *parent = bintreenode_parent(node);
  bintreenode_t *parent_x2 = bintreenode_parent(parent);
  bool is_left_parent = bintreenode_is_left(parent_x2, parent);
  bool is_right_parent = bintreenode_is_right(parent_x2, parent);

  bintreenode_unchain_child(parent_x2, parent);
  bintreenode_unchain_child(parent, node);

  bintreenode_t *left = bintreenode_left(node);
  bintreenode_unchain_child(node, left);

  bintreenode_chain_child_left(node, parent);
  bintreenode_chain_child_right(parent, left);

  if (is_left_parent) {
    bintreenode_chain_child_left(parent_x2, node);
  } else if (is_right_parent) {
    bintreenode_chain_child_right(parent_x2, node);
  }
}

void bintreenode_rotate_right(bintreenode_t *node) {
  bintreenode_t *parent = bintreenode_parent(node);
  bintreenode_t *parent_x2 = bintreenode_parent(parent);
  bool is_left_parent = bintreenode_is_left(parent_x2, parent);
  bool is_right_parent = bintreenode_is_right(parent_x2, parent);

  bintreenode_unchain_child(parent_x2, parent);
  bintreenode_unchain_child(parent, node);

  bintreenode_t *right = bintreenode_right(node);
  bintreenode_unchain_child(node, right);

  bintreenode_chain_child_right(node, parent);
  bintreenode_chain_child_left(parent, right);

  if (is_left_parent) {
    bintreenode_chain_child_left(parent_x2, node);
  } else if (is_right_parent) {
    bintreenode_chain_child_right(parent_x2, node);
  }
}
