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
  Crea una GList y le da valor NULL
*/
SLList sllist_create();

/*
  Toma una lista y una funcion y libera los nodos de la lista y
  sus datos correspondientes con la funcion obtenida.
*/
void sllist_destroy(SLList list, Destroy function);

/*
  Toma una lista y un dato, inserta el dato en la ultima posicion
  de la lista y la devuelve.
*/
SLList sllist_insert_with_replace(SLList list, void *data, Compare);

/*
  Toma una lista y un dato, inserta el dato en la ultima posicion
  de la lista y la devuelve.
*/
SLList sllist_find(SLList list, void *data, Compare);

#endif  /* __SLLIST_H__ */
