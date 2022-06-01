#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "arboles.h"
#include "arpeso.h"
#include "listas.h"

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

int *peso_arreglo_caracteres(int *arreglo, char *buff, int len) {
  char c;
  for (int i = 0; i < len; i++) {
    c = buff[i];
    arreglo[(unsigned char)c] += 1;
  }
  return arreglo;
}

char *traducir(char* texto,int len,char** codigos,int longitud){
  char* traduccion = malloc(sizeof(char)*(longitud+1));
  int posicion=0,digitos = 0;

  for(int i = 0;i<len;i++){
    unsigned char c = texto[i];
    while(codigos[c][digitos] != '\0'){
      traduccion[posicion] = codigos[c][digitos];
      posicion++;
      digitos++;
    }
    digitos = 0;
  }
  traduccion[posicion] = '\0';
  return traduccion;
}


char* unir_arb_let(char* arbol,char* ord){
  char* unido = malloc(sizeof(char)*(767));
  int i,b;
  for(i = 0;i<511;i++) unido[i] = arbol[i];
  for(b=0;b<256;b++) unido[i+b] = ord[b];
  return unido;
}

int longitud_Archivo_final(int* pesos,char **codigos){
  int longitud = 0;
  for(int i = 0;i< 256; i++){
    longitud = longitud + pesos[i]*(strlen(codigos[i]));
  }
  return longitud;
}

char *decodificar(char* bits,int blen, BSTree arbol,int* tlen){
  *tlen = 0;
  char* original = malloc(sizeof(char)*100000);
  BSTree temp = arbol;
  for(int i = 0; i< blen; i++){
    if(bits[i] == '0')
      temp = temp->izq;
    else
      temp = temp->der;
    
    if(es_hoja(temp)){
      original[*tlen] = (char) temp->letra;
      temp = arbol;
      *tlen = *tlen +1;
    }
  }
  return original;
}
