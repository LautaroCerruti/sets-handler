#include "thash.h"
#include <stdio.h>
#include <stdlib.h>

GList* tabla_hash_crear(){
    GList* tabla = (GList*)malloc(sizeof(GList)*TAMANIO_TABLA);
    for (int i = 0; i < TAMANIO_TABLA; i++) {
        tabla[i] = NULL;
    }
    return tabla;
}

GList* tabla_agregar_elemento(GList* tabla, void* dato, FuncionHasheo hasheo, FuncionComparacion) {
    
    return tabla;
}