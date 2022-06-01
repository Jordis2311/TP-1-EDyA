#include "arboles.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/**
 * Devuelve un arbol vacío.
 */
BSTree bstee_crear() { return NULL; }

/**
 * 
 */
int es_hoja(BSTree arbol)
{
  if (arbol->izq == NULL) {
    assert(arbol->der == NULL);
    return 1;
  } else {
    return 0;
  }
}

/**
 * 
 */
void recorrer_arbol_huffman(BSTree arbol){
  if(arbol != NULL){
    if(es_hoja(arbol)){
      printf("%i ",arbol->letra);
    }
    else{
      recorrer_arbol_huffman(arbol->izq);
      recorrer_arbol_huffman(arbol->der);
    }
  }
}


void codigos_arbol(BSTree arbol, char buffer[], int altura, char **codigos,
                   char* est_arb, int *pos_est, char *orden_letras,
                   int* pos_let){
  if(arbol != NULL){
    if(es_hoja(arbol)){
      est_arb[*pos_est] = '1';
      *pos_est = *pos_est + 1;
      orden_letras[*pos_let] = (unsigned char) (arbol->letra);
      *pos_let = *pos_let + 1;

      buffer[altura] = '\0';
      codigos[arbol->letra] = malloc(sizeof(char)*(strlen(buffer) + 1));
      strcpy(codigos[arbol->letra],buffer);
      //printf("Hoja %i, %s\n",arbol->letra,codigos[arbol->letra]);
      //puts("");
    }
    else{
      est_arb[*pos_est] = '0';
      *pos_est = *pos_est + 1;
      int siguiente = altura + 1;
      buffer[altura] = '0';
      //printf("Rama Izquierda\n");
      codigos_arbol(arbol->izq, buffer, siguiente, codigos, est_arb, pos_est,
                    orden_letras, pos_let);
      buffer[altura]= '1';
      //printf("Rama Derecha\n");
      codigos_arbol(arbol->der, buffer, siguiente, codigos, est_arb, pos_est,
                    orden_letras, pos_let);
    }
  }
}

BSTree texto_a_arbol(char *arbol_txt,int *pos_arb,int*pos_let){
  if(arbol_txt[*pos_arb] == '1'){
    struct _BST_Nodo *hoja = malloc(sizeof(struct _BST_Nodo));
    hoja->izq = NULL;
    hoja->der = NULL;

    hoja->letra = (unsigned char) arbol_txt[*pos_let];
    *pos_arb = *pos_arb + 1;
    *pos_let = *pos_let + 1;
    return hoja;
  }
  else if(arbol_txt[*pos_arb] == '0'){
    struct _BST_Nodo *rama = malloc(sizeof(struct _BST_Nodo));
    *pos_arb = *pos_arb + 1;
    rama->izq = texto_a_arbol(arbol_txt,pos_arb,pos_let);
    rama->der = texto_a_arbol(arbol_txt,pos_arb,pos_let);

    return rama;
  }
  else return NULL;
}

/**
 * Libera la memoria pedida por un árbol.
 */
void liberar_arbol(BSTree arbol){
  if(arbol != NULL){
    liberar_arbol(arbol->izq);
    liberar_arbol(arbol->der);
    free(arbol);
  }
}
