#ifndef COMMON_BINTREENODE_H
#define COMMON_BINTREENODE_H

#include "common.h"

typedef struct bintreenode_rec bintreenode_t;
struct bintreenode_rec {
  bintreenode_t *parent;
  bintreenode_t *left;
  bintreenode_t *right;
};

void bintreenode_initialize(bintreenode_t *node);
void bintreenode_finalize(bintreenode_t *node);
bool bintreenode_is_root(bintreenode_t *node);
bool bintreenode_is_parent(bintreenode_t *node, bintreenode_t *other);
bool bintreenode_is_left(bintreenode_t *node, bintreenode_t *other);
bool bintreenode_is_right(bintreenode_t *node, bintreenode_t *other);
void bintreenode_chain_child_left(bintreenode_t *node, bintreenode_t *other);
void bintreenode_chain_child_right(bintreenode_t *node, bintreenode_t *other);
void bintreenode_unchain(bintreenode_t *node);
void bintreenode_unchain_child(bintreenode_t *node, bintreenode_t *other);
bintreenode_t *bintreenode_parent(bintreenode_t *node);
bintreenode_t *bintreenode_left(bintreenode_t *node);
bintreenode_t *bintreenode_right(bintreenode_t *node);
void bintreenode_rotate_left(bintreenode_t *node);
void bintreenode_rotate_right(bintreenode_t *node);

#endif // COMMON_BINTREENODE_H
