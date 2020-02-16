#include "envresult.h"

envresult_t *envresult_set_success(envresult_t *res) {
  if (res == NULL) {
    return NULL;
  }

  res->success = true;
  res->error = ENVERROR_NONE;
  return res;
}

envresult_t *envresult_set_error(envresult_t *res, enverror_t error) {
  if (res == NULL) {
    return NULL;
  }

  res->success = false;
  res->error = error;
  return res;
}

bool envresult_is_success(envresult_t *res) {
  if (res == NULL) {
    return false;
  }
  return res->success;
}

enverror_t envresult_error(envresult_t *res) {
  if (res == NULL) {
    return ENVERROR_NONE;
  }
  return res->error;
}
