#include "thash.h"
#include <stdio.h>
#include <stdlib.h>

THash tabla_hash_crear(){
    SLList* tabla = (SLList*)malloc(sizeof(SLList)*TAMANIO_TABLA);
    for (int i = 0; i < TAMANIO_TABLA; i++) {
        tabla[i] = sllist_create();
    }
    return tabla;
}

THash tabla_agregar_elemento(SLList* tabla, void* dato, FuncionHasheo hasheo, Compare comparar, Destroy destruir) {
    int valhasheo = hasheo(dato);
    tabla[valhasheo] = sllist_insert_with_replace(tabla[valhasheo], dato, comparar, destruir);
    return tabla;
}

void* tabla_buscar_elemento(SLList* tabla, void* dato, FuncionHasheo hasheo, Compare comparar) {
    int valhasheo = hasheo(dato);
    return sllist_find(tabla[hasheo(dato)], dato, comparar);
}

void tabla_destruir(SLList* tabla, Destroy destruir) {
    int i = 0;
    for(;i < TAMANIO_TABLA; ++i){
        sllist_destroy(tabla[i], destruir);
    }
    free(tabla);
}