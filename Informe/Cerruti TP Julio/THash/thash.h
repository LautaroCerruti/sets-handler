#ifndef __THASH_H__
#define __THASH_H__

#include "../SLList/sllist.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define TAMANIO_TABLA 499

typedef SLList* THash;

typedef int (*FuncionHasheo) (int tamanio_tabla, void *dato);

/*
  tabla_hash_crear: -> THash
  Devuelve una tabla hash vacia
*/
THash tabla_hash_crear();

/*
  tabla_agregar_elemento: SLList* void* FuncionHasheo Compare Destroy -> THash
  Toma una tabla, un dato, una funcion para hashear, una para comparar y una para destruir
  si encuentra en la tabla algun dato que coincida con el dato a agregar, lo reemplaza destruyendo el anterior,
  si no simplemente lo agrega a la tabla
*/
THash tabla_agregar_elemento(SLList* tabla, void* dato, FuncionHasheo hasheo, Compare comparar, Destroy destruir);

/*
  tabla_buscar_elemento: SLList* void* FuncionHasheo Compare -> void*
  Busca un elemento en la tabla, si lo encuentra lo retorna, si no retorna null
*/
void* tabla_buscar_elemento(SLList* tabla, void* dato, FuncionHasheo hasheo, Compare comparar);

/*
  tabla_destruir: SLList* Destroy
  Toma una tabla y una funcion para desruir los elmentos y destruye la tabla
*/
void tabla_destruir(SLList* tabla, Destroy destruir);

#endif /* __THASH_H__ */
