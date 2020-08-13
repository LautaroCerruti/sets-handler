#include "sllist.h"
#include <stdio.h>
#include <stdlib.h>

struct _SLNode {
  void *data;
  struct _SLNode *next;
};

SLList sllist_create() {
  return NULL;
}

void glist_destroy(SLList list, Destroy function) {
  SLNode *auxNode = list;
  if (list) {
    list = list->next;
    for (; list != NULL; list = list->next) {
      function(auxNode->data);
      free(auxNode);
      auxNode = list;
    }
    function(auxNode->data);
    free(auxNode);
  }
}

SLList sllist_insert_with_replace(SLList list, void *data, Compare compare, Destroy function) {
  SLNode *node;
  SLList aux = list;
  for (; !compare(list->data, data) && list->next != NULL; list = list->next);
  if (compare(list->data, data)) {
    function(list->data);
    list->data = data;
  } else {
    node = malloc(sizeof(SLNode));
    node->data = data;
    node->next = NULL;
    list->next = node;
  }
  return aux;
}

void* sllist_find(SLList list, void *data, Compare compare){
  for (; list != NULL && !compare(list->data, data); list = list->next);
  return (list ? list->data : NULL);
}