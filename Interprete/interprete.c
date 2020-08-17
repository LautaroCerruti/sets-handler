#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "../THash/thash.h"
#include "../Conjunto/conjunto.h"
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

int hasheo_string(int tamanio_tabla, void *valorVoid) {
  unsigned long long int value_hash = 0;
  char* valor =(char*) valorVoid;
  int  i = 0;
  for (; valor[i] != '\0'; ++i)
    value_hash += valor[i] * pow(2, (i % 10));
  return (int) (value_hash % tamanio_tabla);
}

int comparar_conjunto_string(void* conjunto, void* string) {
  return !strcmp(((Conjunto*)conjunto)->nombre, (char*)string);
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
  if (check_alphanumeric(string)) {
    Conjunto* conjunto = tabla_buscar_elemento(tabla, string, hasheo_string, comparar_conjunto_string);
    if (conjunto)
      conjunto_imprimir(*conjunto);
    else
      printf("Conjunto no encontrado\n");
  } else {
    printf("Comando incorrecto\n");
  }
}

int inserta_conjunto_comprension(THash tabla, char* string, char* nombre_conjunto) {
  Conjunto* conjunto;
  char c = *string, *resto;
  int numero1, numero2;
  ++string;
  if (*string == ' ')
    ++string;
  if (*string != ':')
    return 1;
  ++string;
  if (*string == ' ')
    ++string;
  numero1 = strtod(string, &resto);
  
  if (string == resto || (*resto != ' ' && *resto != '<')) 
    return 1;
  string = resto;
  if (*string == ' ')
    ++string;
  if (*string != '<')
    return 1;
  ++string;
  if (*string != '=')
    return 1;
  ++string;
  if (*string == ' ')
    ++string;
  if (*string != c)
    return 1;
  ++string;
  if (*string == ' ')
    ++string;
  if (*string != '<')
    return 1;
  ++string;
  if (*string != '=')
    return 1;
  ++string;
  if (*string == ' ')
    ++string;
  numero2 = strtod(string, &resto);
  printf("%c\n", *resto);
  if (string == resto || (*resto != ' ' && *resto != '}')) 
    return 1;
  if (*string == ' ')
    ++string;
  if (*string != '}')
    return 1;
  conjunto = numero1 > numero2 ? conjunto_create_empty(nombre_conjunto) : conjunto_create_extension(nombre_conjunto, numero1, numero2);
  tabla = tabla_agregar_elemento(tabla, conjunto, conjunto_hash, conjunto_compara_nombre, conjunto_destroy_conjunto);
  return 0;
}

int inserta_conjunto_extension(THash tabla, char* string, char* nombre_conjunto) {
  char* resto;
  int numero, bandera = 0;
  Conjunto *conjunto = conjunto_create_empty(nombre_conjunto);
  while (*string !='}' && *string !='\0' && !bandera) {
    numero = strtod(string, &resto);
    if (string == resto || *resto != ' ' || *resto != ',') 
      bandera = 1;
    else
    {
      while(*string == ' ' || *string == ',')
        ++string;
      if (!isdigit(*string) && *string !='}')
        bandera = 1;
    }
    if (!bandera) {
      conjunto = conjunto_agregar_elemento(conjunto, numero);
    } 
  }
  if (bandera || (*string =='}' && *(string+1)!='\0')) {
    conjunto_destroy_conjunto(conjunto);
    return 1;
  } else {
    conjunto = conjunto_normalize(conjunto);
    tabla = tabla_agregar_elemento(tabla, conjunto, conjunto_hash, conjunto_compara_nombre, conjunto_destroy_conjunto);
    return 0;
  }
}

void realizar_operacion(THash tabla, char operacion, char* nombre_primer_conjunto, char* nombre_segundo_conjunto, char* nombre_tercer_conjunto){
  Conjunto *primerConjuntoOperacion = tabla_buscar_elemento(tabla, nombre_segundo_conjunto, hasheo_string, comparar_conjunto_string), *segundoConjuntoOperacion = NULL, *conjuntoResultado;
  if (operacion != '~')
    segundoConjuntoOperacion = tabla_buscar_elemento(tabla, nombre_tercer_conjunto, hasheo_string, comparar_conjunto_string);
  if ((primerConjuntoOperacion && operacion == '~') || (primerConjuntoOperacion && segundoConjuntoOperacion)){
    if (operacion == '~') 
      conjuntoResultado = conjunto_complemento(*primerConjuntoOperacion, nombre_primer_conjunto);
    if (operacion == '|') 
      conjuntoResultado = conjunto_union(*primerConjuntoOperacion, *segundoConjuntoOperacion, nombre_primer_conjunto);
    if (operacion == '-') 
      conjuntoResultado = conjunto_resta(*primerConjuntoOperacion, *segundoConjuntoOperacion, nombre_primer_conjunto);
    if (operacion == '&') 
      conjuntoResultado = conjunto_interseccion(*primerConjuntoOperacion, *segundoConjuntoOperacion, nombre_primer_conjunto);
  tabla = tabla_agregar_elemento(tabla, conjuntoResultado, conjunto_hash, conjunto_compara_nombre, conjunto_destroy_conjunto);
  } else
    printf("Conjunto inexistente\n");
}

