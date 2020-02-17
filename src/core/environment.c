#include "environment.h"

struct environment_rec {
  uint64_t xregs[ENVIRONMENT_XREGISTER_NUM];
};

environment_t *environment_new(void) {
  environment_t *env = (environment_t *)memory_alloc(sizeof(environment_t));
  memset(env, 0, sizeof(environment_t));
  return env;
}

void environment_delete(environment_t *env) { memory_free(env); }

uint64_t environment_readreg(environment_t *env, uint8_t regid) {
  if (env == NULL) {
    return 0;
  }

  if (regid == 0) {
    return 0;
  } else if (0 < regid && regid < ENVIRONMENT_XREGISTER_NUM) {
    return env->xregs[regid];
  } else {
    return 0;
  }
}

void environment_writereg(environment_t *env, uint8_t regid, uint64_t value) {
  if (env == NULL) {
    return;
  }

  if (regid == 0) {
    return;
  } else if (0 < regid && regid < ENVIRONMENT_XREGISTER_NUM) {
    env->xregs[regid] = value;
    return;
  } else {
    return;
  }
}

void environment_load(environment_t *env, uint8_t regid, rveaddr_t addr) {}
void environment_store(environment_t *env, uint8_t regid, rveaddr_t addr) {}
