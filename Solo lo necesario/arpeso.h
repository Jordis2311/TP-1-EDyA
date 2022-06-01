#ifndef __ARPESO_H__
#define __ARPESO_H__

#include "arboles.h"


/**
 * ArPeso
 * utilizaremos el Struct ArPeso, para repesentar la importancia, el peso
 * que tiene cada hoja y subarbol para construir finalmente el arbol de huffman
 * en donde:
 * BSTree arbol: es un puntero al arbol que contiene
 * int peso: es el peso de dicho arbol, es decir la cantidad de 
 * apariciones en el archivo que tienen los caracteres de las hojas del arbol
 */
typedef struct _ArPeso{
  BSTree arbol;
  int peso;
} ArPeso;

/**dato_a_AP(int ,int) -> Arpeso
 * Toma un int que representa al ASCII de un caracter y 
 * las repeticiones de dicho caracter y devuelve un 
 * ArPeso que apunta a una hoja con ese caracter y 
 * cuyo peso es las repeticiones de dicho caracter
 */
ArPeso dato_a_AP(int indice, int peso);

/**
 * comparar_pesos(ArPeso a,ArPeso b) -> int
 * Retorna 1 si el peso de b es mayor que el de a y -1 en caso contrario 
 */
int comparar_pesos(ArPeso a,ArPeso b);

/**
 * combinar_ap(ArPeso,ArPeso) -> ArPeso
 * Toma los 2 Arboles de las estructuras y crea un nuevo arbol que tiene de hijo
 * izq al primero y de hijo derecho al segundo.
 * Este arbol lo guarda en un nuevo ArPeso donde su peso es la suma de los 2 
 * pesos de los arboles anteriores.
 */
ArPeso combinar_AP(ArPeso a, ArPeso b);

#endif
