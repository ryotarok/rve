#include "memory.h"
#include "listnode.h"

typedef struct memorynode_rec memorynode_t;
struct memorynode_rec {
  listnode_t node;
  size_t data_bytes;
  uint8_t data[1]; // variable length
};

typedef struct memorydata_rec memorydata_t;
struct memorydata_rec {
  listnode_t nodelist;
  memoryconfig_t config;
  size_t nodelist_length;
};

static memorydata_t memorydata;

void memory_initialize(memoryconfig_t *config) {
  if (config == NULL) {
    return;
  }
  listnode_initialize(&memorydata.nodelist);
  memorydata.nodelist_length = 0;
  memorydata.config = *config;
}

void memory_finalize(void) {
  // do nothing
}

void *memory_alloc(size_t bytes) {
  if (bytes == 0) {
    return NULL;
  }

  memorynode_t *m = malloc(sizeof(memorynode_t) + bytes);
  listnode_initialize(&m->node);
  m->data_bytes = bytes;

  listnode_insert_before(&memorydata.nodelist, &m->node);
  ++memorydata.nodelist_length;

  return m->data;
}

void memory_free(void *ptr) {
  if (ptr == NULL) {
    return;
  }

  memorynode_t *m = (memorynode_t *)listnode_next(&memorydata.nodelist);
  while ((listnode_t *)m != &memorydata.nodelist) {
    if (m->data == ptr) {
      listnode_remove(&m->node);
      --memorydata.nodelist_length;
      free(m);
      return;
    }
    m = (memorynode_t *)listnode_next(&m->node);
  }
  // ?
}

int32_t memory_leaks() {
  if (!memorydata.config.leakcheck) {
    return 0;
  }
  return memorydata.nodelist_length;
}

void memory_dump_leaks() {
  if ((!memorydata.config.leakcheck) || (!memorydata.config.verbose)) {
    return;
  }

  printf("memory\n");
  printf("  leaks: %zu\n", memorydata.nodelist_length);
  if (memorydata.nodelist_length == 0) {
    return;
  }

  printf("  leaked address:\n");
  memorynode_t *m = (memorynode_t *)listnode_next(&memorydata.nodelist);
  while ((listnode_t *)m != &memorydata.nodelist) {
    printf("    %p: ", m->data);
    printf("%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x "
           "%02x %02x %02x",
           m->data[0], m->data[1], m->data[2], m->data[3], m->data[4],
           m->data[5], m->data[6], m->data[7], m->data[8], m->data[9],
           m->data[10], m->data[11], m->data[12], m->data[13], m->data[14],
           m->data[15]);
    printf(" | ");
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", m->data[0], m->data[1],
           m->data[2], m->data[3], m->data[4], m->data[5], m->data[6],
           m->data[7], m->data[8], m->data[9], m->data[10], m->data[11],
           m->data[12], m->data[13], m->data[14], m->data[15]);
    m = (memorynode_t *)listnode_next(&m->node);
  }
}
