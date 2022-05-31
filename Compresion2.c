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
    //unsigned char cc = c;
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

char* concatenar(char *cad1,char *cad2){
  int len1 = strlen(cad1), len2 = strlen(cad2), i,b;
  char *conc = malloc(sizeof(char)*(len1 + len2 + 2));
  for(i = 0; i<len1;i++){
    conc[i] = cad1[i];
  }
  for(b = 0;b<len2;b++){
    conc[i+b] = cad2[b];
  }
  conc[i+b] = '\0';
  return conc;
}

char *traducir(char* texto,int len,char** codigos_arbol){
  char* traduccion = malloc(1);
  *traduccion = 0;

  for(int i = 0;i<len;i++){
    unsigned char c = texto[i];
    char* anterior = traduccion;
    traduccion = concatenar(traduccion,codigos_arbol[c]);
    free(anterior);
  }
  return traduccion;
}


char* unir_arb_let(char* arbol,char* ord){
  char* unido = malloc(sizeof(char)*(767));
  int i,b;
  for(i = 0;i<511;i++) unido[i] = arbol[i];
  for(b=0;b<256;b++) unido[i+b] = ord[b];
  return unido;
}

int main(){
  const char* path = "prueba.txt";
  int len;
  char* buff = readfile(path,&len);

  int *pesos = arreglo_con_peso();
  peso_arreglo_caracteres(pesos, buff, len);

  SList lista_arb = array_a_lista(pesos);

  //slist_recorrer(lista_arb);
  test_hojas_en_lista(lista_arb);
  //puts("");

  BSTree arbol_huffman = combinar_lista(lista_arb);
  //recorrer_arbol_huffman(arbol_huffman);
  //puts("\n");

  char buffer_codigos[30];
  char **codigos = malloc(sizeof(char*)*256);

  char *estructura_arbol =malloc(sizeof(char)*512);
  char *orden_letras = malloc(sizeof(char)*257);
  int pos_est = 0,pos_letra = 0;

  codigos_arbol(arbol_huffman,buffer_codigos,0,codigos,estructura_arbol,&pos_est,orden_letras,&pos_letra);

  //for(int i=0;i<256;i++) printf("%c: %s / ",(unsigned char) i,codigos[i]);
  puts("");

  estructura_arbol[pos_est] = '\0';
  //printf("Estructura Arbol \n%s\n",estructura_arbol);
  puts("");
  orden_letras[pos_letra] = '\0';
  //printf("Orden Letras \n%s\n",orden_letras);

  char *tree = unir_arb_let(estructura_arbol,orden_letras);

  char *traduccion = traducir(buff,len,codigos);

  //printf("Traduccion\n%s\n",traduccion);

  int hlen;
  char *huffman = implode(traduccion,strlen(traduccion),&hlen);
  //printf("Traduccion Final\n%s\n",huffman);

  writefile("hf.txt",huffman,hlen);
  writefile("tree.txt",tree,767);

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
