#ifndef __ARBOLES_H__
#define __ARBOLES_H__

/**
 * _BST_Nodo
 * Definimos la estructura que utilizaremos como arbol
 * Un Arbol Binario de ints
 * Cada nodo del arbol tiene:
 * - int letra: representa el ASCII de la letra que guardamos en este nodo
 * - _BST_Nodo *izq, *der: estos seran los 2 hijos del arbol que apuntaran a 
 * otros arboles.
 */
struct _BST_Nodo {
  int letra;
  struct _BST_Nodo *izq, *der;
};

/**
 * BSTree:
 * Un puntero a un _BST_Nodo que utilizaremos para definir nuestros arboles.
 */
typedef struct _BST_Nodo *BSTree;

/**
 * bstee_crear() -> BSTree
 * Devuelve un arbol vacío.
 */
BSTree bstee_crear();

/**
 * es_hoja(BSTree) -> Int
 * Retorna 1 en el caso que el arbol ingresado no tenga hijos
 * y 0 en caso contrario, tambien comprueba que los nodos tienen 2 hijos o 
 * ninguno.
 */
int es_hoja(BSTree arbol);

/**
 * recorrer_arbol_huffman(BSTree)
 * recorre en inorden el arbol dado mostrando los elementos de sus hojas 
 */
void recorrer_arbol_huffman(BSTree arbol);

/**
 * codigos_arbol(BSTree, Char[], Int, Char**, Char*, Int*, Int*, Char*, Int*)
 * Recorre el arbol hasta llegar a sus hojas guardando en buffer el camino que 
 * se toma para cada hoja en un formato string, utilizando altura para ver en 
 * que posicion tiene que modificar a este buffer.
 * Ademas mientras recorre el arbol, guarda la estructura de este en un char* 
 * utilizando un puntero a int para ver en que posicion tiene que estar y guarda
 * en otro char* el orden de aparicion de los caracteres.
 */
void codigos_arbol(BSTree arbol, char buffer[], int altura, char **codigos,
                   char *est_arb, int *pos_est, char *orden_letras,
                   int *pos_let);

/**
 * texto_a_arbol(char, int*, int*) -> BSTree
 * Recorre el texto dado por el archivo .tree para reconstruir el
 * arbol de huffman que se utilizo para codificar el archivo original
 */
BSTree texto_a_arbol(char *arbol_txt, int *pos_arb, int *pos_let);

/**
 * liberar_arbol(BSTree arbol)
 * Recorre y libera la memoria pedida por un árbol.
 */
void liberar_arbol(BSTree arbol);

#endif
