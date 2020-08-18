#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "./THash/thash.h"
#include "./Conjunto/conjunto.h"
#define MAX_LINEA 1000
#define MAX_NOMBRE_CONJUNTO 50

/*
  check_alphanumeric: char* -> int
  chequea que todo los caracteres de un string sean alphanumericos
*/
int check_alphanumeric(char* string) {
  int ban = 1, i = 0;
  for (; string[i] != '\0' && ban; ++i){
    if (!isalnum(string[i])) //si no es alfanumerico el caracter
      ban = 0; // cambia la bandera a 0
  }
  return ban;
}

/*
  hasheo_string: int void -> int
  Dado el tamanio de la tabla y el string, calcula el hasheo
*/
int hasheo_string(int tamanio_tabla, void *valorVoid) {
  unsigned long long int value_hash = 0;
  char* valor =(char*) valorVoid;
  int  i = 0;
  for (; valor[i] != '\0'; ++i)
    value_hash += valor[i] * pow(2, (i % 10));
  return (int) (value_hash % tamanio_tabla);
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

/*
  imprimir: THash char*
  Busca un conjunto en la tabla hash y lo imprime
*/
void imprimir(THash tabla, char* string){
  if (check_alphanumeric(string)) { // Si no es valido el nombre del cojunto
    // busca el conjunto en la tabla
    Conjunto* conjunto = tabla_buscar_elemento(tabla, string, hasheo_string, comparar_conjunto_string);
    if (conjunto) // si existe
      conjunto_imprimir(*conjunto);
    else // si no existe lo informa
      printf("Conjunto no encontrado\n");
  } else {
    printf("Comando incorrecto\n");
  }
}

/*
  inserta_conjunto_comprension: THash char* char* -> int
  Dada la tabla, el string a parsear y el nombre del conjunto,
  se fija que respete el formato y agrega el conjunto a la tabla.
  Retorna 1 si hubo un error en la sintaxis, 0 en caso contrario
*/
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
  if (string == resto || (*resto != ' ' && *resto != '}'))
    return 1;
  string = resto;
  if (*string == ' ')
    ++string;
  if (*string != '}')
    return 1;
  // si el extremo izquiero es mas grande al derecho crea un conjunto vacio, en otro caso, crea el intervalo
  conjunto = numero1 > numero2 ? conjunto_create_empty(nombre_conjunto) : conjunto_create_extension(nombre_conjunto, numero1, numero2);
  tabla = tabla_agregar_elemento(tabla, conjunto, conjunto_hash, conjunto_compara_nombre, conjunto_destroy_conjunto);
  return 0;
}

/*
  inserta_conjunto_extension: THash char* char* -> int
  Dada la tabla, el string a parsear y el nombre del conjunto,
  se fija que respete el formato y agrega el conjunto a la tabla.
  Retorna 1 si hubo un error en la sintaxis, 0 en caso contrario
*/
int inserta_conjunto_extension(THash tabla, char* string, char* nombre_conjunto) {
  char* resto;
  int numero, bandera = 0;
  Conjunto *conjunto = conjunto_create_empty(nombre_conjunto);
    while (*string !='}' && *string !='\0' && !bandera) {
    numero = strtod(string, &resto);
    if (string == resto || (*resto != ' ' && *resto != ',' && *resto != '}'))
      bandera = 1;
    else
    {
      string = resto;
      if (*string == ' ')
        ++string;
      if (*string == ',')
        ++string;
      else if (*string !='}')
        bandera = 1;
      if (*string == ' ')
        ++string;
      if (!isdigit(*string) && *string != '-' && *string !='}')
        bandera = 1;
    }
    if (!bandera) {
      conjunto = conjunto_agregar_elemento(conjunto, numero); // va agregando los elementos a medida que los lee
    }
  }
  if (bandera || (*string =='}' && *(string+1)!='\0')) {
    conjunto_destroy_conjunto(conjunto); // si algo fallo destruye el conjunto creado
    return 1;
  } else {
    conjunto = conjunto_normalize(conjunto); // si la sintaxis estaba bien, ordena y normaliza el conjunto creado
    tabla = tabla_agregar_elemento(tabla, conjunto, conjunto_hash, conjunto_compara_nombre, conjunto_destroy_conjunto);
    // lo agrega a la tabla
    return 0;
  }
}

