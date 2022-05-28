#include <stdio.h>
#include <stdlib.h>
#include "io.h"

/**
 * Esta es la parte del programa que se encarga de leer y guardar un archivo en
 * un arreglo de caracteres. También guarda la cantidad de caracteres en un 
 * puntero a entero. La idea es guardar el nombre de un archivo de texto (notese
 * que en este caso es "prueba.txt") en un puntero a un arreglo de caracteres
 * que luego se pasará a la función readfile.
 **/

/**
 * Ahora este archivo también crea un arreglo de enteros con el "peso" de cada
 * caracter. Más detalles en la función peso_arreglo_caracteres.
 */

/**
 * arreglo_con_peso es solamente un arreglo de 256 enteros, el número de
 * caracteres ASCII que existen.
 * nota: verificar si esta función debería estar dentro del main
 */

int * arreglo_con_peso() {
  int * arreglo = malloc(sizeof(int)*256);
  for (int i = 0; i < 256; i++) {
    arreglo[i] = 0;
  }
  return arreglo;
}

/**
 * peso_arreglo_caracteres lee todo el arreglo de carcateres que contiene el
 * texto y guarda cuantas apariciones hay de cada uno en un arreglo de enteros
 * donde cada indice de este arreglo es un caracter ASCII.
 */

int * peso_arreglo_caracteres(int *arreglo, char *buff, int len) {
  char c;
  for (int i = 0; i < len; i++) {
    c = buff[i];
    arreglo[(unsigned)c] += 1;
  }
  return arreglo;
}

int main() {
  const char* path = "prueba.txt";
  int len; 
  char* buff;

  int *arreglo = arreglo_con_peso();

  buff = readfile(path, &len);

  peso_arreglo_caracteres(arreglo, buff, len);

  printf("buff = %s\n", buff);
  //~ detalle, este arreglo de caracteres parece imprimir basura al final
  printf("largo = %d\n", len);
  printf("peso 'e' = %d\n", arreglo[101]);

  free(arreglo);

  return 0;
}
