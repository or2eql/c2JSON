/*
  json-obj
  erstellt am: 01. März 2025
  Bibliotheken: llist, dllist, json-dt
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "./json-ob-2.h"
#include "./json-array.h"

int rem_datatype(OBJ *object,DT *elmt) {
  if (object) {
    if ((!object->head && !object->tail) || !elmt) 
      return -1;
  }else{
    return -2;
  }
  
  if (elmt == (DT*)object->head) {
    object->head = elmt->next;
    if(!object->head) {
      object->tail = NULL;
    }else{
      elmt->next->prev = NULL;
    }
  }else{
    elmt->prev->next = elmt->next;
    if(!elmt->next) {
      object->tail = elmt->prev;
    }else{
      elmt->next->prev = elmt->prev;
    }
  }
  elmt->REM(elmt);
  object->size --;
  return 0;
}

//mit while schleife ohne rekursivität ! ! !

void destroy_obj(OBJ **object) {
  if (!object)
    return;
  OBJ *ptr_obj = *object;
  while (ptr_obj->size > 0) {
    ptr_obj->methods->rem_dt(ptr_obj,ptr_obj->tail);
  }
  free(ptr_obj->str_ID);
  free(ptr_obj->methods);
  free(ptr_obj);
}

int DTins_next(OBJ *object,DT *datatype,void *data) {
  if (!object || (!datatype && object->size != 0))
    return -1;
  DT *new_elmt = (DT*)data;
  
  if (data == NULL) {
    return 0;
   }else{ 
    new_elmt->type_data = 1;
    if (object->size == 0) {
      object->head = new_elmt;
      object->head->prev = NULL;
      object->head->next = NULL;
      object->tail = new_elmt;
    }else{
      new_elmt->next = datatype->next;
      new_elmt->prev = datatype;
      if (!new_elmt->next) {
	object->tail = new_elmt;
      }else{
	new_elmt->next->prev = new_elmt;
      }
      datatype->next = new_elmt;
    }
    new_elmt->ID = object->size ++;
    return object->size;
  }
}
   
int DTins_prev(OBJ *object,DT *datatype,void *data) {
    
  if ((!object || !datatype && object->size != 0))
    return -1;
  DT *new_elmt = (DT*)data;

  if (data == NULL) { 
    return 0;
  }else{
      new_elmt->type_data = 1;
    if (object->size == 0) {
      object->head = new_elmt;
      object->head->prev = NULL;
      object->head->next = NULL;
      object->tail = new_elmt;
    }else{
      new_elmt->prev = datatype->prev;
      new_elmt->next = datatype;
      if (!new_elmt->prev) {
	object->head = new_elmt;
      }else{
	new_elmt->prev->next = new_elmt;
      }
      datatype->prev = new_elmt;
    }
  }
  new_elmt->ID = object->size ++;
  return object->size;
  
}
/* fügt eim Objekt in datatype->next ein */
OBJ *obj_ins_objNEXT(OBJ *object,OBJ *nested_obj,DT *datatype) {
  if(!datatype || !object || !nested_obj)
    return NULL;
  DT *new_elmt = NULL;
  init_dt(&new_elmt);
  new_elmt->type_data = 2;
  if (object->size == 0) {
    object->head = new_elmt;
    object->head->prev = NULL;
    object->tail->next = NULL;
    object->tail = new_elmt;
  }else{
    new_elmt->next = datatype->next;
    new_elmt->prev = datatype;
    if (new_elmt->next == NULL) {
      object->tail = new_elmt;
    }else{
      new_elmt->next->prev = new_elmt;
    }
    datatype->next = new_elmt;
  }
  new_elmt->ID = object->size ++;
  //in new_elmt kommt jetzt das objekt
  DT *Sptr_dt = nested_obj->head;
  for (;Sptr_dt != NULL;Sptr_dt = Sptr_dt->next) 
    new_elmt->elmt->Lins_node_next(new_elmt->elmt,new_elmt->elmt->tail,(void*)Sptr_dt);
  return object;
}


OBJ *obj_ins_objPREV(OBJ *object,OBJ *nested_obj,DT *datatype) {
  if(!datatype || !object || !nested_obj)
    return NULL;
  DT *new_elmt = NULL;
  init_dt(&new_elmt);
  new_elmt->type_data = 2;
  if (object->size == 0) {
    object->head = new_elmt;
    object->head->prev = NULL;
    object->tail->next = NULL;
    object->tail = new_elmt;
  }else{
    new_elmt->next = datatype;
    new_elmt->prev = datatype->prev;
    if (new_elmt->prev == NULL) {
      object->head = new_elmt;
    }else{
      new_elmt->prev->next = new_elmt;
    }
    datatype->prev = new_elmt;
  }
  new_elmt->ID = object->size ++;
  //in new_elmt kommt jetzt das objekt
  DT *Sptr_dt = nested_obj->head;
  for (;Sptr_dt != NULL;Sptr_dt = Sptr_dt->next) 
    new_elmt->elmt->Lins_node_next(new_elmt->elmt,new_elmt->elmt->tail,(void*)Sptr_dt);
  return  object;
}

