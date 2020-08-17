#ifndef __GLIST_H__
#define __GLIST_H__

#include <stddef.h>
#include <time.h>
#include <stdio.h>

typedef struct _GNode {
  void *data;
  struct _GNode *prev;
  struct _GNode *next;
} GNode;

typedef GNode *GList;

typedef int (*Compare) (void *data1, void *data2);

typedef void (*Destroy) (void *data);

typedef void (*VisitorFunction) (FILE *output, void *data);

typedef GList(*SortAlgorithm) (GList list, Compare function);

/*
  Crea una GList y le da valor NULL
*/
GList glist_create();
/*
  Toma una lista y una funcion y libera los nodos de la lista y
  sus datos correspondientes con la funcion obtenida.
*/
void glist_destroy(GList list, Destroy function);

/*
  Toma una lista y una posicion y saca el nodo en dicha posicion
  de la lista y lo devuelve.
*/
GNode *glist_pop(GList *list, int pos);
/*
  Toma 2 listas y devuelve su union.
*/
GList glist_concat(GList list1, GList list2);

/*
  Toma una lista y un dato, inserta el dato en la ultima posicion
  de la lista y la devuelve.
*/
GList glist_insert_last_position(GList list, void *data);

/*
  Toma 2 listas y una funcion de comparacion, y devuelve una nueva lista
  con los elementos de ambas ordenados. Para este ordenamiento utiliza 
  dicha funcion de comparacion.
*/
GList glist_merge(GList list1, GList list2, Compare function);

/*
  Toma una lista, la divide en 2, devuelve la primer mitad y cambia la
  lista obtenida para que sea la segunda.
*/
GList glist_split(GList list);

/*
  Toma una lista y una funcion de comparacion, y utiliza el algoritmo
  merge sort para ordenar sus nodos comparandolos con la funcion
  obtenida.
*/
GList glist_merge_sort(GList list, Compare function);

#endif                          /* __GLIST_H__ */