/*
  realizar_operacion: THash char char* char* char*
  Dada una tabla, la operacion a realizar, el nombre del nuevo conjunto, 
  y los nombres de los conjuntos a operar, realiza la operacion que 
  corresponde
*/
void realizar_operacion(THash tabla, char operacion, char* nombre_primer_conjunto, char* nombre_segundo_conjunto, char* nombre_tercer_conjunto){
  Conjunto *primerConjuntoOperacion = tabla_buscar_elemento(tabla, nombre_segundo_conjunto, hasheo_string, comparar_conjunto_string), *segundoConjuntoOperacion = NULL, *conjuntoResultado;
  if (operacion != '~') // si la operacion no es complemento
    segundoConjuntoOperacion = tabla_buscar_elemento(tabla, nombre_tercer_conjunto, hasheo_string, comparar_conjunto_string); // busca el segundo conjunto a operar
  if ((primerConjuntoOperacion && operacion == '~') || (primerConjuntoOperacion && segundoConjuntoOperacion)){
    if (operacion == '~')
      conjuntoResultado = conjunto_complemento(*primerConjuntoOperacion, nombre_primer_conjunto);
    if (operacion == '|')
      conjuntoResultado = conjunto_union(*primerConjuntoOperacion, *segundoConjuntoOperacion, nombre_primer_conjunto);
    if (operacion == '-')
      conjuntoResultado = conjunto_resta(*primerConjuntoOperacion, *segundoConjuntoOperacion, nombre_primer_conjunto);
    if (operacion == '&')
      conjuntoResultado = conjunto_interseccion(*primerConjuntoOperacion, *segundoConjuntoOperacion, nombre_primer_conjunto);
  // realiza la operacion correspondiente y agrega el conjunto a la tabla
  tabla = tabla_agregar_elemento(tabla, conjuntoResultado, conjunto_hash, conjunto_compara_nombre, conjunto_destroy_conjunto);
  } else { // si no encuentra algun conjunto lo informa
    printf("Conjunto inexistente\n");
    free(nombre_primer_conjunto);
  }
}

