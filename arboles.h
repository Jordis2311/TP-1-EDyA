#ifndef __ARBOLES_H__
#define __ARBOLES_H__

struct _BST_Nodo {
  int letra;
  struct _BST_Nodo *izq, *der;
};

typedef struct _BST_Nodo *BSTree;

/**
 * Devuelve un arbol vacío.
 */
BSTree bstee_crear();

/**
 * 
 */
int es_hoja(BSTree arbol);

/**
 * 
 */
void recorrer_arbol_huffman(BSTree arbol);

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
                   int* pos_let);

/**
 * Libera la memoria pedida por un árbol.
 */
void liberar_arbol(BSTree arbol);

/**
 * 
 */
char* unir_arb_let(char* arbol,char* ord);

#endif
