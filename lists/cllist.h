//Benedikt Gruber
//cllist.h


typedef struct cnode CNODE;
typedef struct clist CLIST;

typedef void (*add_remove_clist) (CLIST*);
typedef int (*add_destroy_clist) (CLIST*);
typedef int (*add_ins_cnode_next) (CLIST*,CNODE*,const void *);
typedef int (*add_rem_cnode_next) (CLIST*,CNODE*,void **);


struct cnode{
	CNODE *next;
	int ID;
	void *data;
};

struct clist {
	CNODE *head;
	int size;
	add_remove_clist rem_list;
	add_destroy_clist destr;
	add_ins_cnode_next ins_next;
	add_rem_cnode_next rem_next;
};

void clist_init(CLIST *clist_);
int clist_destr(CLIST *clist_);
int clist_ins_next(CLIST *clist_,CNODE *cnode_,const void *data);
int clist_rem_next(CLIST *clist_,CNODE *cnode_,void **data);
void clist_remove(CLIST *clist_);
int create_empty_clist(int size,CLIST *clist_);
