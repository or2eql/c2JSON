//
// Created by oreql on 15.08.25.
//

#ifndef DLLIST_H
#define DLLIST_H
#include "llist.h"

typedef struct dnode DNODE;
typedef struct dlist DLIST;

typedef int (*add_destroy_dlist) (DLIST**,void**);
typedef int (*add_rem_lelmt) (DLIST*,DNODE*,void **);
typedef DLIST* (*add_ins_next) (DLIST*,DNODE*,void*);
typedef DLIST* (*add_ins_prev) (DLIST*,DNODE*,void*);
typedef char* (*add_Str_ID) (DNODE *,const char*);

struct dnode {
    DNODE *next;
    DNODE *prev;
    int ID;
    char *name_value;
    void *data;
};

struct dlist {
    DNODE *head;
    DNODE *tail;
    int size;
    //Methods
    add_destroy_dlist  destroy_dlist;
    add_ins_next ins_next;
    add_ins_prev ins_prev;
    add_rem_lelmt rem_lelmt;
    add_Str_ID STR_ID;
};

int init_dlist(DLIST **dlist);
int remove_lelmt(DLIST *dlist,DNODE *dnode,void **data);
DLIST *ins_next(DLIST *dlist,DNODE *dnode,void *data);
DLIST *ins_prev(DLIST *dlist,DNODE *dnode,void *data);
int destroy_dlist(DLIST **dlist,void **data);
char *create_name_value(DNODE *dnode,const char *data);

#endif //DLLIST_H
