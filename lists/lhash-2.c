#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "lhash.h"


void init_hash(HASH_TABLE **table,int size) {
  HASH_TABLE *ptr_table = *table;
  if (ptr_table)
    return;

  if ((ptr_table = malloc(sizeof(HASH_TABLE))) == NULL)
    return;

  ptr_table->size = size;
  if ((ptr_table->buckets = (MAP_NODE**)malloc((size +1) * sizeof(MAP_NODE*))) == NULL)
    exit(-1);

  //set to 0
  MAP_NODE *ptr_nul = ptr_table->buckets[0];
  int count;
  for (count = 0;count <= size+1;count ++)
    ptr_nul = NULL;

  if ((ptr_table->method = malloc(sizeof(HASH_METHODS*))) == NULL)
    exit(-1);

  ptr_table->method->HT_ins_next = ht_ins_next;
  ptr_table->method->HT_traverse = ht_traverse;
  ptr_table->method->HT_destroy = ht_destroy;

  *table = ptr_table;
}


unsigned hash_address(const void* ptr,int capacity) {
  uintptr_t val_address = (uintptr_t)ptr;
  val_address = (val_address ^ (val_address << 16)) * HASH_PRIME;
  val_address = (val_address ^ (val_address << 16)) * HASH_PRIME;
  val_address = (val_address ^ (val_address << 16));
  return val_address % capacity;
}

int ht_ins_next(HASH_TABLE **table,const void *org,void *cop) {
  HASH_TABLE *ptr_table = *table;
  if (!ptr_table || !ptr_table->buckets)
    return -1;

  int capacity = ptr_table->size;
  unsigned pos_new_elmt = hash_address(org,capacity);

  MAP_NODE *new_elmt = NULL;
  if (ptr_table->buckets[pos_new_elmt] == NULL) {

    if ((new_elmt = malloc(sizeof(MAP_NODE))) == NULL)
      return -3;
    ptr_table->buckets[pos_new_elmt] = new_elmt;
  }else{
    new_elmt->next = ptr_table->buckets[pos_new_elmt];
    ptr_table->buckets[pos_new_elmt] = new_elmt;
  }

  new_elmt->org_address = org;
  new_elmt->cop_address = cop;
  
  *table = ptr_table;
  return 0;
} 

void *ht_traverse(HASH_TABLE *table,const void *org) {
  int capacity = table->size;
  unsigned pos_new_elmt = hash_address(org,capacity);

  MAP_NODE *ptr = NULL;
  for (ptr = table->buckets[pos_new_elmt];ptr != NULL;ptr = ptr->next) {
    if (ptr->org_address == org)
      return ptr->cop_address;
  }
  return NULL;
}

void ht_destroy(HASH_TABLE *table,MAP_NODE **pos) {
  int max_size = table->size,c = 0;
  MAP_NODE *ptr_list = NULL;
  for (c;c < max_size;c++) {
    if (table->buckets[c]) {
      for (ptr_list = table->buckets[c];ptr_list->next;ptr_list = ptr_list->next)
	free(ptr_list->next);
      free(table->buckets[c]);
    }
  }
}
  


  
