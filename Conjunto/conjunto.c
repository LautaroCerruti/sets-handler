#include "conjunto.h"

typedef struct {
  int extremoIzq;
  int extremoDer;
} ElementoConjunto;

/*
  conjunto_elemento_valores_interseca: int int int int -> int
  Dados los valores de los intervalos, chequea si los mismos se intersecan
*/
int conjunto_elemento_valores_interseca(int izqElem1, int derElem1, int izqElem2, int derElem2){
  return derElem1 >= izqElem2 && izqElem1 <= derElem2;
}

/*
  conjunto_comparar_elementos_by_extremo_izquierdo: void* void* -> int
  Compara los extremos izquierdos de los elementos retornando 0 si son iguales,
  menor a 0 si el del segundo elemento es mayor que el del primero y mayor a 0
  en caso contrario
*/
int conjunto_comparar_elementos_by_extremo_izquierdo(void* elem1, void* elem2) {
  return ((ElementoConjunto *)elem1)->extremoIzq - ((ElementoConjunto *)elem2)->extremoIzq;
}

/*
  conjunto_destroy_elemento: void*
  Hace un free de un elemento conjunto
*/
void conjunto_destroy_elemento(void* elem){
  free((ElementoConjunto*) elem);
}

/*
  conjunto_extension_elemento: ElementoConjunto* ElementoConjunto*
  Dado dos elemtos conjunto extiende el primero uniendolo al segundo
*/
void conjunto_extension_elemento(ElementoConjunto* elemento, ElementoConjunto* extension) {
  elemento->extremoIzq = extension->extremoIzq < elemento->extremoIzq ? extension->extremoIzq : elemento->extremoIzq;
  elemento->extremoDer = extension->extremoDer > elemento->extremoDer ? extension->extremoDer : elemento->extremoDer;
}

/*
  extremo_mas_uno: int -> int
  dado un int, si es igua a INT_MAX retorna ese valor si no el valor+1
*/
int extremo_mas_uno(int valor){
  return valor == INT_MAX ? valor : valor + 1;
}

/*
  extremo_menos_uno: int -> int
  dado un int, si es igua a INT_MIN retorna ese valor si no el valor-1
*/
int extremo_menos_uno(int valor){
  return valor == INT_MIN ? valor : valor - 1;
}

int conjunto_compara_nombre(void* conjunto1, void* conjunto2) {
  return !strcmp(((Conjunto*)conjunto1)->nombre, ((Conjunto*)conjunto2)->nombre);
}

int conjunto_hash(int tamanio_tabla, void* conjunto1) {
  unsigned long long int value_hash = 0;
  int  i = 0;
  for (; ((Conjunto*)conjunto1)->nombre[i] != '\0'; ++i) // mientras sea distinto de terminador
    value_hash += ((Conjunto*)conjunto1)->nombre[i] * pow(2, (i % 10)); // calcula el valor de hasheo
  return (int) (value_hash % tamanio_tabla); // devuelve el resto de dividirlo por el tamanio de la tabla
}

Conjunto* conjunto_create_empty(char *nombreConjunto){
  Conjunto* conjunto = malloc(sizeof(Conjunto));
  conjunto->nombre = nombreConjunto;
  conjunto->conjunto = glist_create();
  return conjunto; // crea un conjunto vacio y lo retorna
}

Conjunto* conjunto_create_extension(char *nombreConjunto, int n1, int n2){
  Conjunto* conjunto = malloc(sizeof(Conjunto));
  conjunto->conjunto = glist_create();
  ElementoConjunto *elemAux = malloc(sizeof(ElementoConjunto));
  elemAux->extremoDer = n2;
  elemAux->extremoIzq = n1;
  conjunto->nombre = nombreConjunto;
  conjunto->conjunto = glist_insert_last_position(conjunto->conjunto, elemAux);
  return conjunto; // crea un conjunto con un elemnto con los valores pasados por parametro
}

void conjunto_destroy_conjunto(void* conjunto){
  Conjunto* aux = (Conjunto*)conjunto;
  if (aux) { // Si existe el conjunto
    if (aux->nombre) // libera el nombre
      free(aux->nombre);
    if (aux->conjunto) // si tiene elmentos
      glist_destroy(aux->conjunto, conjunto_destroy_elemento); // destruye la lista
    free(aux); // libera la memoria del conjunto
  }
}

Conjunto* conjunto_agregar_elemento(Conjunto* conjunto, int numero) {
  ElementoConjunto *elemAux = malloc(sizeof(ElementoConjunto));
  elemAux->extremoIzq = numero;
  elemAux->extremoDer = numero; // crea un elemento con los extremos del valor del numero pasado como intervalo
  conjunto->conjunto = glist_insert_last_position(conjunto->conjunto, elemAux);
  return conjunto; // lo inserta en el conjunto y lo retorna
}

