#include <stdio.h>
#include <stdlib.h>

typedef struct map_node MAP_NODE;
typedef struct hash_table HASH_TABLE;
typedef struct hash_methods HASH_METHODS;

struct map_node {
  const void *org_address;
  void *cop_address;
  MAP_NODE *next;
};

struct hash_table {
  int size;
  MAP_NODE **buckets;
  HASH_METHODS *method;
};


typedef int (*add_ht_ins_next)(HASH_TABLE**,const void*,void*);
typedef void* (*add_ht_traverse)(HASH_TABLE*,const void*);
typedef void (*add_ht_destroy)(HASH_TABLE*,MAP_NODE**);

struct hash_methods {
  add_ht_ins_next HT_ins_next;
  add_ht_traverse HT_traverse;
  add_ht_destroy HT_destroy;
};

void init_hash(HASH_TABLE **table,int size);
int ht_ins_next(HASH_TABLE **table,const void *org,void *cop);
unsigned hash_address(const void* ptr,int capacity);
void *ht_traverse(HASH_TABLE *table,const void *org);
void ht_destroy(HASH_TABLE *table,MAP_NODE **pos);

#define HASH_PRIME 0x45d9f3b

//-----------------------------------------------------------------------------