OBJ *array_ins_objNEXT(OBJ *object,DT *datatype,DLIST *list_dt_array) {
  if (list_dt_array == NULL) {
    return NULL;
  }else if(list_dt_array->size == 0) {
    return NULL;
  }else if(!object || !datatype) {
    return NULL;
  }

  DT *new_elmt = NULL;
  init_dt(&new_elmt);
  new_elmt->type_data = 3;
  if (object->size == 0) {
    object->head = new_elmt;
    object->head->prev = NULL;
    object->tail->next = NULL;
    object->tail = new_elmt;
  }else{
    new_elmt->next = datatype->next;
    new_elmt->prev = datatype;
    if (new_elmt->next == NULL) {
      object->tail = new_elmt;
    }else{
      new_elmt->next->prev = new_elmt;
    }
    datatype->next = new_elmt;
  }
  new_elmt->ID = object->size ++;

  //die dlist wird jetzt zu einer llist
  DNODE *ptr_node = list_dt_array->head;
  void *ptr_data = (void*)ptr_node->data;

  for (;ptr_node != NULL;ptr_node = ptr_node->next)
    new_elmt->elmt->Lins_node_next(new_elmt->elmt,new_elmt->elmt->tail,(void*)ptr_data);
  return object;
}

OBJ *array_ins_objPREV(OBJ *object,DT *datatype,DLIST *list_dt_array) {
if (list_dt_array == NULL) {
    return NULL;
  }else if(list_dt_array->size == 0) {
    return NULL;
  }else if(!object || !datatype) {
    return NULL;
  }

  DT *new_elmt = NULL;
  init_dt(&new_elmt);
  new_elmt->type_data = 3;
  if (object->size == 0) {
    object->head = new_elmt;
    object->head->prev = NULL;
    object->tail->next = NULL;
    object->tail = new_elmt;
  }else{
    new_elmt->next = datatype;
    new_elmt->prev = datatype->prev;
    if (new_elmt->prev == NULL) {
      object->head = new_elmt;
    }else{
      new_elmt->prev->next = new_elmt;
    }
    datatype->prev = new_elmt;
  }
  new_elmt->ID = object->size ++;

  //die dlist wird jetzt zur llist
  DNODE *ptr_node = list_dt_array->head;
  void *ptr_data = (void*)ptr_node->data;

  for (;ptr_node != NULL;ptr_node = ptr_node->next)
    new_elmt->elmt->Lins_node_next(new_elmt->elmt,new_elmt->elmt->tail,(void*)ptr_data);
  return object;
}
 
int create__ID(OBJ *ob,char *pattern) {
  if (!ob || !pattern)
    return -1;

  int len = strlen (pattern) +1;
  if ((ob->str_ID = malloc(len * sizeof(char))) == NULL)
    exit(-1);;
  strncpy(((char*)ob->str_ID),pattern,len);
  return 0;
}

void init_obj(OBJ **object,const char *ID) {
  OBJ *ptr_object = *object;
  if (ptr_object)
      return;
  if ((ptr_object = malloc(sizeof(OBJ))) == NULL)
    exit(-1);
  
  ptr_object->head = NULL;
  ptr_object->tail = NULL;
  ptr_object->str_ID = NULL;

  create__ID(ptr_object,(char*)ID);
  ptr_object->size = 0;
  ptr_object->typ = TYP_OBJ;
  if (((ptr_object->methods = malloc(sizeof(OBJmethods))) == NULL))
    exit(-1);
  ptr_object->methods->rem_dt = rem_datatype;
  ptr_object->methods->destr_obj = destroy_obj;
  ptr_object->methods->dt_ins_next = DTins_next;
  ptr_object->methods->dt_ins_prev = DTins_prev;
  ptr_object->methods->obj_ins_obj_next = obj_ins_objNEXT;
  ptr_object->methods->obj_ins_obj_prev = obj_ins_objPREV;
  ptr_object->methods->array_ins_obj_next = array_ins_objNEXT;
  ptr_object->methods->array_ins_obj_prev = array_ins_objPREV;
  *object = ptr_object;
}
