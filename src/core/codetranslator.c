#include "codetranslator.h"

struct codetranslator_rec {
  struct {
    rveaddr_t startaddr;
    size_t readbytes;
  } target;

  struct {
    size_t wrotebytes;
    size_t tempvar_count;
  } host;

  memoryfragment_t *memoryfragment;
  codefragment_t *codefragment;
};

static void codetranslator_setup(codetranslator_t *translator,
                                 rveaddr_t startaddr,
                                 memoryfragment_t *memoryfragment,
                                 codefragment_t *codefragment);
static void codetranslator_write_prologue(codetranslator_t *translator);
static void codetranslator_write_epilogue(codetranslator_t *translator);

codetranslator_t *codetranslator_new(void) {
  codetranslator_t *translator =
      (codetranslator_t *)memory_alloc(sizeof(codetranslator_t));
  memset(translator, 0, sizeof(codetranslator_t));
  return translator;
}

void codetranslator_delete(codetranslator_t *translator) {
  memory_free(translator);
}

bool codetranslator_translate(codetranslator_t *translator, rveaddr_t startaddr,
                              memoryfragment_t *memoryfragment,
                              codefragment_t *codefragment) {
  codetranslator_setup(translator, startaddr, memoryfragment, codefragment);
  return false;
}

// private

static void codetranslator_setup(codetranslator_t *translator,
                                 rveaddr_t startaddr,
                                 memoryfragment_t *memoryfragment,
                                 codefragment_t *codefragment) {
  translator->target.startaddr = startaddr;
  translator->target.readbytes = 0;
  translator->host.wrotebytes = 0;
  translator->host.tempvar_count = 0;
  translator->memoryfragment = memoryfragment;
  translator->codefragment = codefragment;
}

static void codetranslator_write_prologue(codetranslator_t *translator) {}

static void codetranslator_write_epilogue(codetranslator_t *translator) {}
