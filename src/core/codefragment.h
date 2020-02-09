#ifndef CORE_CODEFRAGMENT_H
#define CORE_CODEFRAGMENT_H

#include "common/common.h"

#include "rve.h"

typedef struct codefragment_rec codefragment_t;

codefragment_t *codefragment_new(rveaddr_t addr);
void codefragment_delete(codefragment_t *fragment);
rveaddr_t codefragment_addr(codefragment_t *fragment);
uint8_t *codefragment_data(codefragment_t *fragment);
size_t codefragment_data_bytes(codefragment_t *fragment);
codefragment_t *codefragment_find(codefragment_t *fragment, rveaddr_t addr);
codefragment_t *codefragment_insert(codefragment_t *fragment,
                                    codefragment_t *other);
codefragment_t *codefragment_remove(codefragment_t *fragment);

#endif // CORE_CODEFRAGMENT_H
