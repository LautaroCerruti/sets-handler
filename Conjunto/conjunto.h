#ifndef __CONJUNTO_H__
#define __CONJUNTO_H__

#include <stddef.h>
#include <../GList/glist.h>
#include <time.h>
#include <stdio.h>

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

void conjunto_destroy_conjunto(Conjunto* conjunto);

int conjunto_compara_nombre(Conjunto* conjunto1, Conjunto* conjunto2);

int conjunto_hash(int tamanio_tabla, Conjunto* conjunto1);

Conjunto* conjunto_agregar_elemento(Conjunto* conjunto, int numero);

Conjunto* conjunto_normalize(Conjunto* conjunto);

#endif /* __CONJUNTO_H__ */
