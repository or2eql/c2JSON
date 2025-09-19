 /*
  json-dt
  erstellt am: 27. Feb 2025
  Bibliotheken: llist, optional
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "./json-dt-2.h"

 void rem(DT *datatype) {
  if (!datatype)
    return;
  void *data = datatype->elmt->head->data;
  LIST *ptr_datatype = datatype->elmt;
  if ((datatype->elmt->Ldestr_list(&ptr_datatype,&data)) == -1) {
    datatype->elmt = NULL;
    return;
  }
    
  memset(datatype,0,sizeof(DT));
}

LIST *put_type(int token,char *str_key,void *ptr_data) {
  
  if (!ptr_data)
    return NULL;
  int str_len = 0;
  LIST *temp = NULL;
  
  if ((temp = malloc(sizeof(LIST))) == NULL) {
    return NULL;
  }
  
  init_list(&temp);
  char *ident1 = "str";
  char *ident2 = "int";
  char *ident3 = "float";
  char *ident4 = "#"; //Object
  char *ident5 = "@"; //Array

  /*
    - hier wird der Json Variablen Name hinterlegt in <head>
  */

  str_len = strlen(str_key);
  if ((temp->Lins_node_next(temp,temp->tail,NULL)) == NULL) {
    return NULL;
  }
  if ((temp->tail->data = malloc(str_len +10 * sizeof(char))) == NULL)
    return NULL;
  if (!temp->tail->data)
    exit(-1);
  
  switch (token) {
  case 1: strcat(((char*)temp->tail->data),"str-");break;
  case 2: strcat(((char*)temp->tail->data),"int-");break;
  case 3: strcat(((char*)temp->tail->data),"flt-");break;
  case 4: strcat(((char*)temp->tail->data),"#---");break;
  case 5: strcat(((char*)temp->tail->data),"@---");break;
  default: fprintf(stderr,"\nfatal error\n");exit(-2);
  }
  *(char*)temp->tail->data = '\0';
  strncat(((char*)temp->tail->data),str_key,str_len);


  /*
    data ist void* und wird über *ptr_data
    dem data Zeiger von *temp zugewiesen
  */
  
  if ((temp->Lins_node_next(temp,temp->tail,(void*)ptr_data)) == NULL) {
    return NULL;
  }
  
  switch (token) {
    
    /*
      wenn data eine Zeichenkette ist
      - token ist 1
    */
  case 1:
    temp->name_node(((NODE**)temp->head),(char*)ident1);break;
    /*
      wenn data eine Ganzzahl ist
      -token ist 2
    */
  case 2:
    temp->name_node(((NODE**)temp->head),(char*)ident2);break;
    /*
      wenn data eine Fließkommazahl ist
      -token ist 3
    */
  case 3:
    temp->name_node(((NODE**)temp->head),(char*)ident3);break;

    default:
        return NULL;

  }
  
  return temp;
}
      
DT *init_dt(DT **datatype) {
  DT *ptr_datatype = *datatype;
  if (ptr_datatype)
    return NULL;
  if ((ptr_datatype = malloc(sizeof(DT))) == NULL) {
    return NULL;
  }
  if ((ptr_datatype->elmt = malloc(sizeof(LIST))) == NULL) {
    return NULL;
  }
 
  LIST **new_elmt = &ptr_datatype->elmt;
  init_list(new_elmt);
  ptr_datatype->type_data = 0;
  ptr_datatype->ID = 0;

  ptr_datatype->next = NULL;
  ptr_datatype->prev = NULL;
  ptr_datatype->PUT_TYPE = put_type;
  ptr_datatype->REM = rem;

  *datatype = ptr_datatype;
}

