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
  Toma una lista y devuelve una nueva con los mismos datos de la
  primera. Los nodos de esta nueva lista no son los mismos pero
  los datos dentro de ellos si.
*/
GList glist_copy(GList list);

/*
  Toma una lista y libera los nodos de dicha lista pero no los datos
  dentro de ellos.
*/
void glist_destroy_copy(GList list);

/*
  Toma un archivo, una lista y una funcion. Utilizando dicha funcion,
  imprime los datos de la lista en las lineas del archivo.
*/
void glist_print_file(FILE *output, GList list, VisitorFunction function);

/*
  Toma 2 nodos e intercambia sus datos;
*/
void glist_swap(GNode *nodo1, GNode *nodo2);

/*
  Toma una lista y una funcion de comparacion, y utiliza el algoritmo
  seleccion sort para ordenar sus nodos comparandolos con la funcion
  obtenida.
*/
GList glist_selection_sort(GList list, Compare function);

/*
  Toma una lista y una funcion de comparacion, y utiliza el algoritmo
  insertion sort para ordenar sus nodos comparandolos con la funcion
  obtenida.
*/
GList glist_insertion_sort(GList list, Compare function);

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

/*
  Toma el nombre de un arhcivo, una lista, un algorito de ordenamiento,
  una funcion de comparacion y funcion que imprime datos en un arhcivo.
  En esta crea un archivo con el nombre proporcionado, una copia de la 
  lista obtenida, aplica la funcion de ordenamiento en dicha lista,
  escribe en el archivo el tiempo que demoro en hacerlo, escribe en cada
  linea del archivo los datos de la nueva lista y finalmente elimina la
  copia de la lista.
*/
void glist_test_sort_algorithm(char *nombreArchivo, GList list,
                               SortAlgorithm sort, Compare functionCompare,
                               VisitorFunction functionVisit);

#endif                          /* __GLIST_H__ */
