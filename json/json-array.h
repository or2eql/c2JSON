/*
  json-array
  erstellt am 17. Apr
  Bibliotheken: llist, dllist, (forward deklaration) object
*/
#ifndef MODUL_ARRAY_H
#define MODUL_ARRAY_H
#include "json-dt-2.h"

typedef struct obj forward_OBJ; //für OBJ Datentypen
typedef struct obj_methods forward_OBJmethods;

typedef struct ary ARY;
typedef struct ary_methods ARYmethods;

typedef DLIST* (*add_ary_ins_array)(ARY**,ARY*,...);
typedef DLIST* (*add_dt_ins_array)(ARY**,DT*,...);
typedef DLIST* (*add_object_ins_array)(ARY**,forward_OBJ*,...);
typedef int (*add_rem_array_elmt)(ARY**,int,void**);
typedef int (*add_destroy_array)(ARY**,void**);

struct ary_methods {
  add_ary_ins_array ary_ins_ary;
  add_dt_ins_array dt_ins_ary;
  add_object_ins_array obj_ins_ary;
  add_rem_array_elmt rem_ary_elmt;
  add_destroy_array destr_ary;
};

struct ary {
  int dim;
  char *ident;
  ARYmethods *methods;
  DLIST *dlist_;
};

void init_array(ARY **array,char *ident);
DLIST *Marray_ins_array(ARY **array,ARY *data,...);
DLIST *Mobj_ins_array(ARY **array,forward_OBJ *data,...);
DLIST *Mdt_ins_array(ARY **array,DT *data,...);
int Mdestroy_array(ARY **array,void **data);
int Mrem_array_elmt(ARY **array,int pos,void **data);

#endif //MODUL_ARRAY_H

