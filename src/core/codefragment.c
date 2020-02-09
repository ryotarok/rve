#include "codefragment.h"
#include "fragmentbase.h"

#define CODEFRAGMENT_DATABYTES (4 * 1024) // 4KB

struct codefragment_rec {
  fragmentbase_t base;
  size_t data_bytes;
  uint8_t *data;
};

codefragment_t *codefragment_new(rveaddr_t addr) {
  codefragment_t *f = (codefragment_t *)memory_alloc(sizeof(codefragment_t));
  memset(f, 0, sizeof(codefragment_t));
  fragmentbase_initialize(&f->base, addr);

  // TODO: assign area from prealloced heap
  f->data = memory_alloc(CODEFRAGMENT_DATABYTES);
  f->data_bytes = CODEFRAGMENT_DATABYTES;
  return f;
}

void codefragment_delete(codefragment_t *fragment) {
  fragmentbase_finalize(&fragment->base);
  memory_free(fragment->data);
  memory_free(fragment);
}

rveaddr_t codefragment_addr(codefragment_t *fragment) {
  if (fragment == NULL) {
    return 0;
  }
  return fragmentbase_addr(&fragment->base);
}

uint8_t *codefragment_data(codefragment_t *fragment) {
  if (fragment == NULL) {
    return NULL;
  }
  return fragment->data;
}

size_t codefragment_data_bytes(codefragment_t *fragment) {
  if (fragment == NULL) {
    return 0;
  }
  return fragment->data_bytes;
}

codefragment_t *codefragment_find(codefragment_t *fragment, rveaddr_t addr) {
  return (codefragment_t *)fragmentbase_find(&fragment->base, addr);
}

codefragment_t *codefragment_insert(codefragment_t *fragment,
                                    codefragment_t *other) {
  fragmentbase_insert(&fragment->base, &other->base);
  // TODO: do splay?
  return fragment;
}

codefragment_t *codefragment_remove(codefragment_t *fragment) {
  fragmentbase_remove(&fragment->base);
  return fragment;
}
