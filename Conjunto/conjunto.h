#ifndef __CONJUNTO_H__
#define __CONJUNTO_H__

#include "../GList/glist.h"
#include <stddef.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

typedef struct {
  char *nombre;
  GList conjunto;
} Conjunto;

typedef struct {
  int extremoIzq;
  int extremoDer;
} ElementoConjunto;

void conjunto_imprimir(Conjunto conjunto);

Conjunto* conjunto_create_empty(char *nombreConjunto);

Conjunto* conjunto_create_extension(char *nombreConjunto, int n1, int n2);

void conjunto_destroy_conjunto(void* conjunto);

int conjunto_compara_nombre(void* conjunto1, void* conjunto2);

int conjunto_hash(int tamanio_tabla, void* conjunto1);

Conjunto* conjunto_agregar_elemento(Conjunto* conjunto, int numero);

Conjunto* conjunto_normalize(Conjunto* conjunto);

Conjunto* conjunto_complemento(Conjunto conjunto, char *nombreConjunto);

Conjunto* conjunto_resta(Conjunto conjunto1, Conjunto conjunto2, char *nombreConjunto);

Conjunto* conjunto_interseccion(Conjunto conjunto1, Conjunto conjunto2, char *nombreConjunto);

Conjunto* conjunto_union(Conjunto conjunto1, Conjunto conjunto2, char *nombreConjunto);
#endif /* __CONJUNTO_H__ */
