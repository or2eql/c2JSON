/*
  json-ob
  erstellt am 28. Feb 2025
  Bibliotheken: llist, dllist, (forward deklaration) json-array
*/
#ifndef MODUL_OBJECT_H
#define MODUL_OBJECT_H

#include "./json-dt-2.h"

typedef struct ary forward_ary; //für ARY Datentypen
typedef struct ary_methods forward_ARYmethods;

typedef struct obj OBJ;
typedef struct obj_methods OBJmethods;

typedef enum {
  TYP_OBJ,
  TYP_NEW_OBJ
}typ__object;


struct obj {
  int size;
  int ID;
  DT *head;
  DT *tail;
  char *str_ID;
  OBJmethods *methods;
  typ__object typ;
};

typedef int (*add_remove_dt)(OBJ*,DT*,void **);
typedef int (*add_dt_ins_next)(OBJ*,DT*,void*);
typedef int (*add_dt_ins_prev)(OBJ*,DT*,void*);
typedef void (*add_destroy_obj)(OBJ*);
typedef int (*add_str__ID)(OBJ*,const char*);
//nested Objects
//oder array in Objects
typedef OBJ* (*add_obj_ins_obj_next)(OBJ*,OBJ*,DT*);
typedef OBJ* (*add_obj_ins_obj_prev)(OBJ*,OBJ*,DT*);
typedef OBJ* (*add_array_ins_ob_next)(OBJ*,DT*,DLIST*);
typedef OBJ* (*add_array_ins_ob_prev)(OBJ*,DT*,DLIST*);

struct obj_methods {
  add_remove_dt rem_dt;
  add_destroy_obj destr_obj;
  add_dt_ins_next dt_ins_next;
  add_dt_ins_prev dt_ins_prev;
  add_str__ID create_ID;
  //wenn es sich um ein nested Object handelt
  add_obj_ins_obj_next obj_ins_obj_next;
  add_obj_ins_obj_prev obj_ins_obj_prev;
  add_array_ins_ob_next array_ins_obj_next;
  add_array_ins_ob_prev array_ins_obj_prev;
};

int make_deep_copy(OBJ **deep_copy,OBJ *nested_object);

void init_obj(OBJ** object,const char *ID);
int rem_datatype(OBJ *object,DT *elmt,void **data);
void destroy_obj(OBJ *object);
int DTins_next(OBJ *object,DT *datatype,void *data);
int DTins_prev(OBJ *object,DT *datatype,void *data);
OBJ *obj_ins_objNEXT(OBJ *object,OBJ *nested_obj,DT *datatype,HASH_TABLE **table);
OBJ *obj_ins_objPREV(OBJ *object,OBJ *nested_obj,DT *datatype);
OBJ *array_ins_objNEXT(OBJ *object,DT *datatype,DLIST *list_dt_array);
OBJ *array_ins_objPREV(OBJ *object,DT *datatype,DLIST *list_dt_array);

#endif //MODUL_OBJECT_H
