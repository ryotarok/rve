#ifndef CORE_ENVIRONMENT_H
#define CORE_ENVIRONMENT_H

#include "common/common.h"

#include "rve.h"

#define ENVIRONMENT_XREGISTER_NUM (32)

typedef struct environment_rec environment_t;

environment_t *environment_new(void);
void environment_delete(environment_t *env);
uint64_t environment_readreg(environment_t *env, uint8_t regid);
void environment_writereg(environment_t *env, uint8_t regid, uint64_t value);
void environment_load(environment_t *env, uint8_t regid, rveaddr_t addr);
void environment_store(environment_t *env, uint8_t regid, rveaddr_t addr);

#endif // CORE_ENVIRONMENT_H
