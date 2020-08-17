#include "conjunto.h"
#include <stdio.h>
#include <stdlib.h>

int conjunto_elemento_interseca(int izqElem1, int derElem1, int izqElem2, int derElem2){
return derElem1 >= izqElem2 && izqElem1 <= derElem2;
}

void conjunto_destroy_elemento(ElementoConjunto* elem){
  free(elem);
}

void conjunto_destroy_conjunto(Conjunto* conjunto){
  if (conjunto) {
    if (conjunto->nombre)
      free(conjunto->nombre);
    if (conjunto->conjunto)
      glist_destroy(conjunto->conjunto, conjunto_destroy_elemento);
    free(conjunto);
  }
}

Conjunto* conjunto_create_empty(char *nombreConjunto){
  Conjunto* conjunto = malloc(sizeof(Conjunto));
  conjunto->nombre = nombreConjunto;
  return conjunto;
}

Conjunto* conjunto_create_extension(char *nombreConjunto, int n1, int n2){
  Conjunto* conjunto = malloc(sizeof(Conjunto));
  ElementoConjunto *elemAux = malloc(sizeof(ElementoConjunto));
  elemAux->extremoDer = n2;
  elemAux->extremoIzq = n1;
  conjunto->nombre = nombreConjunto;
  conjunto->conjunto = glist_insert_last_position(conjunto->conjunto, elemAux);
  return conjunto;
}

void conjunto_extension_elemento(ElementoConjunto* elemento, ElementoConjunto* extension) {
  elemento->extremoIzq = extension->extremoIzq < elemento->extremoIzq ? extension->extremoIzq : elemento->extremoIzq;
  elemento->extremoDer = extension->extremoDer > elemento->extremoDer ? extension->extremoDer : elemento->extremoDer;
}

Conjunto* conjunto_union(Conjunto conjunto1, Conjunto conjunto2, char *nombreConjunto) {
  GList aux1 = conjunto1.conjunto, aux2 = conjunto2.conjunto;
  Conjunto* newConjunto = conjunto_create_empty(nombreConjunto);
  ElementoConjunto *elemAux;
  if (!conjunto1.conjunto && !conjunto2.conjunto) {
    return newConjunto;
  }
  while (aux1 || aux2) {
    if (!elemAux) {
      elemAux = malloc(sizeof(ElementoConjunto));
      if (aux1) {
        elemAux->extremoIzq = ((ElementoConjunto*)aux1->data)->extremoIzq;
        elemAux->extremoDer = ((ElementoConjunto*)aux1->data)->extremoDer;
        aux1 = aux1->next;
        if(aux1 == conjunto1.conjunto)
          aux1 = NULL;
      } else {
        elemAux->extremoIzq = ((ElementoConjunto*)aux2->data)->extremoIzq;
        elemAux->extremoDer = ((ElementoConjunto*)aux2->data)->extremoDer;
        aux2 = aux2->next;
        if(aux2 == conjunto2.conjunto)
          aux2 = NULL;
      }
    } else {
      if (conjunto_elemento_interseca(elemAux->extremoDer + 1, elemAux->extremoIzq + 1, ((ElementoConjunto*)aux1->data)->extremoIzq, ((ElementoConjunto*)aux1->data)->extremoDer) 
        || conjunto_elemento_interseca(elemAux->extremoDer + 1, elemAux->extremoIzq + 1, ((ElementoConjunto*)aux2->data)->extremoIzq, ((ElementoConjunto*)aux2->data)->extremoDer)) {
        if (conjunto_elemento_interseca(elemAux->extremoDer + 1, elemAux->extremoIzq + 1, ((ElementoConjunto*)aux1->data)->extremoIzq, ((ElementoConjunto*)aux1->data)->extremoDer)) {
          conjunto_extension_elemento(elemAux, aux1->data);
          aux1 = aux1->next != conjunto1.conjunto ? aux1->next : NULL;
        }
        if (conjunto_elemento_interseca(elemAux->extremoDer + 1, elemAux->extremoIzq + 1, ((ElementoConjunto*)aux2->data)->extremoIzq, ((ElementoConjunto*)aux2->data)->extremoDer)) {
          conjunto_extension_elemento(elemAux, aux2->data);
          aux2 = aux2->next != conjunto2.conjunto ? aux2->next : NULL;
        }
      } else {
        newConjunto->conjunto = glist_insert_last_position(newConjunto->conjunto, elemAux);
        elemAux = NULL;
      }
    }
  };
  newConjunto->conjunto = glist_insert_last_position(newConjunto->conjunto, elemAux);
  return newConjunto;
}

Conjunto* conjunto_interseccion(Conjunto conjunto1, Conjunto conjunto2, char *nombreConjunto) {
  GList aux1 = conjunto1.conjunto, aux2 = conjunto2.conjunto;
  Conjunto* newConjunto = conjunto_create_empty(nombreConjunto);
  ElementoConjunto *elemAux;
  while (aux1 && aux2){
    if (conjunto_elemento_interseca(((ElementoConjunto*)aux1->data)->extremoIzq, ((ElementoConjunto*)aux1->data)->extremoDer, ((ElementoConjunto*)aux2->data)->extremoIzq, ((ElementoConjunto*)aux2->data)->extremoDer)) {
      elemAux = malloc(sizeof(ElementoConjunto));
      elemAux->extremoIzq = ((ElementoConjunto*)aux1->data)->extremoIzq > ((ElementoConjunto*)aux2->data)->extremoIzq ? ((ElementoConjunto*)aux1->data)->extremoIzq : ((ElementoConjunto*)aux2->data)->extremoIzq;
      elemAux->extremoDer = ((ElementoConjunto*)aux1->data)->extremoDer < ((ElementoConjunto*)aux2->data)->extremoDer ? ((ElementoConjunto*)aux1->data)->extremoDer : ((ElementoConjunto*)aux2->data)->extremoDer;
      newConjunto->conjunto = glist_insert_last_position(newConjunto->conjunto, elemAux);
    }
    if (((ElementoConjunto*)aux1->data)->extremoDer < ((ElementoConjunto*)aux2->data)->extremoDer)
      aux1 = aux1->next != conjunto1.conjunto ? aux1->next : NULL;
    else
      aux2 = aux2->next != conjunto2.conjunto ? aux2->next : NULL;
  };
  return newConjunto;
}