int main() {
  char buffer[MAX_LINEA], aux[MAX_NOMBRE_CONJUNTO], *bufferAux, *nombre_primer_conjunto = NULL, *nombre_segundo_conjunto = NULL, *nombre_tercer_conjunto = NULL, operacion;
  int i = 0, error =0;
  buffer[0] = '\0';
  THash tabla = tabla_hash_crear(); // crea la tabla

//   printf("|: Union\n");
//   printf("e: Eliminar\n");
//   printf("?: Intersecar\n");
//   printf("Estos comandos deberan ser de la manera:\n");
//   printf("  'CaracterOperacion [Numero1, Numero2]'\n");
//   printf("dfs, bfs: Mostrar arbol\n");
//   printf("salir: Finalizar programa\n\n");
  while (strcmp(leer_cadena(buffer), "salir\0")) { // si es distinto de salir
    error = 0;
    nombre_primer_conjunto = NULL;
    nombre_segundo_conjunto = NULL;
    nombre_tercer_conjunto = NULL;
    if (buffer[0] == 'i' && buffer[1] == 'm' && buffer[2] == 'p'
      && buffer[3] == 'r' && buffer[4] == 'i' && buffer[5] == 'm'
      && buffer[6] == 'i' && buffer[7] == 'r' && buffer[8] == ' ')
      imprimir(tabla, buffer + 9); // si el comando es imprimir ejecuta esta funcion
    else {
      for(i = 0;i<MAX_NOMBRE_CONJUNTO && buffer[i] != '=' && buffer[i] != '\0'; ++i){
        aux[i] = buffer[i]; // lee el nombre del conjunto resultado
      }
      if (buffer[i] == '=' && i > 0) {
        if(aux[i-1] == ' ')
          aux[i-1] = '\0';
        else
          aux[i] = '\0';
        if (check_alphanumeric(aux)) {
          nombre_primer_conjunto = malloc(sizeof(char)*(strlen(aux)+1));
          strcpy(nombre_primer_conjunto, aux);
        } else
          error = 1;
      } else
        error = 1;

      if (!error) {
        ++i;
        if (buffer[i]==' ')
          ++i;
        if (buffer[i]=='{') { // si es una creacion de conjunto
          ++i;
          if(isalpha(buffer[i]) && buffer[i] != '-'){
            error = inserta_conjunto_comprension(tabla, buffer+i, nombre_primer_conjunto);
          } else if (isdigit(buffer[i]) || buffer[i] == '-') {
            error = inserta_conjunto_extension(tabla, buffer+i, nombre_primer_conjunto);
          } else
                error = 1;
        } else if (buffer[i]=='~') { // si es un complemento
          bufferAux = buffer + (i+1);
          operacion = buffer[i];
          for(i = 0;i<MAX_NOMBRE_CONJUNTO && *bufferAux != '\0' && !error; ++bufferAux) {
            aux[i] = *bufferAux; // lee el conjunto a operar
            ++i;
          }
          if (*bufferAux == '\0' && i > 0 && !error) {
            if(aux[i-1] == ' ')
              aux[i-1] = '\0';
            else
              aux[i] = '\0';
            if (check_alphanumeric(aux)) {
              nombre_segundo_conjunto = malloc(sizeof(char)*(strlen(aux)+1));
              strcpy(nombre_segundo_conjunto, aux);
            } else
              error = 1;
          } else
            error = 1;
          if (!error)
            realizar_operacion(tabla, operacion, nombre_primer_conjunto, nombre_segundo_conjunto, nombre_tercer_conjunto);
        } else if (!isalnum(buffer[i]))
          error = 1;
        else {
          bufferAux = buffer + i;
          for(i = 0;i<MAX_NOMBRE_CONJUNTO && *bufferAux != '-' && *bufferAux != '&' && *bufferAux != '|' && *bufferAux != '\0' && !error; ++bufferAux) {
            aux[i] = *bufferAux; // lee el primer conjunto a operar
            ++i;
          }

          if ((*bufferAux == '-' || *bufferAux == '&' || *bufferAux == '|') && i > 0 && !error) {
            operacion = *bufferAux;
            if(aux[i-1] == ' ')
              aux[i-1] = '\0';
            else
              aux[i] = '\0';
            if (check_alphanumeric(aux)) {
              nombre_segundo_conjunto = malloc(sizeof(char)*(strlen(aux)+1));
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
              aux[i] = *bufferAux; // lee el segundo conjunto a operar
              ++i;
            }
            if (*bufferAux == '\0' && i > 0 && !error) {
              if(aux[i-1] == ' ')
                aux[i-1] = '\0';
              else
                aux[i] = '\0';
              if (check_alphanumeric(aux)) {
                nombre_tercer_conjunto = malloc(sizeof(char)*(strlen(aux)+1));
                strcpy(nombre_tercer_conjunto, aux);
              } else
                error = 1;
            } else
              error = 1;
            if (!error)
              realizar_operacion(tabla, operacion, nombre_primer_conjunto, nombre_segundo_conjunto, nombre_tercer_conjunto);
          }
        }
      }
    }
    if (nombre_segundo_conjunto)
      free(nombre_segundo_conjunto); // libera la memoria de los nombres de los conjuntos a operar
    if (nombre_tercer_conjunto)
      free(nombre_tercer_conjunto); // libera la memoria de los nombres de los conjuntos a operar
    if (error) {
      printf("Entrada incorrecta\n");
      free(nombre_primer_conjunto);
    }
  }
  tabla_destruir(tabla, conjunto_destroy_conjunto); // destruye la tabla
  return 0;
}
