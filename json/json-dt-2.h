/*
  json-dt
  erstellt: 27. Feb 2025
  Bibliotheken: llist
*/
#ifndef MODULE_DT_H
#define MODULE_DT_H
#include "../lists/llist.h"
#include "../lists/dllist.h"

typedef struct datatype DT;
typedef struct datatypeMeth DTmeth;

typedef LIST* (*add_put_datatype)(int,char*,void*);
typedef void (*add_remove_datatype)(DT*);

struct datatype {
  /*
    wenn type_data:
    - 1 dann handelt es sich um DT
    - 2 dann handelt es sich um OBJ
    - 3 dann handlet es sich um ARRAY 
  */
  int type_data;
  int ID;
  struct datatype *next;
  struct datatype *prev;
  LIST *elmt;
  add_put_datatype PUT_TYPE;
  add_remove_datatype REM;
 
};


DT *init_dt(DT **data_type);
LIST *put_type(int token,char *str_key,void *data);
void rem(DT *data_type);

#define TYPEstr 1
#define TYPEint 2
#define TYPEfloat 3
#endif
