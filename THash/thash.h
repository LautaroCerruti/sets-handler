#ifndef __THASH_H__
#define __THASH_H__

#include <stddef.h>
#include <time.h>
#include <stdio.h>
#include <../GList/glist.h>

#define TAMANIO_TABLA 499

typedef int *(*FuncionHasheo) (void *dato);

#endif /* __THASH_H__ */
