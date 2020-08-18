#include "sllist.h"

struct _SLNode {
  void *data;
  struct _SLNode *next;
};

SLList sllist_create() {
  return NULL;
}

void sllist_destroy(SLList list, Destroy function) {
  SLNode *auxNode = list;
  if (list) {                   // si existe la lista
    list = list->next;
    for (; list != NULL; list = list->next) {   // mientras haya elementos en la lista
      function(auxNode->data);  // liberamos el del nodo anterior
      free(auxNode);            // liberamos el nodo anterior
      auxNode = list;
    }
    function(auxNode->data);    // liberamos el dato del ultimo nodo
    free(auxNode);              // liberamos el nodo
  }
}

SLList sllist_insert_with_replace(SLList list, void *data, Compare compare,
                                  Destroy function) {
  SLNode *node = NULL;
  SLList aux = list;
  if (!list) {                  // si no existe la lista
    node = malloc(sizeof(SLNode));
    node->data = data;
    node->next = NULL;
    return node;                // creamos un nuevo nodo con el dato y lo retornamos
  }
  // mientras el nodo de la lista no evalue en verdadero en la comparacion y la lista no haya llegado al final se mueve por la lista
  for (; !compare(list->data, data) && list->next != NULL; list = list->next);
  if (compare(list->data, data)) {      // si la comparacion evalua verdadera
    function(list->data);       // borramos el dato guardado
    list->data = data;          // gurdamos el nuevo dato en este nodo
  } else {                      // si no
    // creamos un nuevo nodo y lo insertamos al final de la lista
    node = malloc(sizeof(SLNode));
    node->data = data;
    node->next = NULL;
    list->next = node;
  }
  return aux;
}

void *sllist_find(SLList list, void *data, Compare compare) {
  // mientras el nodo de la lista no evalue en verdadero en la comparacion y la lista no haya llegado al final se mueve por la lista
  for (; list != NULL && !compare(list->data, data); list = list->next);
  return (list ? list->data : NULL);    // si encontro el nodo lo retorna un puntero al mismo, si no retorna NULL
}