Conjunto* conjunto_normalize(Conjunto* conjunto) {
  if (!conjunto->conjunto) // si el conjunto esta vacio
    return conjunto;
  conjunto->conjunto = glist_merge_sort(conjunto->conjunto, conjunto_comparar_elementos_by_extremo_izquierdo); // ordena los elementos
  GList aux = conjunto->conjunto, nodoBorrar = NULL;
  while (aux != conjunto->conjunto->prev) { // mientras no este en el ultimo nodo
    if (extremo_menos_uno(((ElementoConjunto *)aux->next->data)->extremoIzq) == ((ElementoConjunto *)aux->data)->extremoDer || ((ElementoConjunto *)aux->next->data)->extremoIzq == ((ElementoConjunto *)aux->data)->extremoDer) {
      ((ElementoConjunto *)aux->data)->extremoDer = ((ElementoConjunto *)aux->next->data)->extremoDer; // si el extremo izquierdo del siguiente nodo es igual al derecho o al derecho +1 de el nodo actual lo extiende
      aux->next->next->prev = aux;
      nodoBorrar = aux->next;
      aux->next = nodoBorrar->next;
      conjunto_destroy_elemento(nodoBorrar->data); // borra el nodo que ya no sirve
      free(nodoBorrar);
    } else
      aux = aux->next;
  }
  return conjunto; // retorna el conjunto normalizado
}

void conjunto_imprimir(Conjunto conjunto) {
  GList aux = conjunto.conjunto;
  if (conjunto.conjunto) {
    do {
        if (((ElementoConjunto*)aux->data)->extremoIzq == ((ElementoConjunto*)aux->data)->extremoDer)
          printf("%d", ((ElementoConjunto*)aux->data)->extremoIzq);
        else
          printf("%d:%d", ((ElementoConjunto*)aux->data)->extremoIzq, ((ElementoConjunto*)aux->data)->extremoDer);
        aux = aux->next;
        if (aux != conjunto.conjunto)
          printf(",");
    } while (aux != conjunto.conjunto);
  } else
    printf("conjunto vacio");

  printf("\n");
}

