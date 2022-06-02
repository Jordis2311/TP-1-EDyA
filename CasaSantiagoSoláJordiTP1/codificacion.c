#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "arboles.h"
#include "arpeso.h"
#include "listas.h"

/**
 * peso_arreglo_caracteres(int*, char*, int)
 */

void peso_arreglo_caracteres(int *arreglo, char *buff, int len) {
  char c;
  for (int i = 0; i < len; i++) {
    c = buff[i];
    arreglo[(unsigned char) c] += 1;
  }
}

/**
 * arreglo_con_peso() -> int*
 */
int *arreglo_con_peso() {
  int *arreglo = malloc(sizeof(int) * 256);
  for (int i = 0; i < 256; i++) {
    arreglo[i] = 0;
  }
  return arreglo;
}

/**
 * traducir(char*, int, char**, int) -> char*
 */
char *traducir(char *texto, int len, char **codigos, int long_bits){
  char* traduccion = malloc(sizeof(char) * (long_bits + 1));
  int posicion = 0, digitos = 0;

  for (int i = 0; i<len; i++) {
    unsigned char c = texto[i];
    while (codigos[c][digitos] != '\0') {
      traduccion[posicion] = codigos[c][digitos];
      posicion++;
      digitos++;
    }
    digitos = 0;
  }
  traduccion[posicion] = '\0';
  return traduccion;
}

/**
 * unir_arb_let(char*, char*) -> char*
 */
char* unir_arb_let(char *arbol, int alen, char *ord, int llen) {
  char* unido = malloc(sizeof(char) * (alen+llen + 1));
  int i, b;
  for (i = 0; i < alen; i++) unido[i] = arbol[i];
  for (b = 0; b < llen; b++) unido[i+b] = ord[b];
  return unido;
}

/**
 * longitud_Archivo_final(int*, char **) -> int
 */
int longitud_archivo_final(int *pesos, char **codigos, int len){
  int longitud = 0;
  for (int i = 0; i < len; i++) {
    longitud = longitud + pesos[i] * (strlen(codigos[i]));
  }
  return longitud;
}

/**
 * decodificar(char*, int, BSTree, int*) -> char*
 */
char *decodificar(char *bits, int blen, BSTree arbol, int *tlen){
  *tlen = 0;
  char* original = malloc(sizeof(char) * blen);
  BSTree temp = arbol;
  for (int i = 0; i < blen; i++) {
    if (bits[i] == '0')
      temp = temp->izq;
    else
      temp = temp->der;
    
    if (es_hoja(temp)) {
      original[*tlen] = (char) temp->letra;
      temp = arbol;
      *tlen = *tlen + 1;
    }
  }
  return original;
}
