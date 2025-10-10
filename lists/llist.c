//
// Created by oreql on 15.08.25.
//

#include "llist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>


struct names_by_fail {
  char *first_nameValue[16];
  char *last_nameValue[16];
  int count_first_name;
  int count_last_name;
};

struct names_by_fail NAMES_BY_FAIL = {
  .first_nameValue = { "Anna", "Ben", "Clara", "David", "Emilia", "Felix", "Greta", "Hannes","Ida", "Jakob", "Katharina", "Leo", "Marie", "Nils", "Pia", "Simon" },
  .last_nameValue = { "Müller", "Schmidt", "Schneider", "Fischer", "Weber", "Meyer", "Wagner", "Becker","Schulz", "Hoffmann", "Koch", "Bauer", "Richter", "Klein", "Wolf", "Neumann" },
  .count_first_name = 0,
  .count_last_name = 0
};



char *str_ID(NODE **node,const char *str) {
  NODE *ptr_node = *node;
  if (ptr_node == NULL) {
    return NULL;
  }
  unsigned long int len = strlen(str) + 1;
  if (ptr_node->name_value == NULL) {
    if ((ptr_node->name_value = (char*) malloc(sizeof(char)*(len))) == NULL) {
      return NULL;
    }
  }

  strncpy(ptr_node->name_value, str, len);
  ptr_node->name_value[len -1] = '\0';
  *node = ptr_node;
  return ptr_node->name_value;
}

void name_node(NODE **node,const char *name) {
  NODE *ptr_node = *node;
  if (ptr_node == NULL) {
    return;
  }

  switch (ptr_node->status_named_node) {
  case 0:
    //kein name wurde vergeben
    str_ID(&ptr_node,name);
    ptr_node->status_named_node ^= 0xffff0000;
    break;
  case 0xffff0000:
    //name für die node wurde vergeben
    break;
  case 0x00000ffff:
    //sha wert ist vergeben --> zurücksetzten FEHLER
    if (ptr_node->sha_value) {
      free(ptr_node->sha_value);
    }
    ptr_node->sha_value = NULL;
    ptr_node->status_named_node = 0;
    break;
  case 0xffffffff:
    //beide werte sind vergeben --> zurücksetzten
    if (ptr_node->name_value && ptr_node->sha_value) {
      free(((char*)ptr_node->name_value));
      //free(((unsigned char*)ptr_node->sha_value));
    }
    ptr_node->name_value = NULL;
    str_ID(&ptr_node,name);
    ptr_node->sha_value = NULL;
    ptr_node->status_named_node = 0;
    break;

  default : printf("\nsomething goes very wrong\n");
    exit(-2);
  }

  *node = ptr_node;
}

char *create_random_name(void) {
  char *buffer = NULL;
  if (NAMES_BY_FAIL.count_first_name >= 16 || NAMES_BY_FAIL.count_last_name >= 16) {
    return NULL;
  }
  char *first_name = NAMES_BY_FAIL.first_nameValue[NAMES_BY_FAIL.count_first_name++];
  char *last_name = NAMES_BY_FAIL.last_nameValue[NAMES_BY_FAIL.count_last_name++];
  long unsigned int size = 0;
  if ((buffer = (char*) malloc((size = (strlen(first_name)+strlen(last_name)+2)) * sizeof(char))) == NULL)
    return NULL;


  strncat(buffer, first_name ,strlen(first_name));
  strcat(buffer, " ");
  strncat(buffer, last_name,strlen(last_name));
  buffer[size -1] = '\0';
  return buffer;
}

unsigned char *make_sha256(char data[]) {
  if (data == NULL) {
    return NULL;
  }
  char *buffer =  NULL;
  if ((buffer = (char*) malloc(strlen(data) +1)) == NULL)
    return NULL;
  int i = 0;
  unsigned int c = 0;
  for (i = 0; data[i] != '\0'; i++) {
    c = (unsigned int) data[i];
    if (c <= 127) {
      buffer[i] = data[i];
    } else {
      free(buffer);
      buffer = NULL;
      buffer = create_random_name();
      break;
    }
  }

  unsigned char *hash = NULL;
  if ((hash = malloc(SHA256_DIGEST_LENGTH +1 * sizeof(unsigned char))) == NULL)
    return NULL;
  SHA256((const unsigned char*)buffer,strlen(buffer),hash);
  hash[SHA256_DIGEST_LENGTH] = '\0';
  free(buffer);
  buffer = NULL;
  return hash;
}