Conjunto* conjunto_union(Conjunto conjunto1, Conjunto conjunto2, char *nombreConjunto) {
  GList aux1 = conjunto1.conjunto, aux2 = conjunto2.conjunto;
  Conjunto* newConjunto = conjunto_create_empty(nombreConjunto); // crea un conjunto vacio
  ElementoConjunto *elemAux = NULL;
  if (!conjunto1.conjunto && !conjunto2.conjunto) { // si son vacios
    return newConjunto;
  }
  while (aux1 && aux2) { // mientras ambos tengan elementos sin unir
    if (!elemAux) { // si no existe el nodo a agregar
      elemAux = malloc(sizeof(ElementoConjunto));
      // si el extremo izquiero del nodo del primer conjunto es menor que el del segundo
      if (((ElementoConjunto*)aux1->data)->extremoIzq < ((ElementoConjunto*)aux2->data)->extremoIzq) { 
        elemAux->extremoIzq = ((ElementoConjunto*)aux1->data)->extremoIzq;
        elemAux->extremoDer = ((ElementoConjunto*)aux1->data)->extremoDer;
        aux1 = aux1->next; // le asignamos estos valores al auxiliar y desplazamos el nodo del primer conjunto
        if(aux1 == conjunto1.conjunto) // si este nodo es igual al del comienzo almacenamos NULL
          aux1 = NULL;
      } else { // si el extremo izquiero del nodo del segundo conjunto es menor que el del primero
        elemAux->extremoIzq = ((ElementoConjunto*)aux2->data)->extremoIzq;
        elemAux->extremoDer = ((ElementoConjunto*)aux2->data)->extremoDer;
        aux2 = aux2->next; // le asignamos estos valores al auxiliar y desplazamos el nodo del segundo conjunto
        if(aux2 == conjunto2.conjunto) // si este nodo es igual al del comienzo almacenamos NULL
          aux2 = NULL;
      }
    } else {
      // si el nodo auxiliar se interseca con alguno del intervalo o puede ser unificado en un unico intervalo
      if (conjunto_elemento_valores_interseca(extremo_menos_uno(elemAux->extremoIzq), extremo_mas_uno(elemAux->extremoDer), ((ElementoConjunto*)aux1->data)->extremoIzq, ((ElementoConjunto*)aux1->data)->extremoDer)
        || conjunto_elemento_valores_interseca(extremo_menos_uno(elemAux->extremoIzq), extremo_mas_uno(elemAux->extremoDer), ((ElementoConjunto*)aux2->data)->extremoIzq, ((ElementoConjunto*)aux2->data)->extremoDer)) {
        if (conjunto_elemento_valores_interseca(extremo_menos_uno(elemAux->extremoIzq), extremo_mas_uno(elemAux->extremoDer), ((ElementoConjunto*)aux1->data)->extremoIzq, ((ElementoConjunto*)aux1->data)->extremoDer)) {
          conjunto_extension_elemento(elemAux, aux1->data); // si se interseca con el del primero lo extendemos
          aux1 = aux1->next != conjunto1.conjunto ? aux1->next : NULL;
        }
        if (conjunto_elemento_valores_interseca(extremo_menos_uno(elemAux->extremoIzq), extremo_mas_uno(elemAux->extremoDer), ((ElementoConjunto*)aux2->data)->extremoIzq, ((ElementoConjunto*)aux2->data)->extremoDer)) {
          conjunto_extension_elemento(elemAux, aux2->data); // si se interseca con el del segundo lo extendemos
          aux2 = aux2->next != conjunto2.conjunto ? aux2->next : NULL;
        }
      } else {
        newConjunto->conjunto = glist_insert_last_position(newConjunto->conjunto, elemAux); // si no interseca, lo insertamos en el nuevo conjunto
        elemAux = NULL; // reseteamos el valor de la variable auxiliar
      }
    }
  }
  if (!aux1 && aux2) { // si el primer conjunto ya no tiene elementos pero el segundo si
    while (aux2) { // mientras el segundo conjunto tenga elementos
        if (!elemAux) {
          elemAux = malloc(sizeof(ElementoConjunto));
          elemAux->extremoIzq = ((ElementoConjunto*)aux2->data)->extremoIzq;
          elemAux->extremoDer = ((ElementoConjunto*)aux2->data)->extremoDer;
          aux2 = aux2->next; // vamos tomando los nodos del segundo conjunto
          if(aux2 == conjunto2.conjunto)
            aux2 = NULL;
        } else {
          if (conjunto_elemento_valores_interseca(extremo_menos_uno(elemAux->extremoIzq), extremo_mas_uno(elemAux->extremoDer), ((ElementoConjunto*)aux2->data)->extremoIzq, ((ElementoConjunto*)aux2->data)->extremoDer)) {
            conjunto_extension_elemento(elemAux, aux2->data); // revisamos la interseccion
            aux2 = aux2->next != conjunto2.conjunto ? aux2->next : NULL;
          } else {
            newConjunto->conjunto = glist_insert_last_position(newConjunto->conjunto, elemAux);
            elemAux = NULL; // lo va insertando en el conjunto
          }
        }
    }
  }
  if (aux1 && !aux2) { // si el segundo conjunto ya no tiene elementos pero el primero si
    while (aux1) { // mientras el primer conjunto tenga elementos
        if (!elemAux) {
          elemAux = malloc(sizeof(ElementoConjunto));
          elemAux->extremoIzq = ((ElementoConjunto*)aux1->data)->extremoIzq;
          elemAux->extremoDer = ((ElementoConjunto*)aux1->data)->extremoDer;
          aux1 = aux1->next; // vamos tomando los nodos del primer conjunto
          if(aux1 == conjunto1.conjunto)
            aux1 = NULL;
        } else {
          if (conjunto_elemento_valores_interseca(extremo_menos_uno(elemAux->extremoIzq), extremo_mas_uno(elemAux->extremoDer), ((ElementoConjunto*)aux1->data)->extremoIzq, ((ElementoConjunto*)aux1->data)->extremoDer)) {
            conjunto_extension_elemento(elemAux, aux1->data); // revisamos la interseccion
            aux1 = aux1->next != conjunto1.conjunto ? aux1->next : NULL;
          } else {
            newConjunto->conjunto = glist_insert_last_position(newConjunto->conjunto, elemAux);
            elemAux = NULL; // lo va insertando en el conjunto
          }
        }
    }
  }
  newConjunto->conjunto = glist_insert_last_position(newConjunto->conjunto, elemAux); // intertamos el ultimo nodo
  return newConjunto; // retornamos el conjunto
}

