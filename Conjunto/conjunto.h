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

#endif /* __CONJUNTO_H__ */
