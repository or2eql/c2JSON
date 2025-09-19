#include "json-array.h"
#include "json-ob-2.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void traverse_DT(OBJ *object,DT *leaf,DT *leaf_next,LIST **result);
//void traverse_DT(DT *root,DT *leaf,DT **leaf_next,LIST **result);
void rem_leaf(DT *root,DT *leaf,DT **leaf_next);
LIST *get_object(DT *start,DT *next,LIST *result);
LIST *get_array(DT *start,DT *next,LIST *result);
typedef LIST*  (*add_get_types)(DT*,DT*,LIST*);

LIST *create_debug_seq(OBJ *object);
char *get_json(LIST *debug);
LIST *get_debug(char *json_str);
char *create_debug_string_object(void *data);
char *create_debug_string_array(void *data);