int main() {
  char buffer[MAX_LINEA], aux[MAX_NOMBRE_CONJUNTO], *bufferAux, *nombre_primer_conjunto = NULL, *nombre_segundo_conjunto = NULL, *nombre_tercer_conjunto = NULL, operacion;
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
    error = 0;
    nombre_primer_conjunto = NULL;
    nombre_segundo_conjunto = NULL;
    nombre_tercer_conjunto = NULL;
    if (buffer[0] == 'i' && buffer[1] == 'm' && buffer[2] == 'p'
      && buffer[3] == 'r' && buffer[4] == 'i' && buffer[5] == 'm'
      && buffer[6] == 'i' && buffer[7] == 'r' && buffer[8] == ' ') 
      imprimir(tabla, buffer + 9);
    else {
      for(i = 0;i<MAX_NOMBRE_CONJUNTO && buffer[i] != '=' && buffer[i] != '\0'; ++i){
        aux[i] = buffer[i];
      }
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
        if (buffer[i]==' ')
          ++i;
        if (buffer[i]=='{') {
          ++i;
          if(isalpha(buffer[i])){
            error = inserta_conjunto_comprension(tabla, buffer+i, nombre_primer_conjunto);
          } else if (isdigit(buffer[i])) {
            error = inserta_conjunto_extension(tabla, buffer+i, nombre_primer_conjunto);
          } else 
            error = 1;
        } else if (buffer[i]=='~') {
          bufferAux = buffer + (i+1);
          operacion = buffer[i];

          for(i = 0;i<MAX_NOMBRE_CONJUNTO && *bufferAux != '-' && *bufferAux != '&' && *bufferAux != '|' && *bufferAux != '\0' && !error; ++bufferAux) {
            aux[i] = *bufferAux;
            ++i;
          }
            
          if ((*bufferAux == '-' || *bufferAux == '&' || *bufferAux == '|') && i > 0 && !error) {
            operacion = *bufferAux;
            if(aux[i-1] == ' ')
              aux[i-1] = '\0';
            else
              aux[i] = '\0';
            if (check_alphanumeric(aux)) {
              nombre_segundo_conjunto = malloc(sizeof(char)*strlen(aux));
              strcpy(nombre_segundo_conjunto, aux);
            } else
              error = 1;
          } else
            error = 1;

          // Complemento
          realizar_operacion(tabla, operacion, nombre_primer_conjunto, nombre_segundo_conjunto, nombre_tercer_conjunto);
        } else if (!isalnum(buffer[i]))
          error = 1;
        else {
          bufferAux = buffer + i;
          printf("PIJAAAAA\n");
          for(i = 0;i<MAX_NOMBRE_CONJUNTO && *bufferAux != '-' && *bufferAux != '&' && *bufferAux != '|' && *bufferAux != '\0' && !error; ++bufferAux) {
            aux[i] = *bufferAux;
            ++i;
          }
            
          if ((*bufferAux == '-' || *bufferAux == '&' || *bufferAux == '|') && i > 0 && !error) {
            operacion = *bufferAux;
            if(aux[i-1] == ' ')
              aux[i-1] = '\0';
            else
              aux[i] = '\0';
            if (check_alphanumeric(aux)) {
              nombre_segundo_conjunto = malloc(sizeof(char)*strlen(aux));
              strcpy(nombre_segundo_conjunto, aux);
            } else
              error = 1;
          } else
            error = 1;

          if (!error) {
            ++bufferAux;
            if (*bufferAux == ' ')
              ++bufferAux;
            
            for(i = 0;i<MAX_NOMBRE_CONJUNTO && *bufferAux != '\0' && !error; ++bufferAux) {
              aux[i] = *bufferAux;
              ++i;
            }

            if (*bufferAux == '\0' && i > 0 && !error) {
              if(aux[i-1] == ' ')
                aux[i-1] = '\0';
              else
                aux[i] = '\0';
              if (check_alphanumeric(aux)) {
                nombre_tercer_conjunto = malloc(sizeof(char)*strlen(aux));
                strcpy(nombre_tercer_conjunto, aux);
              } else
                error = 1;
            } else
              error = 1;

            realizar_operacion(tabla, operacion, nombre_primer_conjunto, nombre_segundo_conjunto, nombre_tercer_conjunto);
            
          }
          if (nombre_segundo_conjunto)
            free(nombre_segundo_conjunto);
          if (nombre_tercer_conjunto)
            free(nombre_tercer_conjunto);
        }
      }
    }
    if (error)
      printf("Entrada incorrecta\n");
  }
  tabla_destruir(tabla, conjunto_destroy_conjunto);
  return 0;
}
