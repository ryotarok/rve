#ifndef CORE_CODETRANSLATOR_H
#define CORE_CODETRANSLATOR_H

#include "common/common.h"

#include "rve.h"

#include "codefragment.h"
#include "memoryfragment.h"

typedef struct codetranslator_rec codetranslator_t;

codetranslator_t *codetranslator_new(void);
void codetranslator_delete(codetranslator_t *translator);
bool codetranslator_translate(codetranslator_t *translator, rveaddr_t startaddr,
                              memoryfragment_t *memoryfragment,
                              codefragment_t *codefragment);

#endif // CORE_CODETRANSLATOR_H
