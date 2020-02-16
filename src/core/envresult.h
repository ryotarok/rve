#ifndef CORE_ENVRESULT_H
#define CORE_ENVRESULT_H

#include "common/common.h"

#include "rve.h"

enum enverror_enum {
  ENVERROR_NONE,
  ENVERROR_READMEMORY,
  ENVERROR_WRITEMEMORY,
};
typedef enum enverror_enum enverror_t;

typedef struct envresult_rec envresult_t;
struct envresult_rec {
  bool success;
  enverror_t error;
};
envresult_t *envresult_set_success(envresult_t *res);
envresult_t *envresult_set_error(envresult_t *res, enverror_t error);
bool envresult_is_success(envresult_t *res);
enverror_t envresult_error(envresult_t *res);

#endif // CORE_ENVRESULT_H
