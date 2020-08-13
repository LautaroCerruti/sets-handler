#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_LINEA 1000

/*
    leer_cadena: char* -> char*
    Toma lo escrito por el teclado, y lo retorna reemplazando el salto de linea
    por un '\0'.
*/
char *leer_cadena(char *string) {
  char c, *aux = string;
  // Mientras que el caracter leido sea distinto a '\n'
  while ((c = getchar()) != '\n') {
    if (c != '\r') {            // Si el caracter leido es distinto a '\r'
      *string = c;              // Almacenamos el caracter en string
      ++string;                 // Movemos la posicion a la que apunta string
    }
  }
  *string = '\0';               // Colocamos un terminador al final
  return aux;                   // Devolvemos un puntero al comienzo de string
}

// char obtener_operacion(char *string, Intervalo ** intervalo) {
//   char operacion = string[0], *resto;
//   double numero1, numero2;
//   if (strlen(string) >= 8 && string[1] == ' ' && string[2] == '[') {
//     string += 3;
//     if (isdigit(*string) != 0 || *string == '-') {
//       numero1 = strtod(string, &resto);
//     }
//     if (*resto == ',' && *(resto + 1) == ' '
//         && (isdigit(*(resto + 2)) || *(resto + 2) == '-')) {
//       string = resto + 2; 
//       numero2 = strtod(string, &resto);
//     }
//     if (*resto == ']' && *(resto + 1) == '\0') {
//       *intervalo = intervalo_crear(numero1, numero2);
//       return operacion;
//     }
//   }
//   return '\0';
// }



int main() {
   char buffer[MAX_LINEA];
   buffer[0] = '\0';
//   ITree arbol = itree_crear(), nodo;
//   Intervalo *intervalo;

//   printf("i: Insertar\n");
//   printf("e: Eliminar\n");
//   printf("?: Intersecar\n");
//   printf("Estos comandos deberan ser de la manera:\n");
//   printf("  'CaracterOperacion [Numero1, Numero2]'\n");
//   printf("dfs, bfs: Mostrar arbol\n");
//   printf("salir: Finalizar programa\n\n");

//   while (strcmp(leer_cadena(buffer), "salir\0")) {
//     if (!strcmp(buffer, "dfs\0")) {
//       itree_recorrer_dfs(arbol, intervalo_imprimir);
//       printf("\n");
//     } else if (!strcmp(buffer, "bfs\0")) {
//       itree_recorrer_bfs(arbol, intervalo_imprimir);
//       printf("\n");
//     } else {
//       switch (obtener_operacion(buffer, &intervalo)) {
//       case 'i':
//         arbol = itree_insertar(arbol, intervalo);
//         break;
//       case 'e':
//         arbol = itree_eliminar(arbol, intervalo);
//         intervalo_destruir(intervalo);
//         break;
//       case '?':
//         nodo = itree_intersecar(arbol, intervalo);
//         if (nodo) {
//           printf("  Si,");
//           itree_aplicar_a_intervalo(nodo, intervalo_imprimir);
//         } else
//           printf("  No");
//         printf("\n");
//         intervalo_destruir(intervalo);
//         nodo = NULL;
//         break;
//       case '\0':
//         printf("  Comando Incorrecto\n");
//         break;
//       default:
//         intervalo_destruir(intervalo);
//         printf("  Comando Incorrecto\n");
//         break;
//       }
//     }
//   }
//   itree_destruir(arbol, intervalo_destruir);
  return 0;
}
