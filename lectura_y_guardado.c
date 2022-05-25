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

int main() {
  const char* path = "prueba.txt";
  char* buff;
  int* len;

  buff = readfile(path, len);
  printf("%s\n", buff);
  printf("%d\n", *len);

  return 0;
}
