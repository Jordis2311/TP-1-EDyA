#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "io.h"
#include "arboles.h"
#include "arpeso.h"
#include "listas.h"

/**
 * peso_arreglo_caracteres lee todo el arreglo de carcateres que contiene el
 * texto y guarda cuantas apariciones hay de cada uno en un arreglo de enteros
 * donde cada indice de este arreglo es un caracter ASCII.
 */

int * peso_arreglo_caracteres(int *arreglo, char *buff, int len) {
  char c;
  for (int i = 0; i < len; i++) {
    c = buff[i];
    arreglo[(unsigned char)c] += 1;
  }
  return arreglo;
}

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

int main(){
  const char* path = "prueba 2.txt";
  int len;
  char* buff = readfile(path,&len);

  int *pesos = arreglo_con_peso();
  peso_arreglo_caracteres(pesos, buff, len);

  SList lista_arb = array_a_lista(pesos);

  test_hojas_en_lista(lista_arb);

  BSTree arbol_huffman = combinar_lista(lista_arb);
  recorrer_arbol_huffman(arbol_huffman);

  char buffer_codigos[30];
  char **codigos = malloc(sizeof(char*)*256);

  char *estructura_arbol =malloc(sizeof(char)*512);
  char *orden_letras = malloc(sizeof(char)*257);
  int pos_est = 0,pos_letra = 0;

  codigos_arbol(arbol_huffman,buffer_codigos,0,codigos,estructura_arbol,&pos_est,orden_letras,&pos_letra);

  estructura_arbol[pos_est] = '\0';

  orden_letras[pos_letra] = '\0';

  char *tree = unir_arb_let(estructura_arbol,orden_letras);

  int longitud = longitud_Archivo_final(pesos,codigos);

  char *traduccion = traducir(buff,len,codigos,longitud);

  int hlen;
  char *huffman = implode(traduccion,strlen(traduccion),&hlen);

  writefile("prueba.txt.hf",huffman,hlen);
  writefile("prueba.txt.tree",tree,767);

  free(tree);
  free(huffman);
  free(traduccion);
  for(int i=0;i<256;i++) free(codigos[i]);
  free(codigos);
  free(orden_letras);
  free(estructura_arbol);
  liberar_arbol(arbol_huffman);
  free(pesos);
  free(buff);

  printf("Termino\n");
  return 0;
}
