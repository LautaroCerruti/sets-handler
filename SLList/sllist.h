#ifndef __SLLIST_H__
#define __SLLIST_H__

#include <stddef.h>
#include <time.h>
#include <stdio.h>

typedef struct _SLNode SLNode;

typedef SLNode *SLList;

typedef int (*Compare) (void *data1, void *data2);

typedef void (*Destroy) (void *data);

/*
  Crea una SLList y le da valor NULL
*/
SLList sllist_create();

/*
  Toma una lista y una funcion y libera los nodos de la lista y
  sus datos correspondientes con la funcion obtenida.
*/
void sllist_destroy(SLList list, Destroy function);

/*
  Toma una lista, un dato, una funcion de comparacion y una funcion de destruccion.
  Si encuentra un dato en la lista que evalue en verdaderoen la comparacion con el dato a guardar,
  lo reemplaza, si no almacena el dato al final de la lista y la retorna
*/
SLList sllist_insert_with_replace(SLList list, void *data, Compare compare, Destroy function);

/*
 Toma una lista, un void* y una funcion de comparacion
  Busca en la lista el dato que evalue verdadero con el void*, en caso de contrarlo lo retorna,
  en caso contrario retorna NULL
*/
void* sllist_find(SLList list, void *data, Compare compare);

#endif  /* __SLLIST_H__ */