Conjunto* conjunto_complemento(Conjunto conjunto, char *nombreConjunto) {
  Conjunto* newConjunto = conjunto_create_empty(nombreConjunto);
  GList aux = conjunto.conjunto;
  ElementoConjunto *elemAux;
  if (aux && ((ElementoConjunto*)aux->data)->extremoIzq == INT_MIN && ((ElementoConjunto*)aux->data)->extremoDer == INT_MAX)
    return newConjunto;
  elemAux = malloc(sizeof(ElementoConjunto));
  if (!aux) {
    elemAux->extremoIzq = INT_MIN;
    elemAux->extremoDer = INT_MAX;
    newConjunto->conjunto = glist_insert_last_position(newConjunto->conjunto, elemAux);
  }
  if (((ElementoConjunto*)aux->data)->extremoIzq != INT_MIN) {
    elemAux->extremoIzq = INT_MIN;
    elemAux->extremoDer = ((ElementoConjunto*)aux->data)->extremoIzq;
    newConjunto->conjunto = glist_insert_last_position(newConjunto->conjunto, elemAux);
    aux = aux->next;
  } else {
    aux = aux->next;
  }
  while (aux != conjunto.conjunto) {
    elemAux = malloc(sizeof(ElementoConjunto));
    elemAux->extremoIzq = ((ElementoConjunto*)aux->prev->data)->extremoDer;
    elemAux->extremoDer = ((ElementoConjunto*)aux->data)->extremoIzq;
    newConjunto->conjunto = glist_insert_last_position(newConjunto->conjunto, elemAux);
    aux = aux->next;
  };
  if (((ElementoConjunto*)aux->prev->data)->extremoDer != INT_MAX) {
    elemAux = malloc(sizeof(ElementoConjunto));
    elemAux->extremoIzq = ((ElementoConjunto*)aux->prev->data)->extremoDer;
    elemAux->extremoDer = INT_MAX;
    newConjunto->conjunto = glist_insert_last_position(newConjunto->conjunto, elemAux);
  }
  return newConjunto;
}

Conjunto* conjunto_resta(Conjunto conjunto1, Conjunto conjunto2, char *nombreConjunto) {
  GList aux1 = conjunto1.conjunto, aux2 = conjunto2.conjunto;
  ElementoConjunto *elemAux;
  Conjunto* complementoConjunto2 = conjunto_complemento(conjunto2, NULL);
  Conjunto* newConjunto = conjunto_interseccion(conjunto1, *complementoConjunto2, NULL);
  conjunto_destroy_conjunto(complementoConjunto2);
  return newConjunto;
}

void conjunto_imprimir(Conjunto conjunto) {
  GList aux = conjunto.conjunto;
  do {
    if (((ElementoConjunto*)aux->data)->extremoIzq == ((ElementoConjunto*)aux->data)->extremoDer)
      printf("%d", ((ElementoConjunto*)aux->data)->extremoIzq);
    else
      printf("%d:%d", ((ElementoConjunto*)aux->data)->extremoIzq, ((ElementoConjunto*)aux->data)->extremoDer);
    if (aux != conjunto.conjunto)
      print(",");
  } while (aux != conjunto.conjunto);
  print("\n");
}

int conjunto_compara_nombre(Conjunto* conjunto1, Conjunto* conjunto2) {
  return !strcmp(conjunto1->nombre, conjunto2->nombre);
}

int conjunto_hash(int tamanio_tabla, Conjunto* conjunto1) {
  unsigned long long int value_hash = 0;
  int  i = 0;
  for (; conjunto1->nombre[i] != '\0'; ++i)
    value_hash += conjunto1->nombre[i] * pow(2, (i % 10));
  return (int) (value_hash % tamanio_tabla);
}

Conjunto* conjunto_agregar_elemento(Conjunto* conjunto, int numero) {
  ElementoConjunto *elemAux = malloc(sizeof(ElementoConjunto));
  elemAux->extremoIzq = numero;
  elemAux->extremoDer = numero;
  conjunto->conjunto = glist_insert_last_position(conjunto->conjunto, elemAux);
  return conjunto;
}

Conjunto* conjunto_normalize(Conjunto* conjunto) {
  conjunto->conjunto = glist_merge_sort(conjunto->conjunto, conjunto_comparar_elementos_by_extremo_izquierdo);
  GList aux = conjunto->conjunto, nodoBorrar;
  while (aux != conjunto->conjunto->prev) {
    if (((ElementoConjunto *)aux->next->data)->extremoIzq - 1 == ((ElementoConjunto *)aux->data)->extremoDer) {
      ((ElementoConjunto *)aux->data)->extremoDer = ((ElementoConjunto *)aux->next->data)->extremoDer;
      aux->next->next->prev = aux;
      nodoBorrar = aux->next;
      aux->next = nodoBorrar->next;
      conjunto_destroy_elemento(nodoBorrar->data);
      free(nodoBorrar);
    } else
      aux = aux->next;
  }
  return conjunto;
}

int conjunto_comparar_elementos_by_extremo_izquierdo(void* elem1, void* elem2) {
  return ((ElementoConjunto *)elem1)->extremoIzq - ((ElementoConjunto *)elem2)->extremoIzq;
}
