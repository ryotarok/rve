#include "memoryfragment.h"
#include "fragmentbase.h"

#define MEMORYFRAGMENT_DATABYTES (16 * 4 * 1024) // 64KB

struct memoryfragment_rec {
  fragmentbase_t base;
  size_t data_bytes;
  uint8_t *data;
};

memoryfragment_t *memoryfragment_new(rveaddr_t addr) {
  memoryfragment_t *f =
      (memoryfragment_t *)memory_alloc(sizeof(memoryfragment_t));
  memset(f, 0, sizeof(memoryfragment_t));
  fragmentbase_initialize(&f->base, addr);

  // TODO: assign area from prealloced heap
  f->data = memory_alloc(MEMORYFRAGMENT_DATABYTES);
  f->data_bytes = MEMORYFRAGMENT_DATABYTES;
  return f;
}

void memoryfragment_delete(memoryfragment_t *fragment) {
  fragmentbase_finalize(&fragment->base);
  memory_free(fragment->data);
  memory_free(fragment);
}

rveaddr_t memoryfragment_addr(memoryfragment_t *fragment) {
  if (fragment == NULL) {
    return 0;
  }
  return fragmentbase_addr(&fragment->base);
}

uint8_t *memoryfragment_data(memoryfragment_t *fragment) {
  if (fragment == NULL) {
    return NULL;
  }
  return fragment->data;
}

size_t memoryfragment_data_bytes(memoryfragment_t *fragment) {
  if (fragment == NULL) {
    return 0;
  }
  return fragment->data_bytes;
}

memoryfragment_t *memoryfragment_find(memoryfragment_t *fragment,
                                      rveaddr_t addr) {
  return (memoryfragment_t *)fragmentbase_find(&fragment->base, addr);
}

memoryfragment_t *memoryfragment_insert(memoryfragment_t *fragment,
                                        memoryfragment_t *other) {
  fragmentbase_insert(&fragment->base, &other->base);
  // TODO: do splay?
  return fragment;
}

memoryfragment_t *memoryfragment_remove(memoryfragment_t *fragment) {
  fragmentbase_remove(&fragment->base);
  return fragment;
}
