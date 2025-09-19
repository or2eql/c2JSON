//
// Created by oreql on 15.08.25.
//

#include "dllist.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
int init_dlist(DLIST **dlist) {
    DLIST *ptr_dlist = *dlist;
    if (ptr_dlist) {
        return -1;
    }
    if ((ptr_dlist = malloc(sizeof(DLIST))) == NULL) {
        return -2;
    }
    ptr_dlist->head = NULL;
    ptr_dlist->tail = NULL;
    ptr_dlist->size = 0;
    //Methods
    ptr_dlist->destroy_dlist = destroy_dlist;
    ptr_dlist->ins_next = ins_next;
    ptr_dlist->ins_prev = ins_prev;
    ptr_dlist->rem_lelmt = remove_lelmt;
    ptr_dlist->STR_ID = create_name_value;

    *dlist = ptr_dlist;
    return 0;
}

int remove_lelmt(DLIST *dlist, DNODE *dnode,void **data) {
  if (dlist) {
    if ((!dlist->head && !dlist->tail) || !dnode)
      return -1;
  }else{
    return -2;
  }
  if (data)
    *data = dnode->data;
  if (dnode == dlist->head) {
    dlist->head = dnode->next;
    if (!dlist->head) {
      dlist->tail = NULL;
    }else{
      dnode->next->prev = NULL;
    }
  }else{

    dnode->prev->next = dnode->next;
    if (!dnode->next) {
      dlist->tail = dnode->prev;
    }else{
      dnode->next->prev = dnode->prev;
    }
  }
  if (dnode->name_value)
    free(((char*)dnode->name_value));
  free(dnode);
  dlist->size --;
  return dlist->size;
}

int destroy_dlist(DLIST **dlist) {
  if (!dlist)
    return 0;
  DLIST *ptr_dlist = *dlist;
  int r = 0;
  void **data = (void**)ptr_dlist->tail->data;
  while (ptr_dlist->size > 0) {
    remove_lelmt(ptr_dlist,ptr_dlist->tail,(void **)&data); 
  }
  free(ptr_dlist);
  *dlist = ptr_dlist;
}


DLIST *ins_next(DLIST *dlist,DNODE *dnode,void *data) {
  if(!dlist || (!dnode && dlist->size != 0))
    return NULL;

  DNODE *new_elmt = NULL;
  if ((new_elmt = malloc(sizeof(DNODE))) == NULL)
    return NULL;
  if (data)
    new_elmt->data = (void *) data;
  if (!dlist->size) {
    dlist->head = new_elmt;
    dlist->head->prev = NULL;
    dlist->head->next = NULL;
    dlist->tail = new_elmt;
  }else{
    new_elmt->next = dnode->next;
    new_elmt->prev = dnode;
    if (!dnode->next) {
      dlist->tail = new_elmt;
    }else{
      new_elmt->next->prev = new_elmt;
    }
    dnode->next = new_elmt;
  }
  new_elmt->ID = dlist->size ++;
  new_elmt->name_value = NULL;
  return dlist;
}

DLIST *ins_prev(DLIST *dlist,DNODE *dnode,void *data) {
  if (!dlist || (!dnode && dlist->size != 0))
    return NULL;

  DNODE *new_elmt = NULL;
  if ((new_elmt = malloc(sizeof(DNODE))) == NULL)
    return NULL;
  if (data)
    new_elmt->data = (void*) data;
  if (!dlist->size) {
    dlist->head = new_elmt;
    dlist->head->prev = NULL;
    dlist->head->next = NULL;
    dlist->tail = new_elmt;
  }else{
    new_elmt->next = dnode;
    new_elmt->prev = dnode->prev;
    if (!dnode->prev) {
      dlist->head = new_elmt;
    }else{
      dnode->prev->next = new_elmt;
    }
    dnode->prev = new_elmt;
  }
  new_elmt->ID = dlist->size ++;
  new_elmt->name_value = NULL;
  return dlist;
}


char *create_name_value(DNODE *dnode,const char *str) {
  if (!dnode || !str)
    return 0;
	
  int len = strlen(str) +1;
  if ((dnode->name_value = malloc(len *(sizeof(char)))) == NULL)
    return 0;
  strncpy(((char*)dnode->name_value),str,len);
  return dnode->name_value;
}

	


