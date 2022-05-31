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

/**
 * combinar_lista(SList) -> BSTree
 * Toma la lista enlazada de ArPeso y combina todos los Arboles y Pesos de las 
 * estructuras segun su Peso y los vuelve a insertar en la lista.
 * Cuando solo queda un elemento en dicha lista se retorna el arbol de huffman.
 */
BSTree combinar_lista(SList lista){
  SNodo *eliminador;
  while(lista->sig != NULL){
    //Combina los ArPeso colocando el arbol del ArPeso con mayor peso a la 
    //izquierda
    ArPeso combinacion = combinar_AP(lista->sig->dato,lista->dato);  
    //Al estar la lista ordenada de menor a mayor, nodo->sig tendra un peso 
    //mayor o igual
    eliminador = lista;
    lista = lista->sig;
    free(eliminador); //Eliminamos los 2 nodos utilizados
    eliminador = lista;
    lista = lista->sig;
    free(eliminador);
    lista = insert_sort(lista,combinacion);
  }
  BSTree arbol_final = lista->dato.arbol;
  free(lista);
  return arbol_final;
}

/**
 * codigos_arbol(BSTree,Char[],Int,Char**)
 * Recorre el arbol hasta llegar a sus hojas guardando en buffer el camino que 
 * se toma para cada hoja en un formato string, utilizando altura para ver en 
 * que posicion tiene que modificar a este buffer.
 * Ademas mientras recorre el arbol, guarda la estructura de este en un char* 
 * utilizando un puntero a int para ver en que posicion tiene que estar y guarda
 * en otro char* el orden de aparicion de los caracteres.
 */
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
