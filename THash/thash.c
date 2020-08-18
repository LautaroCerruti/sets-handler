#include "thash.h"

THash tabla_hash_crear() {
  SLList *tabla = (SLList *) malloc(sizeof(SLList) * TAMANIO_TABLA);    // asignamos la memoria de la tabla
  for (int i = 0; i < TAMANIO_TABLA; i++) {
    tabla[i] = sllist_create(); // inicializamos todas las lingked list de la tabla
  }
  return tabla;                 // retornamos la tabla
}

THash tabla_agregar_elemento(SLList * tabla, void *dato, FuncionHasheo hasheo,
                             Compare comparar, Destroy destruir) {
  int valhasheo = hasheo(TAMANIO_TABLA, dato);  // hasheamos el dato para saber el indice de la tabla
  tabla[valhasheo] = sllist_insert_with_replace(tabla[valhasheo], 
                                                dato, comparar, destruir);    // insertamos en la linked list que corresonde a ese indice el dato
  return tabla;
}

void *tabla_buscar_elemento(SLList * tabla, void *dato, FuncionHasheo hasheo,
                            Compare comparar) {
  int valhasheo = hasheo(TAMANIO_TABLA, dato);  // hasheamos el dato para saber el indice de la tabla
  return sllist_find(tabla[valhasheo], dato, comparar); // buscamos en la linked list el dato
}

void tabla_destruir(SLList * tabla, Destroy destruir) {
  int i = 0;
  for (; i < TAMANIO_TABLA; ++i) {
    sllist_destroy(tabla[i], destruir); // destruimos todas las linked lists
  }
  free(tabla);                  // liberamos la memoria de la tabla
}
