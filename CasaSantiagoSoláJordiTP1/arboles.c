#include "arboles.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/**
 * bstee_crear() -> BSTree
 */
BSTree bstee_crear() { return NULL; }

/**
 * es_hoja(BSTree) -> Int
 */
int es_hoja(BSTree arbol) {
  if (arbol->izq == NULL) {
    assert(arbol->der == NULL);
    return 1;
  } else {
    assert(arbol->der != NULL);
    return 0;
  }
}

/**
 * recorrer_arbol_huffman(BSTree)
 */
void recorrer_arbol_huffman(BSTree arbol) {
  if (arbol != NULL) {
    if (es_hoja(arbol)) {
      printf("%i ", arbol->letra);
    } else {
      recorrer_arbol_huffman(arbol->izq);
      recorrer_arbol_huffman(arbol->der);
    }
  }
}

/**
 * codigos_arbol(BSTree, Char[], Int, Char**, Char*, Int*, Int*, Char*, Int*)
 */
void codigos_arbol(BSTree arbol, char buffer[], int altura, char **codigos,
                   char *est_arb, int *pos_est, char *orden_letras,
                   int *pos_let) {
  if (arbol != NULL) {
    if (es_hoja(arbol)) {
      est_arb[*pos_est] = '1'; //En la estructura del arbol de huffman, el 1 
							   //representa una hoja
      *pos_est = *pos_est + 1;
      orden_letras[*pos_let] = (unsigned char) (arbol->letra); //Guarda las 
												   //letras del arbol en inorden
      *pos_let = *pos_let + 1;

      //Guardamos el camino recorrido para llegar a esta letra siendo este su 
      //codigo en binario
      buffer[altura] = '\0';
      codigos[arbol->letra] = malloc(sizeof(char) * (strlen(buffer) + 1));
      strcpy(codigos[arbol->letra], buffer);
    } else {
      est_arb[*pos_est] = '0'; //En la estructura del arbol de huffman, 
							   //el 0 representa una rama
      *pos_est = *pos_est + 1;
      int siguiente = altura + 1;
      buffer[altura] = '0'; //Escribimos en el buffer el camino que recorre 
							//para llegar al siguiente nodo
      codigos_arbol(arbol->izq, buffer, siguiente, codigos, est_arb, pos_est,
                    orden_letras, pos_let);
      buffer[altura] = '1';
      codigos_arbol(arbol->der, buffer, siguiente, codigos, est_arb, pos_est,
                    orden_letras, pos_let);
    }
  }
}

/**
 * texto_a_arbol(char, int*, int*) -> BSTree
 */
BSTree texto_a_arbol(char *arbol_txt,int *pos_arb,int*pos_let) {
  if (arbol_txt[*pos_arb] == '1') {
    struct _BST_Nodo *hoja = malloc(sizeof(struct _BST_Nodo));
    hoja->izq = NULL;
    hoja->der = NULL;

    hoja->letra = (unsigned char) arbol_txt[*pos_let];
    *pos_arb = *pos_arb + 1;
    *pos_let = *pos_let + 1;
    return hoja;
  }
  else if (arbol_txt[*pos_arb] == '0') {
    struct _BST_Nodo *rama = malloc(sizeof(struct _BST_Nodo));
    *pos_arb = *pos_arb + 1;
    rama->izq = texto_a_arbol(arbol_txt, pos_arb, pos_let);
    rama->der = texto_a_arbol(arbol_txt, pos_arb, pos_let);

    return rama;
  }
  else return NULL;
}

/**
 * liberar_arbol(BSTree arbol)
 */
void liberar_arbol(BSTree arbol) {
  if (arbol != NULL) {
    liberar_arbol(arbol->izq);
    liberar_arbol(arbol->der);
    free(arbol);
  }
}
