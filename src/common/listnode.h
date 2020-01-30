#ifndef COMMON_LISTNODE_H
#define COMMON_LISTNODE_H

#include "common.h"

typedef struct listnode_rec listnode_t;
struct listnode_rec {
  listnode_t *prev;
  listnode_t *next;
};

void listnode_initialize(listnode_t *node);
void listnode_finalize(listnode_t *node);
bool listnode_is_alone(listnode_t *node);
bool listnode_is_prev(listnode_t *node, listnode_t *other);
bool listnode_is_next(listnode_t *node, listnode_t *other);
void listnode_insert_before(listnode_t *node, listnode_t *other);
void listnode_insert_after(listnode_t *node, listnode_t *other);
void listnode_remove(listnode_t *node);
listnode_t *listnode_prev(listnode_t *node);
listnode_t *listnode_next(listnode_t *node);

#endif // COMMON_LISTNODE_H
