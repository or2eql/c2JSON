//cllist
/*
 erstellt: 25. Feb 2025
 zirkulär einfach verkettete Listen
*/
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./cllist.h"

//initialisiere eine einfach verkettete zirkuläre Liste
void clist_init(CLIST *clist_) {
  if (!clist_)
    return;
  clist_->head = NULL;
  clist_->size = 0;
  //CLL - Methoden
  clist_->rem_list = clist_remove;
  clist_->destr = clist_destr;
  clist_->ins_next = clist_ins_next;
  clist_->rem_next = clist_rem_next;
}


int clist_destr(CLIST *clist_) {
  if (!clist_)
    return -1;
  void *data = NULL;
  while(clist_->size > 0) {
    if (!clist_rem_next(clist_,((CNODE*)clist_->head),(void**)&data)) {
      if (clist_->destr)
	return clist_destr(data);
    }else{
      return -1;
    }
  }
  memset(clist_,0,sizeof(CLIST));
  return 0;
}

int clist_ins_next(CLIST *clist_,CNODE *cnode_,const void *data) {
  if (!clist_ || (!cnode_ && clist_->size != 0))
    return -1;

  CNODE *new_elmt = NULL;
  if ((new_elmt = malloc(sizeof(CNODE))) == NULL)
    exit(-1);
  if (data)
    new_elmt->data = (void*) data;
  if (!clist_->size) {
    new_elmt->next = new_elmt;
    clist_->head = new_elmt;
  }else{
    new_elmt->next = cnode_->next;
    cnode_->next = 	new_elmt;
  }
  new_elmt->ID = clist_->size++;
  return clist_->size;
}


int clist_rem_next(CLIST *clist_,CNODE *cnode_,void **data) {
  if (clist_) {
    if ((!clist_->head) || !cnode_)
      return -1;
  }else{
    return -2;
  }

  CNODE *ptr_rem_elmt = NULL;
  if (data)
    *data = cnode_->next->data;
  if (cnode_->next == cnode_) {
    ptr_rem_elmt = cnode_->next;
    clist_->head = NULL;
  }else{
    ptr_rem_elmt = cnode_->next;
    cnode_->next = cnode_->next->next;
    if (ptr_rem_elmt == clist_->head)
      clist_->head = ptr_rem_elmt->next;
  }
  free(ptr_rem_elmt);
  clist_->size--;
  return 0;
}

void clist_remove(CLIST *clist_) {
  if (clist_) {
    if (clist_->head->next == clist_->head) {
      free(clist_->head);
      return;
    }
  }else{
    return;
  }
	
  if (clist_->head->next->next == clist_->head) {
    free(clist_->head->next);
    free(clist_->head);
    return;
  }

  CNODE *ptr = clist_->head->next;
  while (ptr->next != clist_->head && clist_->size-- > 1) {
    ptr = ptr->next;
    free(clist_->head->next);
    clist_->head->next = ptr;
    if (ptr->next == ptr) 
      {break;}
  }
  free(clist_->head);
  clist_->size = 0;
  return;
}

int create_empty_clist(int size,CLIST *clist_) {
  if (clist_) {
    if (clist_->head)
      return -1;
  }else{

    return -2;
  }
  CNODE *new_elmt = NULL;
  while (size --) {
    if (!clist_->head) {
      if ((new_elmt = malloc(sizeof(CNODE))) == NULL)
	exit(-1);
      clist_->head = new_elmt;
    }else{
			
      if ((new_elmt->next = malloc(sizeof(CNODE))) == NULL)
	exit(-1);
      new_elmt = new_elmt->next;
    }
    new_elmt->next = clist_->head;
    clist_->size ++;
    new_elmt->ID = clist_->size;
  }
  return clist_->size;
}
