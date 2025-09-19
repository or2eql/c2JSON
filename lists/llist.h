//
// Created by oreql on 15.08.25.
//

#ifndef LLIST_H
#define LLIST_H

#include "/usr/include/openssl/sha.h"

typedef struct node NODE;
typedef struct list LIST;

//Methods
typedef int (*add_destroy_list)(LIST**,void**);
typedef LIST* (*add_ins_node_next)(LIST*,NODE*,void*);
typedef LIST* (*add_rem_next_elmt)(LIST*,NODE*,void **);
//typedef char* (*add_str_ID)(NODE**,const char*);
typedef void (*add_name_node)(NODE**,const char*);
typedef void (*add_create_sha256)(NODE **,char*);
//Openssl Methods


struct node {
    NODE *next;
    int ID;
    unsigned int status_named_node;
    unsigned char *sha_value;
    char *name_value;
    void *data;
};

struct list {
    NODE *head;
    NODE *tail;
    int size;
    //Methods
    add_destroy_list Ldestr_list;
    add_ins_node_next Lins_node_next;
    add_rem_next_elmt Lrem_next_elmt;
    add_name_node name_node;
    add_create_sha256 create_sha256;
};

int init_list(LIST **list_);
int destroy_list(LIST **list_,void **data);
LIST *ins_node_next(LIST *list,NODE *node,void *data);
LIST *rem_next_elmt(LIST *list,NODE *node,void **data);
//char *str_ID(NODE **node,const char *str);
char *str_ID(NODE **node,const char *str);
void name_node(NODE **node,const char *name);
char *create_random_name(void);
unsigned char *make_sha256(char data[]);
void create_sha2(NODE **node,char[]);



#endif //LLIST_H
