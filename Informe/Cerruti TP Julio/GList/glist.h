#ifndef __GLIST_H__
#define __GLIST_H__

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _GNode {
  void *data;
  struct _GNode *prev;
  struct _GNode *next;
} GNode;

typedef GNode *GList;

typedef int (*Compare) (void *data1, void *data2);

typedef void (*Destroy) (void *data);

/*
  glist_create: -> GList
  Crea una GList y le da valor NULL
*/
GList glist_create();

/*
  glist_destroy: GList Destroy
  Toma una lista y una funcion y libera los nodos de la lista y
  sus datos correspondientes con la funcion obtenida.
*/
void glist_destroy(GList list, Destroy function);

/*
  glist_pop: GList* -> GNode*
  Toma una lista y saca el primer nodo de la misma y lo retorna
*/
GNode *glist_pop(GList *list);

/*
  glist_concat: GList GList -> GList
  Toma 2 listas y devuelve su union.
*/
GList glist_concat(GList list1, GList list2);

/*
  glist_insert_last_position: GList void* -> GList
  Toma una lista y un dato, inserta el dato en la ultima posicion
  de la lista y la devuelve.
*/
GList glist_insert_last_position(GList list, void *data);

/*
  glist_merge: GList GList Compare -> GList
  Toma 2 listas y una funcion de comparacion, y devuelve una nueva lista
  con los elementos de ambas ordenados. Para este ordenamiento utiliza 
  dicha funcion de comparacion.
*/
GList glist_merge(GList list1, GList list2, Compare function);

/*
  glist_split: GList -> GList
  Toma una lista, la divide en 2, devuelve la primer mitad y cambia la
  lista obtenida para que sea la segunda.
*/
GList glist_split(GList list);

/*
  glist_merge_sort: GList Compare -> GList
  Toma una lista y una funcion de comparacion, y utiliza el algoritmo
  merge sort para ordenar sus nodos comparandolos con la funcion
  obtenida.
*/
GList glist_merge_sort(GList list, Compare function);

#endif                          /* __GLIST_H__ */