Conjunto* conjunto_interseccion(Conjunto conjunto1, Conjunto conjunto2, char *nombreConjunto) {
  GList aux1 = conjunto1.conjunto, aux2 = conjunto2.conjunto;
  Conjunto* newConjunto = conjunto_create_empty(nombreConjunto);
  ElementoConjunto *elemAux;
  while (aux1 && aux2) { // mientras haya elementos en ambos conjuntos
    if (conjunto_elemento_valores_interseca(((ElementoConjunto*)aux1->data)->extremoIzq, ((ElementoConjunto*)aux1->data)->extremoDer, ((ElementoConjunto*)aux2->data)->extremoIzq, ((ElementoConjunto*)aux2->data)->extremoDer)) {
      elemAux = malloc(sizeof(ElementoConjunto)); // si los mismos intersecan, creamos un nuevo nodo con el intervalo intersecado
      elemAux->extremoIzq = ((ElementoConjunto*)aux1->data)->extremoIzq > ((ElementoConjunto*)aux2->data)->extremoIzq ? ((ElementoConjunto*)aux1->data)->extremoIzq : ((ElementoConjunto*)aux2->data)->extremoIzq;
      elemAux->extremoDer = ((ElementoConjunto*)aux1->data)->extremoDer < ((ElementoConjunto*)aux2->data)->extremoDer ? ((ElementoConjunto*)aux1->data)->extremoDer : ((ElementoConjunto*)aux2->data)->extremoDer;
      newConjunto->conjunto = glist_insert_last_position(newConjunto->conjunto, elemAux); // insertamos este nodo
    }
    // movemos de elemento en el conjunto que tenga el extremo derecho mas chico
    if (((ElementoConjunto*)aux1->data)->extremoDer < ((ElementoConjunto*)aux2->data)->extremoDer)
      aux1 = aux1->next != conjunto1.conjunto ? aux1->next : NULL;
    else
      aux2 = aux2->next != conjunto2.conjunto ? aux2->next : NULL;
  }
  return newConjunto; // returnamos el nuevo conjunto
}

Conjunto* conjunto_complemento(Conjunto conjunto, char *nombreConjunto) {
  Conjunto* newConjunto = conjunto_create_empty(nombreConjunto);
  GList aux = conjunto.conjunto;
  ElementoConjunto *elemAux;
  if (aux && ((ElementoConjunto*)aux->data)->extremoIzq == INT_MIN && ((ElementoConjunto*)aux->data)->extremoDer == INT_MAX)
    return newConjunto; // si el conunto es el universo, retornamos un conjunto vacio
  elemAux = malloc(sizeof(ElementoConjunto));
  if (!aux) {
    elemAux->extremoIzq = INT_MIN;
    elemAux->extremoDer = INT_MAX;
    newConjunto->conjunto = glist_insert_last_position(newConjunto->conjunto, elemAux);
    return newConjunto; // si el conjunto es vacio retornamos uno con todos los elementos del conjunto
  }
  // si el extremo izquiero del primer nodo es distinto al INT_MIN
  if (((ElementoConjunto*)aux->data)->extremoIzq != INT_MIN) {
    elemAux->extremoIzq = INT_MIN;
    elemAux->extremoDer = ((ElementoConjunto*)aux->data)->extremoIzq - 1;
    newConjunto->conjunto = glist_insert_last_position(newConjunto->conjunto, elemAux);
    aux = aux->next; // insertamos un nodo que va de INT_MIN a extremoIzq - 1
  } else {
    aux = aux->next; // si no, saltamos al siguiente nodo
  }
  while (aux != conjunto.conjunto) {
    elemAux = malloc(sizeof(ElementoConjunto));
    elemAux->extremoIzq = ((ElementoConjunto*)aux->prev->data)->extremoDer + 1;
    elemAux->extremoDer = ((ElementoConjunto*)aux->data)->extremoIzq - 1;
    newConjunto->conjunto = glist_insert_last_position(newConjunto->conjunto, elemAux);
    aux = aux->next; // insertamos nodos que van de extremoDer + 1 del nodo anterior al extremoIzq - 1 del nodo actual
  };
  // si el extremo derecho del del ultimo nodo del conjunto es distinto a INT_MAX
  if (((ElementoConjunto*)aux->prev->data)->extremoDer != INT_MAX) {
    elemAux = malloc(sizeof(ElementoConjunto));
    elemAux->extremoIzq = ((ElementoConjunto*)aux->prev->data)->extremoDer + 1;
    elemAux->extremoDer = INT_MAX;
    newConjunto->conjunto = glist_insert_last_position(newConjunto->conjunto, elemAux);
    // insertamos un nodo que va desde el extremo derecho +1 a INT_MAX
  }
  return newConjunto; // retornamos el complemento recien creado
}

Conjunto* conjunto_resta(Conjunto conjunto1, Conjunto conjunto2, char *nombreConjunto) {
  Conjunto* complementoConjunto2 = conjunto_complemento(conjunto2, NULL); // realizamos el complemento de segundo conjunto
  Conjunto* newConjunto = conjunto_interseccion(conjunto1, *complementoConjunto2, NULL); // intersecamos el primer conjunto con el complemento del segundo
  newConjunto->nombre = nombreConjunto;
  conjunto_destroy_conjunto(complementoConjunto2); // destruimos el complemento del segundo conjunto creado como auxiliar
  return newConjunto; // retornamos la resta de los conjuntos
}

int comparar_conjunto_string(void* conjunto, void* string) {
  return strcmp(((Conjunto*)conjunto)->nombre, (char*)string) == 0 ? 1 : 0;
}