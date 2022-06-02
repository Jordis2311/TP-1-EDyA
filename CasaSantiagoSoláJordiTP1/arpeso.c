#include "arpeso.h"
#include <stdio.h>
#include <stdlib.h>

#include "arboles.h"

/**
 * dato_a_AP(int, int) -> Arpeso 
 */
ArPeso dato_a_AP(int indice, int peso){
  ArPeso arP;
  struct _BST_Nodo *hoja = malloc(sizeof(struct _BST_Nodo));
  hoja->letra = indice;
  hoja->izq = hoja->der = NULL;

  arP.arbol = hoja;
  arP.peso = peso;

  return arP;
}

/**
 * comparar_pesos(ArPeso a,ArPeso b) -> int
 */
int comparar_pesos(ArPeso a, ArPeso b) {
  if (a.peso > b.peso) return 1;
  else return -1;
}

/**
 * combinar_ap(ArPeso,ArPeso) -> ArPeso
 */
ArPeso combinar_AP(ArPeso a, ArPeso b) {
  ArPeso combinado;
  struct _BST_Nodo *hoja = malloc(sizeof(struct _BST_Nodo));
  hoja->der = b.arbol;
  hoja->izq = a.arbol;
  combinado.arbol = hoja;
  combinado.peso = a.peso + b.peso;

  return combinado;
}
