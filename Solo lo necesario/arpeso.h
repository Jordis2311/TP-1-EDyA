#ifndef __ARPESO_H__
#define __ARPESO_H__

#include "arboles.h"

typedef struct _ArPeso{
  BSTree arbol;
  int peso;
} ArPeso;

/**
 * 
 */
ArPeso dato_a_AP(int indice, int peso);

/**
 * 
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
