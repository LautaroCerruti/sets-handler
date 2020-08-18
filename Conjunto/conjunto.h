#ifndef __CONJUNTO_H__
#define __CONJUNTO_H__

#include "../GList/glist.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

typedef struct {
  char *nombre;
  GList conjunto;
} Conjunto;

/*
  conjunto_compara_nombre: void* void* -> int
  Dados 2 conjuntos compara sus nombres retornando 1 si son iguales,
  0 en caso contrario
*/
int conjunto_compara_nombre(void* conjunto1, void* conjunto2);

/*
  conjunto_hash: int void* -> int
  dado el tamanio de la tabla y el conjunto, genera un hasheo segun su nombre
*/
int conjunto_hash(int tamanio_tabla, void* conjunto1);

/*
  conjunto_create_empty: char* -> Conjunto*
  Dado un array de char, retorna un conjunto vacio con array de nombre
*/
Conjunto* conjunto_create_empty(char *nombreConjunto);

/*
  conjunto_create_extension: char* int int -> Conjunto*
  crea un conjunto con un solo elemento en la lista dado por los enteros 
  pasados como parametros y de nombre el array de char pasado como parametro
*/
Conjunto* conjunto_create_extension(char *nombreConjunto, int n1, int n2);

/*
  conjunto_destroy_conjunto: void*
  dado un conjunto lo destruye
*/
void conjunto_destroy_conjunto(void* conjunto);

/*
  conjunto_agregar_elemento: Conjunto* int -> Conjunto*
  dado un conjunto y un numero, agrega este ultimo al conjunto
*/
Conjunto* conjunto_agregar_elemento(Conjunto* conjunto, int numero);

/*
  conjunto_normalize: Conjunto* -> Conjunto*
  dado un conjunto, ordena sus elementos, en caso de haber repetidos los 
  elimina y en caso de tener intervalos pero con los elementos de forma
  individual cambia los extremos y elimina los nodos para que quede bien
  almacenado
*/
Conjunto* conjunto_normalize(Conjunto* conjunto);

/*
  conjunto_imprimir: Conjunto
  Dado un conjunto, lo imprime por pantalla
*/
void conjunto_imprimir(Conjunto conjunto);

/*
  conjunto_union: Conjunto Conjunto char* -> Conjunto*
  Toma 2 conjuntos y un nombre, une los 2 conjuntos en uno nuevo,
  le pone como nombre el array de char y retorna un puntero al mismo
*/
Conjunto* conjunto_union(Conjunto conjunto1, Conjunto conjunto2, char *nombreConjunto);

/*
  conjunto_interseccion: Conjunto Conjunto char* -> Conjunto*
  Toma 2 conjuntos y un nombre, interseca los 2 conjuntos en uno nuevo,
  le pone como nombre el array de char y retorna un puntero al mismo
*/
Conjunto* conjunto_interseccion(Conjunto conjunto1, Conjunto conjunto2, char *nombreConjunto);

/*
  conjunto_complemento: Conjunto char* -> Conjunto*
  Dado un conjunto y un nombre, le hace el complemento, lo almacena en 
  uno nuevo y le pone de nombre el array de char pasado,
  retorna un puntero al mismo
*/
Conjunto* conjunto_complemento(Conjunto conjunto, char *nombreConjunto);

/*
  conjunto_resta: Conjunto Conjunto char* -> Conjunto*
  Toma 2 conjuntos y un nombre, resta los 2 conjuntos en uno nuevo,
  le pone como nombre el array de char y retorna un puntero al mismo
*/
Conjunto* conjunto_resta(Conjunto conjunto1, Conjunto conjunto2, char *nombreConjunto);

/*
  comparar_conjunto_string: void* void* -> int
  Compara el nombre d eun conjunto con un string
*/
int comparar_conjunto_string(void* conjunto, void* string);

#endif /* __CONJUNTO_H__ */
