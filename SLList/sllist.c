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
  GNode *auxNode;
  GNode *previous = list->prev;
  for (; list != NULL; list = list->next) {
    auxNode = list->next;
    function(list->data);
    free(list);
  }
  function(list->data);
  free(list);
}

SLList sllist_insert_with_replace(SLList list, void *data, Compare compare, Destroy function) {
  GNode *node = malloc(sizeof(GNode));
  node->data = data;
  for (; list->next != NULL && compare(list->data) list = list->next){

  };
  node->next = list;

  return glist_concat(list, node);
}
