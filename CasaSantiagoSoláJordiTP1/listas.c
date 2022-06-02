#include "listas.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
 * slist_crear() -> SList
 */
SList slist_crear() { return NULL; }

/**
 * insert_sort(SList, ArPeso) -> SList
 */
SList insert_sort(SList lista, ArPeso dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  if (lista == NULL)
    return nuevoNodo;

  if (comparar_pesos(lista->dato,dato) == 1) {
    nuevoNodo->sig = lista;
    return nuevoNodo;
  } else {
    SList nodo = lista;
    for (; nodo->sig != NULL; nodo = nodo->sig) {
      if (comparar_pesos(nodo->sig->dato, dato) == 1) {
        nuevoNodo->sig = nodo->sig;
        nodo->sig = nuevoNodo;
        return lista;
      }
    }
    nodo->sig = nuevoNodo;
    return lista;
  }
}

/**
 * array_a_lista(int*) -> SList
 */
SList array_a_lista(int *array) {
  SList lista = slist_crear();

  for (int i = 0; i < 256; i++) {
    ArPeso dato = dato_a_AP(i,array[i]);
    lista = insert_sort(lista,dato);
  }
  return lista;
}

/**
 * slist_recorrer(SList)
 */
void slist_recorrer(SList lista) {
  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig){
    printf("%i ", nodo->dato.peso);
    recorrer_arbol_huffman(nodo->dato.arbol);
    printf(" -> ");
  }
  puts("");
}

/**
 * combinar_lista(SList) -> BSTree
 */
BSTree combinar_lista(SList lista) {
  SNodo *eliminador;
  while (lista->sig != NULL) {
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
 * test_hojas_en_lista(SList)
 */
void test_hojas_en_lista(SList lista) {
  SList temp = lista;
  for (; temp != NULL; temp = temp->sig) {
    assert(es_hoja(temp->dato.arbol) == 1);
  }
}
