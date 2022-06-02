#ifndef __LISTAS_H__
#define __LISTAS_H__

#include "arpeso.h"

typedef struct _SNodo {
  ArPeso dato;
  struct _SNodo *sig;
} SNodo;

typedef SNodo *SList;

/**
 * slist_crear() -> SList
 * Devuelve una lista vacía.
 */
SList slist_crear();

/**
 * insert_sort(SList, ArPeso) -> SList
 * Inserta de manera ordenada en la lista el dato ArPeso segun su peso.
 */
SList insert_sort(SList lista, ArPeso dato);

/**
 * array_a_lista(int*) -> SList
 * Toma la lista de ints que representan los pesos de cada caracter y los 
 * inserta utilizando insert_sort de menor a mayor en una lista simple de ArPeso
 * en donde el indice es el caracter y lo que esta dentro del array en su 
 * posicion es el peso del caracter (cuantas veces aparece).
 * Cada ArPeso contiene un arbol que se inicializa en 1 hoja conteniendo a el 
 * caracter (es decir el indice) y tambien contiene dicho peso.
 */
SList array_a_lista(int* array);

/**
 * slist_recorrer(SList)
 * Recorre la lista enlazada de arpeso mostrando, 
 * el peso de sus nodos y los caracteres que contenienen
 */
void slist_recorrer(SList lista);

/**
 * combinar_lista(SList) -> BSTree
 * Toma la lista enlazada de ArPeso y combina todos los Arboles y Pesos de las 
 * estructuras segun su Peso y los vuelve a insertar en la lista.
 * Cuando solo queda un elemento en dicha lista se retorna el arbol de huffman.
 */

BSTree combinar_lista(SList lista);

/**
 * test_hojas_en_lista(SList)
 * Verifica que se creo bien la lista desde el array.
 */
void test_hojas_en_lista(SList lista);

#endif
