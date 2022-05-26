#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _BST_Nodo {
  int dato;
  struct _BST_Nodo *izq, *der;
};

typedef struct _BST_Nodo *BSTree;

typedef struct _ArPeso{
  BSTree arbol;
  int peso;
}ArPeso;

typedef struct _SNodo {
  ArPeso dato;
  struct _SNodo *sig;
}SNodo;

typedef SNodo *SList;

SList slist_crear() { return NULL; }

BSTree bstee_crear() { return NULL; }

ArPeso dato_a_AP(int indice, int peso){
  ArPeso arP;
  struct _BST_Nodo *hoja = malloc(sizeof(struct _BST_Nodo));
  hoja->dato = indice;
  hoja->izq = hoja->der = NULL;

  arP.arbol = hoja;
  arP.peso = peso;

  return arP;
}

int comparar_pesos(ArPeso a,ArPeso b){
  if(a.peso > b.peso) return 1;
  else return -1;
}

SList slist_agregar_ordenado(SList lista, ArPeso dato) {
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

void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar);
  }
}

SList array_a_lista(int* array){
  SList lista = slist_crear();
  
  for(int i=0;i<10;i++){ //la lista tiene una longitud predeterminada pues cada indice representa un caracter (0-255) y lo que contiene ese indice es el peso de dicho caracter
    //Solo 10 para testeo
    ArPeso dato = dato_a_AP(i,array[i]);
    lista = slist_agregar_ordenado(lista,dato);
  }
  return lista;
}

void slist_recorrer(SList lista) {
  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig){
    printf("%i %i -> ",nodo->dato.peso,nodo->dato.arbol->dato);
  }
}

ArPeso combinar_AP(ArPeso a, ArPeso b){
  ArPeso combinado;
  struct _BST_Nodo *hoja = malloc(sizeof(struct _BST_Nodo));
  hoja->der = b.arbol;
  hoja->izq = a.arbol;
  combinado.arbol = hoja;
  combinado.peso = a.peso + b.peso;

  return combinado;
}

BSTree combinar_lista(SList lista){
  SNodo *eliminador;
  while(lista->sig != NULL){
    ArPeso combinacion = combinar_AP(lista->sig->dato,lista->dato);
    eliminador = lista;
    lista = lista->sig;
    free(eliminador);
    eliminador = lista;
    lista = lista->sig;
    free(eliminador);
    lista = slist_agregar_ordenado(lista,combinacion); 
  }
  return lista->dato.arbol;
}

void recorrer_arbol_huffman(BSTree arbol){
  if(arbol != NULL){
    if(arbol->izq == NULL && arbol->der == NULL){
      printf("%i ",arbol->dato);
    }
    else{
      recorrer_arbol_huffman(arbol->izq);
      recorrer_arbol_huffman(arbol->der);
    }
  }
}

int main(){

  int *pesos = malloc(sizeof(int)*10);
  pesos[0] = 7;
  pesos[1] = 3;
  pesos[2] = 2;
  pesos[3] = 4;
  pesos[4] = 1;
  pesos[5] = 5;
  pesos[6] = 7;
  pesos[7] = 8;
  pesos[8] = 3;
  pesos[9] = 10;
  
  SList lista_arb = array_a_lista(pesos);

  slist_recorrer(lista_arb);
  puts("");

  BSTree arbol_huffman = combinar_lista(lista_arb);
  recorrer_arbol_huffman(arbol_huffman);
  puts("");
  return 0;
}
