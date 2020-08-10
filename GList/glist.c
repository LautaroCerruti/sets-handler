#include "glist.h"
#include <stdio.h>
#include <stdlib.h>

struct _GNode {
  void *data;
  struct _GNode *prev;
  struct _GNode *next;
};

GList glist_create() {
  return NULL;
}

void glist_destroy(GList list, Destroy function) {
  GNode *auxNode;
  GNode *previous = list->prev;
  for (; list != previous; list = auxNode) {
    auxNode = list->next;
    function(list->data);
    free(list);
  }
  function(list->data);
  free(list);
}

GList glist_insert_last_position(GList list, void *data) {
  GNode *node = malloc(sizeof(GNode));
  node->data = data;
  node->prev = node;
  node->next = node;

  return glist_concat(list, node);
}

GList glist_concat(GList list1, GList list2) {
  if (!list1)
    return list2;
  if (!list2)
    return list1;
  list1->prev->next = list2;
  list2->prev->next = list1;
  GList temp = list1->prev;
  list1->prev = list2->prev;
  list2->prev = temp;
  return list1;
}

GList glist_merge(GList list1, GList list2, Compare function) {
  if (!list1)
    return list2;
  if (!list2)
    return list1;
  if (function(list1->data, list2->data) < 0) {
    if (list1 == list1->next) {
      list1 = glist_concat(list1, list2);
    } else {
      GNode *auxNode = glist_pop(&list1, 0);
      list1 = glist_merge(list1, list2, function);
      list1 = glist_concat(auxNode, list1);
    }
    return list1;
  } else {
    if (list2 == list2->next) {
      list2 = glist_concat(list2, list1);
    } else {
      GNode *auxNode = glist_pop(&list2, 0);
      list2 = glist_merge(list1, list2, function);
      list2 = glist_concat(auxNode, list2);
    }
    return list2;
  }
}

GList glist_split(GList list) {
  GNode *node1 = list;
  GNode *node2 = list;
  for (; node1->next != list && node1->next->next != list;
       node1 = node1->next->next, node2 = node2->next);
  GList newList = node2->next;
  list->prev->next = newList;
  newList->prev = list->prev;
  list->prev = node2;
  node2->next = list;
  return newList;
}

GList glist_merge_sort(GList list, Compare function) {
  if (!list || list->next == list)
    return list;
  GList list2 = glist_split(list);

  list = glist_merge_sort(list, function);
  list2 = glist_merge_sort(list2, function);

  return glist_merge(list, list2, function);
}