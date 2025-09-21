#include <stdio.h>
#include "json/c-json.h"

int main(void) {
    LIST *test1 = NULL;
    void *data = NULL;
    int res = init_list(&test1);
    int a = 123;
    int b = 654;
    test1 = test1->Lins_node_next(test1,test1->tail,&a);
    test1 = test1->Lins_node_next(test1,test1->head,&a);
    test1 = test1->Lrem_next_elmt(test1,test1->tail,&data);
    test1 = test1->Lrem_next_elmt(test1,test1->tail,NULL);
    test1 = test1->Lins_node_next(test1,test1->tail,&a);
    test1 = test1->Lins_node_next(test1,test1->head,&a);

    NODE *ptr = test1->head;
    test1->name_node(&ptr,"hello world");
    test1->create_sha256(&ptr,ptr->name_value);
    test1->name_node(&ptr,"2hello world");
    test1->Ldestr_list(&test1,&data);

    DLIST *test2 = NULL;
   
    res = init_dlist(&test2);
    test2->ins_next(test2,test2->head,&a);
    test2->rem_lelmt(test2,test2->tail,&data);
    test2->ins_prev(test2,test2->tail,&a);
    test2->rem_lelmt(test2,test2->tail,NULL);
    test2->destroy_dlist(&test2,&data);

    DT *test3 = NULL;
    DT *test4 = NULL;
    init_dt(&test3);
    init_dt(&test4);
    test3->elmt = test3->PUT_TYPE(TYPEint,"das ist ein test",&a);
    test4->elmt = test4->PUT_TYPE(TYPEint,"das ist ein zweiter test",&b);
    OBJ *test5 = NULL;
    init_obj(&test5,"test-ob");
    test5->methods->dt_ins_next(test5,test5->head,test3);
    test5->methods->dt_ins_next(test5,test5->head,test4);
    test5->methods->dt_ins_next(test5,test5->tail,test3);
    test5->methods->dt_ins_next(test5,test5->tail,test4);
    test5->methods->destr_obj(&test5);
    return 0;
}
