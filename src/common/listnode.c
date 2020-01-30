#include "listnode.h"

void listnode_initialize(listnode_t *node) {
  node->prev = node;
  node->next = node;
}

void listnode_finalize(listnode_t *node) {
  UNREF(node);
  // do nothing
}

bool listnode_is_alone(listnode_t *node) {
  return ((node->prev == node) && (node->next == node));
}

bool listnode_is_prev(listnode_t *node, listnode_t *other) {
  return (node->prev == other);
}

bool listnode_is_next(listnode_t *node, listnode_t *other) {
  return (node->next == other);
}

void listnode_insert_before(listnode_t *node, listnode_t *other) {
  other->prev = node->prev;
  other->next = node;
  node->prev->next = other;
  node->prev = other;
}

void listnode_insert_after(listnode_t *node, listnode_t *other) {
  other->prev = node;
  other->next = node->next;
  node->next->prev = other;
  node->next = other;
}

void listnode_remove(listnode_t *node) {
  node->prev->next = node->next;
  node->next->prev = node->prev;
  node->prev = node;
  node->next = node;
}

listnode_t *listnode_prev(listnode_t *node) { return node->prev; }

listnode_t *listnode_next(listnode_t *node) { return node->next; }
