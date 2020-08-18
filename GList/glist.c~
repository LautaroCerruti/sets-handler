#include "glist.h"

GList glist_create() {
  return NULL;
}

void glist_destroy(GList list, Destroy function) {
  GNode *auxNode;
  GNode *previous = list->prev;
  for (; list != previous; list = auxNode) { // mientras la lista no tenga un unico nodo
    auxNode = list->next;
    function(list->data);
    free(list); // liberamos el dato con la funcion y el mismo nodo
  }
  function(list->data); // liberamos el dato del ultio nodo que queda
  free(list); // liberamos el nodo
}

GList glist_insert_last_position(GList list, void *data) {
  GList node = malloc(sizeof(GNode));
  node->data = data;
  node->prev = node;
  node->next = node; // creamos un nodo con el dato y ponemos las referencias a si mismo
  return glist_concat(list, node); // lo concatenamos con el resto de la lista
}

GList glist_concat(GList list1, GList list2) {
  if (!list1) // si no existe la primera lista
    return list2; // retornamos la segunda
  if (!list2) // si no existe la segunda
    return list1; // retornamos la primera
  list1->prev->next = list2;
  list2->prev->next = list1;
  GList temp = list1->prev;
  list1->prev = list2->prev;
  list2->prev = temp;
  return list1; // concatenemos la segunda lista al final de la primera y retornamos el comienzo de la primera
}

GNode *glist_pop(GList *list) {
  GNode *node = glist_create();
  if (list && *list) { // si existe la lsita y no esta vacia
    if ((*list)->next == *list) { // si tiene un solo elemento
      node = *list; 
      list = NULL; // vacia la lista
    } else { // si tiene mas de un elemento
      node = *list;
      *list = (node)->next;
      node->prev->next = node->next;
      node->next->prev = node->prev;
      node->next = node;
      node->prev = node; // saca el primero cambiando todas las referencias
    }
  }
  return node; // retorna el elemento sacado
}

GList glist_merge(GList list1, GList list2, Compare function) {
  if (!list1) // si no existe la primera lista
    return list2; // retornamos la segunda
  if (!list2) // si no existe la segunda
    return list1; // retornamos la primera
  if (function(list1->data, list2->data) < 0) { // si la comparacion evalua menor a 0
    if (list1 == list1->next) { // si la lista tiene un solo nodo
      list1 = glist_concat(list1, list2); // las concatena
    } else {
      GNode *auxNode = glist_pop(&list1); // si no saca el primer nodo de la prier lista
      list1 = glist_merge(list1, list2, function); // hace un merge de la lista sin el primer nodo y la segunda
      list1 = glist_concat(auxNode, list1); // concatena el primer nodo de la lista sacado con la lista resultante del merge anterior
    }
    return list1; // devuelv la lista
  } else {
    if (list2 == list2->next) { // si la segunda lista tiene un solo nodo
      list2 = glist_concat(list2, list1); // las concatena
    } else {
      GNode *auxNode = glist_pop(&list2); // saca el primer nodo de la segunda lista
      list2 = glist_merge(list1, list2, function); // hace un merge de la primer lista con la segunda sin este nodo
      list2 = glist_concat(auxNode, list2); // concatena este nodo al final de la nueva segunda lista
    }
    return list2; // retorna esta segunda lista
  }
}

GList glist_split(GList list) {
  GNode *node1 = list;
  GNode *node2 = list;
  // movemos con nodos auxiliares en la lista, en uno de a 1 nodo y en otro de a 2 hasta que el que mueve de a 2 llegue a null
  // de esta forma tenemos el que se mueve a  en la mitad de la lista
  for (; node1->next != list && node1->next->next != list;
       node1 = node1->next->next, node2 = node2->next);
  GList newList = node2->next;
  list->prev->next = newList;
  newList->prev = list->prev;
  list->prev = node2;
  node2->next = list; 
  // cambiamos las referencias para que la lista quede dividida en 2, y retornamos la lista que comienza en la mitad de la que era la lista original
  return newList;
}

GList glist_merge_sort(GList list, Compare function) {
  if (!list || list->next == list)
    return list; // si la lista esta vacia o tiene solo 1 elemento la retornamos
  GList list2 = glist_split(list); // dividimos la lista

  list = glist_merge_sort(list, function); // hacemos un merge sort de la mitad de la lista
  list2 = glist_merge_sort(list2, function); // hacemos un merge sort de la otra mitad de la lista

  return glist_merge(list, list2, function); // mergeamos las 2 listas
}
