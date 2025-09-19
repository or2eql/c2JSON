#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "json-array.h"
#include "json-ob-2.h"

int Mrem_array_elmt(ARY **array,int pos,void **data) {
  ARY *ptr_ary = *array;
  if (!ptr_ary) { 
    return -1;
  }
    
  DNODE *ptr_rem = ptr_ary->dlist_->head;
  if (pos > ptr_ary->dlist_->size || pos == 0) {
    return -2;
  } else {
    int count = 0;
    for (count;count < pos;count ++) {
      ptr_rem = ptr_rem->next;
    }
    void *ptr_data = ptr_rem->data;
    ptr_ary->dlist_->rem_lelmt(ptr_ary->dlist,ptr_rem,&ptr_data);
  }
  *array = ptr_ary;
  *data = ptr_data;
  return ptr_ary->dlist_->size;
}

int Mdestroy_array(ARY **array,void **data) {
  ARY *ptr_ary = *array;
  if (!ptr_ary) {
    return -1;
  }

  void *ptr_data = *data,
  DNODE *ptr_elmt = ptr_ary->dlist_->tail;

  while (ptr_ary_>size > 0) {
    ptr_ary->dlist->rem_lelmt(ptr_ary_->dlist_,ptr_elmt,&ptr_data);
  }
  if (ptr_ary->dlist_->size == 0) {
    *array = ptr_ary;
    
    return 0;
  } else {
    return -2;
  }
}


DLIST *Mdt_ins_array(ARY **array,DT *data,...) {
  ARY *ptr_ary = *array;
  if (ptr_ary == NULL)
    return NULL;
  
  DLIST *res = NULL;
  if ((res = malloc(sizeof(DLIST))) == NULL)
    return NULL;
  init_dlist(res);

  res->ins_next(res,res->tail,NULL);
  init_dt((DT**)&res->tail->data);
  ((DT*)res->tail->data)->type_data = 1;
  
  va_list args;
  va_start(args,data);
  DT *ptrDT = data,*ptrDT_res = (DT*)res->tail->data; //S
  do {
    ptrDT_res->elmt->Lins_node_next(ptrDT_res->elmt,ptrDT_res->elmt->tail,(void*)ptrDT);
    ptrDT = va_arg(args,DT*);
  }while(ptrDT != NULL);
  va_end(args);
  if (!ptr_ary->dlist_)
      ptr_ary->dlist_ = res;
  *array = ptr_ary;
  return res;
}


DLIST *Mobj_ins_array(ARY **array,forward_OBJ *data,...) {
  ARY *ptr_ary = *array;
  if (ptr_ary == NULL)
    return NULL;

  DLIST *res = NULL;
  if ((res = malloc(sizeof(DLIST))) == NULL)
    return NULL;
  init_dlist(res);

  res->ins_next(res,res->tail,NULL);
  init_dt((DT**)&res->tail->data);
  ((DT*)res->tail->data)->type_data = 2;
  
  va_list args;
  va_start(args,data);
  forward_OBJ *ptrOBJ = data;
  DT *ptrDT_res = (DT*)res->tail->data;
  do {
    ptrDT_res->elmt->Lins_node_next(ptrDT_res->elmt,ptrDT_res->elmt->tail,(void*)ptrOBJ);
    ptrOBJ = va_arg(args,forward_OBJ*);
  }while(ptrOBJ != NULL);
  va_end(args);
  if (!ptr_ary->dlist_)
      ptr_ary->dlist_ = res;
  *array = ptr_ary;
  return res;
}

DLIST *Marray_ins_array(ARY **array,ARY *data,...) {
  ARY *ptr_ary = *array;
  if (ptr_ary == NULL)
    exit(-1);

  DLIST *res = NULL;
  if ((res = malloc(sizeof(DLIST))) == NULL)
    return NULL;
  init_dlist(res);

  res->ins_next(res,res->tail,NULL);
  init_dt((DT**)&res->tail->data);
  ((DT*)res->tail->data)->type_data = 3;

  va_list args;
  va_start(args,data);
  ARY *ptrARY = data;
  DT *ptrDT_res = (DT*)res->tail->data;
  do {
    ptrDT_res->elmt->Lins_node_next(ptrDT_res->elmt,ptrDT_res->elmt->tail,(void*)ptrARY);
    ptrARY = va_arg(args,ARY*);
  }while(ptrARY != NULL);
  va_end(args);
  if (!ptr_ary->dlist_)
    ptr_ary->dlist_ = res;
  *array = ptr_ary;
  return res;
}
    
    
void init_array(ARY **array,char *ident) {
  ARY *ptr_ary = *array;
  if (ptr_ary)
    return;

  if ((ptr_ary = malloc(sizeof(ARY))) == NULL)
    return;

  if ((ptr_ary->methods = malloc(sizeof(ARYmethods))) == NULL)
    return;

  int size = strlen(ident);
  if ((ptr_ary->ident = malloc((size +1) * sizeof(char))) == NULL)
    return;

  if ((ptr_ary->dlist_ = malloc(sizeof(DLIST))) == NULL)
    return;

  dlist_init(ptr_ary->dlist_);
  ptr_ary->dim = 1;

  //Methoden initialisieren
  ptr_ary->methods->ary_ins_ary = Marray_ins_array;
  ptr_ary->methods->dt_ins_ary = Mdt_ins_array;
  ptr_ary->methods->obj_ins_ary = Mobj_ins_array;
  ptr_ary->methods->rem_ary_elmt = Mrem_array_elmt;
  ptr_ary->methods->destr_ary = Mdestroy_array;

  *array = ptr_ary;
  return;
}


