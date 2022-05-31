#include "listas.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
 * Devuelve una lista vacía.
 */
SList slist_crear() { return NULL; }

/**
 * insert_sort(SList,ArPeso) -> SList
 * Inserta de manera ordenada en la lista el dato ArPeso segun su peso.
 */
SList insert_sort(SList lista, ArPeso dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  if (lista == NULL)
    return nuevoNodo;

  if (comparar_pesos(lista->dato,dato) == 1){
    nuevoNodo->sig = lista;
    return nuevoNodo;
  }
  else{
    SList nodo = lista;
    for (;nodo->sig != NULL;nodo = nodo->sig){
      if(comparar_pesos(nodo->sig->dato,dato) == 1){
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
 * Toma la lista de ints que representan los pesos de cada caracter y los 
 * inserta utilizando insert_sort de menor a mayor en una lista simple de ArPeso
 * en donde el indice es el caracter y lo que esta dentro del array en su 
 * posicion es el peso del caracter (cuantas veces aparece).
 * Cada ArPeso contiene un arbol que se inicializa en 1 hoja conteniendo a el 
 * caracter (es decir el indice) y tambien contiene dicho peso.
 */
SList array_a_lista(int* array){
  SList lista = slist_crear();

  for(int i=0;i<256;i++){ //la lista tiene una longitud predeterminada pues cada
	// indice representa un caracter (0-255) y lo que contiene ese indice es el 
	// peso de dicho caracter
    // Solo 10 para testeo
    ArPeso dato = dato_a_AP(i,array[i]);
    lista = insert_sort(lista,dato);
  }
  return lista;
}

/**
 * 
 */
void slist_recorrer(SList lista) {
  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig){
    printf("%i ",nodo->dato.peso);
    recorrer_arbol_huffman(nodo->dato.arbol);
    printf(" -> ");
  }
  puts("");
}

/**ass
 * Verifica que se creo bien la lista desde el array.
 */
void test_hojas_en_lista(SList lista){
  SList temp = lista;
  for(;temp!=NULL;temp = temp->sig){
    assert(es_hoja(temp->dato.arbol) == 1);
  }
}
