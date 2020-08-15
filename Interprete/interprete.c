#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <../THash/thash.h>
#include <../Conjunto/conjunto.h>
#define MAX_LINEA 1000
#define MAX_NOMBRE_CONJUNTO 50

int check_alphanumeric(char* string) {
  int ban = 1, i = 0;
  for (; string[i] != '\0'; ++i){
    if (!isalnum(string[i]))
      ban = 0;
  }
  return ban;
}

int hasheo_string(char *valor) {
  unsigned long long int value_hash = 0;
  int  i = 0;
  for (; valor[i] != '\0'; ++i)
    value_hash += valor[i] * pow(2, (i % 10));
  return (int) (value_hash % TAMANIO_TABLA);
}

int comparar_conjunto_string(Conjunto* conjunto, char* string) {
  return !strcmp(conjunto->nombre, string);
}

/*
    leer_cadena: char* -> char*
    Toma lo escrito por el teclado ignorando los espacios en blanco extras,
    y lo retorna reemplazando el salto de linea por un '\0'.
*/
char *leer_cadena(char *string) {
  char c, *aux = string;
  int espacio = 0;
  // Mientras que el caracter leido sea distinto a '\n'
  while ((c = getchar()) != '\n') {
    if (c != '\r' && c != ' ') {     // Si el caracter leido es distinto a '\r'
      *string = c;              // Almacenamos el caracter en string
      ++string;                 // Movemos la posicion a la que apunta string
    }
    if (c == ' ') {
      if (!espacio) {
        espacio = 1;
        *string = c;              // Almacenamos el caracter en string
        ++string;
      }
    } else {
      espacio = 0;
    }
  }
  *string = '\0';               // Colocamos un terminador al final
  return aux;                   // Devolvemos un puntero al comienzo de string
}

void imprimir(THash tabla, char* string){
  if(check_alphanumeric(string)){
    Conjunto* conjunto = tabla_buscar_elemento(tabla, string, hasheo_string, comparar_conjunto_string);
    if (conjunto)
      conjunto_imprimir(*conjunto);
    else
      printf("Conjunto no encontrado\n");
  } else {
    printf("Comando incorrecto\n");
  }
}

int main() {
  char buffer[MAX_LINEA], aux[MAX_NOMBRE_CONJUNTO], *nombre_primer_conjunto = NULL;
  int i = 0, error =0;
  buffer[0] = '\0';
  THash tabla = tabla_hash_crear();

//   printf("|: Union\n");
//   printf("e: Eliminar\n");
//   printf("?: Intersecar\n");
//   printf("Estos comandos deberan ser de la manera:\n");
//   printf("  'CaracterOperacion [Numero1, Numero2]'\n");
//   printf("dfs, bfs: Mostrar arbol\n");
//   printf("salir: Finalizar programa\n\n");
  while (strcmp(leer_cadena(buffer), "salir\0")) {
    if (buffer[0] == 'i' && buffer[1] == 'm' && buffer[2] == 'p'
      && buffer[3] == 'r' && buffer[4] == 'i' && buffer[5] == 'm'
      && buffer[6] == 'i' && buffer[7] == 'r' && buffer[8] == ' ') 
      imprimir(tabla, buffer + 9);
    else {
      for(;i<MAX_NOMBRE_CONJUNTO && buffer[i] != '=' && buffer[i] != '\0'; ++i)
        aux[i] = buffer[i];
      if (buffer[i] == '=' && i > 0) {
        if(aux[i-1] == ' ')
          aux[i-1] = '\0';
        else
          aux[i] = '\0';
        if (check_alphanumeric(aux)) {
          nombre_primer_conjunto = malloc(sizeof(char)*strlen(aux));
          strcpy(nombre_primer_conjunto, aux);
        } else
          error = 1;
      } else
        error = 1;
      if (!error) {
        ++i;
        if ()
      }
    }
    if (error)
      printf("Entrada incorrecta \n");
  }
  return 0;
}
