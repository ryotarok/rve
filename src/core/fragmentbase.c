#include "fragmentbase.h"

static bool fragmentbase_is_leaf(fragmentbase_t *base);
static void fragmentbase_unchain(fragmentbase_t *base);

void fragmentbase_initialize(fragmentbase_t *base, rveaddr_t addr) {
  bintreenode_initialize(&base->node);
  base->addr = addr;
}

void fragmentbase_finalize(fragmentbase_t *base) {
  bintreenode_finalize(&base->node);
}

rveaddr_t fragmentbase_addr(fragmentbase_t *base) {
  if (base == NULL) {
    return 0;
  }
  return base->addr;
}

fragmentbase_t *fragmentbase_left(fragmentbase_t *base) {
  return (fragmentbase_t *)bintreenode_left(&base->node);
}

fragmentbase_t *fragmentbase_right(fragmentbase_t *base) {
  return (fragmentbase_t *)bintreenode_right(&base->node);
}

fragmentbase_t *fragmentbase_find(fragmentbase_t *base, rveaddr_t addr) {
  if (base == NULL) {
    return NULL;
  }

  fragmentbase_t *b = base;
  while (b != NULL) {
    if (addr < b->addr) {
      b = (fragmentbase_t *)bintreenode_left(&b->node);
    } else if (b->addr < addr) {
      b = (fragmentbase_t *)bintreenode_right(&b->node);
    } else {
      return b;
    }
  }
  return NULL;
}

fragmentbase_t *fragmentbase_find_minnode(fragmentbase_t *base) {
  if (base == NULL) {
    return NULL;
  }

  fragmentbase_t *b = base;
  while (bintreenode_left(&b->node) != NULL) {
    b = (fragmentbase_t *)bintreenode_left(&b->node);
  }
  return b;
}

fragmentbase_t *fragmentbase_find_maxnode(fragmentbase_t *base) {
  if (base == NULL) {
    return NULL;
  }

  fragmentbase_t *b = base;
  while (bintreenode_right(&b->node) != NULL) {
    b = (fragmentbase_t *)bintreenode_right(&b->node);
  }
  return b;
}

fragmentbase_t *fragmentbase_root(fragmentbase_t *base) {
  if (base == NULL) {
    return NULL;
  }

  fragmentbase_t *b = base;
  while (bintreenode_parent(&b->node) != NULL) {
    b = (fragmentbase_t *)bintreenode_parent(&b->node);
  }
  return b;
}

void fragmentbase_insert(fragmentbase_t *base, fragmentbase_t *other) {
  if ((base == NULL) || (other == NULL)) {
    return;
  }
  fragmentbase_t *b = base;
  fragmentbase_t *prevb = b;
  while (b != NULL) {
    if (other->addr < b->addr) {
      prevb = b;
      b = fragmentbase_left(b);
    } else if (b->addr < other->addr) {
      prevb = b;
      b = fragmentbase_right(b);
    } else {
      // found same addr fragment
      return;
    }
  }

  if (other->addr < prevb->addr) {
    bintreenode_chain_child_left(&prevb->node, &other->node);
  } else if (prevb->addr < other->addr) {
    bintreenode_chain_child_right(&prevb->node, &other->node);
  }
}

void fragmentbase_remove(fragmentbase_t *base) {
  if (fragmentbase_is_leaf(base)) {
    fragmentbase_unchain(base);
  }
}

static bool fragmentbase_is_leaf(fragmentbase_t *base) {
  return ((fragmentbase_left(base) == NULL) &&
          (fragmentbase_right(base) == NULL))
             ? true
             : false;
}

static void fragmentbase_unchain(fragmentbase_t *base) {
  bintreenode_unchain(&base->node);
}
