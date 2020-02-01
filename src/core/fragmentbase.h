#ifndef CORE_FRAGMENTBASE_H
#define CORE_FRAGMENTBASE_H

#include "common/common.h"

#include "core/rve.h"

typedef struct fragmentbase_rec fragmentbase_t;
struct fragmentbase_rec {
  bintreenode_t node;
  rveaddr_t addr;
};

void fragmentbase_initialize(fragmentbase_t *base, rveaddr_t addr);
void fragmentbase_finalize(fragmentbase_t *base);
rveaddr_t fragmentbase_addr(fragmentbase_t *base);
fragmentbase_t *fragmentbase_left(fragmentbase_t *base);
fragmentbase_t *fragmentbase_right(fragmentbase_t *base);
fragmentbase_t *fragmentbase_find(fragmentbase_t *base, rveaddr_t addr);
fragmentbase_t *fragmentbase_find_minnode(fragmentbase_t *base);
fragmentbase_t *fragmentbase_find_maxnode(fragmentbase_t *base);
fragmentbase_t *fragmentbase_root(fragmentbase_t *base);
void fragmentbase_insert(fragmentbase_t *base, fragmentbase_t *other);
void fragmentbase_remove(fragmentbase_t *base);

#endif // CORE_FRAGMENTBASE_H
