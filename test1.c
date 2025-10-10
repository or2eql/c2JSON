#include <stdio.h>
#include "json/c-json.h"

int main(void) {
    LIST *test1 = NULL;
    void *data = NULL;
    int res = init_list(&test1);
    int a = 123;
    int b = 654;
    char *string = "3hello world";
    test1 = test1->Lins_node_next(test1,test1->tail,&a);
    test1 = test1->Lins_node_next(test1,test1->head,&a);
    test1 = test1->Lins_node_next(test1,test1->tail,&a);
    test1 = test1->Lins_node_next(test1,test1->head,&a);
    test1 = test1->Lrem_next_elmt(test1,test1->head->next,&data);
    test1 = test1->Lrem_next_elmt(test1,test1->head,&data);
    test1 = test1->Lrem_next_elmt(test1,test1->head,&data);
    test1 = test1->Lrem_next_elmt(test1,test1->head,&data);
    test1 = test1->Lins_node_next(test1,test1->head,&a);
    //    test1 = test1->

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
    DT *test5 = NULL;
    DT *test6 = NULL;
    DT *test7 = NULL;
    test3 = init_dt();
    test4 = init_dt();
    test5 = init_dt();
    test6 = init_dt();
    test7 = init_dt();
    test3->elmt = test3->PUT_TYPE(TYPEint,"das ist ein test",&a);
    test4->elmt = test4->PUT_TYPE(TYPEint,"das ist ein zweiter test",&b);
    test5->elmt = test5->PUT_TYPE(TYPEint,"keiner",&a);
    //test6->elmt = test6->PUT_TYPE(TYPEint,"alle",&b);
    test7->elmt = test7->PUT_TYPE(TYPEstr,"lulz",string);
    OBJ *test05 = NULL;
    init_obj(&test05,"test-ob");
    test05->methods->dt_ins_next(test05,test05->head,test3);
    test05->methods->dt_ins_next(test05,test05->head,test4);
    test05->methods->dt_ins_next(test05,test05->tail,test3);
    test05->methods->dt_ins_next(test05,test05->tail,test4);
    test05->methods->destr_obj(&test05);
    return 0;
}
