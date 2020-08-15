#ifndef __THASH_H__
#define __THASH_H__

#include <stddef.h>
#include <time.h>
#include <stdio.h>
#include <../SLList/sllist.h>

#define TAMANIO_TABLA 499

typedef SLList* THash;

typedef int (*FuncionHasheo) (int tamanio_tabla, void *dato);

THash tabla_hash_crear();

THash tabla_agregar_elemento(SLList* tabla, void* dato, FuncionHasheo hasheo, Compare comparar, Destroy destruir);

void* tabla_buscar_elemento(SLList* tabla, void* dato, FuncionHasheo hasheo, Compare comparar);

void tabla_destruir(SLList* tabla, Destroy destruir);

#endif /* __THASH_H__ */
