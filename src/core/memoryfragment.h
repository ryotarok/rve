#ifndef CORE_MEMORYFRAGMENT_H
#define CORE_MEMORYFRAGMENT_H

#include "common/common.h"

#include "rve.h"

typedef struct memoryfragment_rec memoryfragment_t;

memoryfragment_t *memoryfragment_new(rveaddr_t addr);
void memoryfragment_delete(memoryfragment_t *fragment);
rveaddr_t memoryfragment_addr(memoryfragment_t *fragment);
uint8_t *memoryfragment_data(memoryfragment_t *fragment);
size_t memoryfragment_data_bytes(memoryfragment_t *fragment);
memoryfragment_t *memoryfragment_find(memoryfragment_t *fragment,
                                      rveaddr_t addr);
memoryfragment_t *memoryfragment_insert(memoryfragment_t *fragment,
                                        memoryfragment_t *other);
memoryfragment_t *memoryfragment_remove(memoryfragment_t *fragment);

#endif // CORE_MEMORYFRAGMENT_H