void create_sha2(NODE **node,char data[]) {
  if (*node == NULL) {
    return;
  }
  NODE *ptr_node = *node;
  unsigned char* hash = make_sha256(ptr_node->name_value);
    
  if ((ptr_node->sha_value = malloc((SHA256_DIGEST_LENGTH +1) * sizeof(unsigned char))) == NULL)
    return;
  if (ptr_node->status_named_node == 0x0 || ptr_node->status_named_node == 0xffff0000) {
    memset((char*)ptr_node->sha_value,0,(SHA256_DIGEST_LENGTH +1) * sizeof(unsigned char));
    ptr_node->sha_value[SHA256_DIGEST_LENGTH] ='\0';
    strcat(ptr_node->sha_value,hash);
    ptr_node->status_named_node ^= 0x0000ffff;
  } else {
    //sha- wert kann nicht vergeben werden --> zurücksetzen
    free(ptr_node->sha_value);
    if (ptr_node->name_value) {
      free(ptr_node->name_value);
    } else if (ptr_node->sha_value) {
      free(ptr_node->sha_value);
    }
    ptr_node->name_value = NULL;
    ptr_node->sha_value = NULL;
    ptr_node->status_named_node = 0x0;
  }
  free(hash);
  *node = ptr_node;
}

int init_list(LIST **list_) {
  LIST *ptr_list = *list_;
  if (ptr_list) {
    return -1;
  }
  if ((ptr_list = malloc(sizeof(LIST))) == NULL) {
    return -2;
  }
  ptr_list->head = NULL;
  ptr_list->head = NULL;
  ptr_list->size = 0;
  //Methods
  ptr_list->name_node = name_node;
  ptr_list->create_sha256 = create_sha2;
  ptr_list->Ldestr_list = destroy_list;
  ptr_list->Lins_node_next = ins_node_next;
  ptr_list->Lrem_next_elmt = rem_next_elmt;

  *list_ = ptr_list;
  return 0;
}

LIST *rem_next_elmt(LIST *list,NODE *node,void **data) {
  if (list == NULL || list->size == 0) {
    return list;
  }
  void *ptr_data = NULL;
  NODE *rem_next = NULL;

  if (node == NULL) {
    rem_next = list->head;
    list->head = list->head->next;
    if (list->size == 1) {
      list->tail = NULL;
    }
  } else {
    if (node->next == NULL) {
      if (list->size != 1) {
	return list;
      }
    }
    if (list->size == 1) {
    	rem_next = list->head;
    } else {
      rem_next = node->next;
      node->next = rem_next->next;
    }
    if (node->next == NULL) {
      list->tail = node;
    }
  }

  if (*data) {
    *data = rem_next->data;
  }
  
  free(rem_next);
  rem_next = NULL;
  list->size --;
  if (list->size == 0)
    list->head = NULL;
  return list;
}
  
  

int destroy_list(LIST **list,void **data) {

  if (list == NULL || *list == NULL) {
    return -1;
  }
  void *ptr_data = *data;
  do {
    rem_next_elmt(*list,NULL,&ptr_data);
  } while ((*list)->head); 

  free(*list);
  *list = NULL;
  return 0;
}

LIST *ins_node_next(LIST *list,NODE *node,void *data) {
  if (list == NULL) {
    return list;
  }

  NODE *new_elmt = NULL;
  if ((new_elmt = malloc(sizeof(NODE))) == NULL) {
    return NULL;
  }
  
  new_elmt->name_value = NULL;
  new_elmt->sha_value = NULL;
  new_elmt->ID = list->size ++;
  new_elmt->status_named_node = 0;
  new_elmt->next = NULL;

  
  if (node == NULL) {
    new_elmt->next = list->head;
    list->head = new_elmt;
    if (list->tail == NULL) {
      list->tail = new_elmt;
    }
  } else {
    new_elmt->next = node->next;
    node->next = new_elmt;
    if (new_elmt->next == NULL) {
      list->tail = new_elmt;
    }
  }
  if (data) {
    new_elmt->data = (void*)data;
  }
  return list;
}
