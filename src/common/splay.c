#include "splay.h"

static void splay_zig(bintreenode_t *node, bintreenode_t *parent);
static void splay_zig_zig(bintreenode_t *node, bintreenode_t *parent,
                          bool is_left_left, bool is_right_right);
static void splay_zig_zag(bintreenode_t *node, bool is_left_right,
                          bool is_right_left);

bintreenode_t *splay(bintreenode_t *node) {
  for (;;) {
    bintreenode_t *parent = bintreenode_parent(node);
    if (parent == NULL) {
      break;
    }

    bintreenode_t *parent_x2 = bintreenode_parent(parent);

    if (parent_x2 == NULL) {
      splay_zig(node, parent);
    } else {
      bool is_left_left = bintreenode_is_left(parent_x2, parent) &&
                          bintreenode_is_left(parent, node);
      bool is_right_right = bintreenode_is_right(parent_x2, parent) &&
                            bintreenode_is_right(parent, node);
      bool is_left_right = bintreenode_is_left(parent_x2, parent) &&
                           bintreenode_is_right(parent, node);
      bool is_right_left = bintreenode_is_right(parent_x2, parent) &&
                           bintreenode_is_left(parent, node);

      if (is_left_left || is_right_right) {
        splay_zig_zig(node, parent, is_left_left, is_right_right);
      } else if (is_left_right || is_right_left) {
        splay_zig_zag(node, is_left_right, is_right_left);
      }
    }
  }
  return node;
}

static void splay_zig(bintreenode_t *node, bintreenode_t *parent) {
  bool is_left = bintreenode_is_left(parent, node);
  bool is_right = bintreenode_is_right(parent, node);

  if (is_left) {
    bintreenode_rotate_right(node);
  } else if (is_right) {
    bintreenode_rotate_left(node);
  }
}

static void splay_zig_zig(bintreenode_t *node, bintreenode_t *parent,
                          bool is_left_left, bool is_right_right) {
  if (is_left_left) {
    bintreenode_rotate_right(parent);
    bintreenode_rotate_right(node);
  } else if (is_right_right) {
    bintreenode_rotate_left(parent);
    bintreenode_rotate_left(node);
  }
}

static void splay_zig_zag(bintreenode_t *node, bool is_left_right,
                          bool is_right_left) {
  if (is_left_right) {
    bintreenode_rotate_left(node);
    bintreenode_rotate_right(node);
  }
  if (is_right_left) {
    bintreenode_rotate_right(node);
    bintreenode_rotate_left(node);
  }
}
