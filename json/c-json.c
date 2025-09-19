#include "new-json-array.h"
#include "new-json-ob-2.h"
#include "c-json.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//code noch dokumentieren
void rem_leaf(DT *root,DT *leaf,DT **leaf_next) {
  DT **ptr = NULL;
  void *data = NULL;
  if (leaf->type_data == 2 || leaf->type_data ==3) {
    ptr = &leaf;
    rem_leaf(root,((DT*)(*ptr)->elmt->head->data),((DT**)(*ptr)->elmt->head->data));
    data = (void*)(*ptr)->elmt->head->data;
    (*ptr)->elmt = (*ptr)->elmt->Lrem_next((*ptr)->elmt,(*ptr)->elmt->head,data);
  }else{
    return;
  }
}
void traverse_DT(OBJ *object,DT *leaf,DT *leaf_next,LIST **result) {
  if (object->head->elmt->size == 0)
    return;
  DT *Sleaf = NULL;
  if (leaf != leaf_next) {
    Sleaf = (DT*)leaf_next;
  }else{
    Sleaf = object->head;
  }
  LIST *res = *result;
  //DT *ptr = *leaf_next;
  //DT *ptr_next = (DT*)&ptr->elmt->head->data;
  //  *leaf_next = ptr;
  if (leaf->type_data == 3) {
    //leaf = (DT*)leaf_next;
    //traverse_DT(root,leaf,leaf_next,&res);
  }
  if (leaf->type_data == 2) {
    //leaf = *leaf_next;
    //leaf = ((DT*)(void**)leaf->elmt->head->data);
    void *ptrp = NULL;
    if (leaf != leaf_next) {
      ptrp = (void*)Sleaf->elmt->head->data;
    }else{
      ptrp = (void*)&leaf->elmt->head->data;
    }
    DT **ptr_leaf = (DT**)ptrp;
    traverse_DT(object,leaf,*ptr_leaf,&res);
  }
  if (leaf->type_data == 1) {/*
    void **datap = ((void*)leaf->elmt->head->data);
    leaf->elmt = leaf->elmt->Lrem_next(leaf->elmt,leaf->elmt->tail,datap);
    res->Lins_next(res,res->tail,(void*)(*datap));
    if (leaf->elmt->size == 0) { 
      rem_leaf(root,leaf,leaf_next);
      traverse_DT(root,root,&root,result);
			    */ }
  }
//}

