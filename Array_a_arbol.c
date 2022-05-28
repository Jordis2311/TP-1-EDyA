#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct _BST_Nodo {
  int letra;
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
  hoja->letra = indice;
  hoja->izq = hoja->der = NULL;

  arP.arbol = hoja;
  arP.peso = peso;

  return arP;
}

int comparar_pesos(ArPeso a,ArPeso b){
  if(a.peso > b.peso) return 1;
  else return -1;
}


//insert_sort(SList,ArPeso) -> SList
//Inserta de manera ordenada en la lista el dato ArPeso segun su peso
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

void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar);
  }
}

//array_a_lista(int*) -> SList
//Toma la lista de ints que representan los pesos de cada caracter
//y los insterta utilizando insertsort de menor a mayor en una lista simple de ArPeso
//en donde el indice es el caracter y lo que esta dentro del array en su posicion es el peso del caracter (cuantas veces aparece)
//Cada ArPeso contiene un arbol que se inicializa en 1 hoja conteniendo a el caracter (es decir el indice) y tambien contiene dicho pero
SList array_a_lista(int* array){
  SList lista = slist_crear();
  
  for(int i=0;i<10;i++){ //la lista tiene una longitud predeterminada pues cada indice representa un caracter (0-255) y lo que contiene ese indice es el peso de dicho caracter
    //Solo 10 para testeo
    ArPeso dato = dato_a_AP(i,array[i]);
    lista = insert_sort(lista,dato);
  }
  return lista;
}

int es_hoja(BSTree arbol)
{
  if (arbol->izq == NULL) {
    assert(arbol->der == NULL);
    return 1;
  } else {
    return 0;
  }
}

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

void slist_recorrer(SList lista) {
  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig){
    printf("%i ",nodo->dato.peso);
    recorrer_arbol_huffman(nodo->dato.arbol);
    printf(" -> ");
  }
  puts("");
}

//combinar_ap(ArPeso,ArPeso) -> ArPeso
//Toma los 2 Arboles de las estructuras y crea un nuevo arbol que tiene de hijo izq al primero y de hijo derecho al segundo
//Este arbol lo guarda en un nuevo ArPeso donde su peso es la suma de los 2 pesos de los arboles anteriores
ArPeso combinar_AP(ArPeso a, ArPeso b){
  ArPeso combinado;
  struct _BST_Nodo *hoja = malloc(sizeof(struct _BST_Nodo));
  hoja->der = b.arbol;
  hoja->izq = a.arbol;
  combinado.arbol = hoja;
  combinado.peso = a.peso + b.peso;

  return combinado;
}

//combinar_lista(SList) -> BSTree
//Toma la lista enlazada de ArPeso y combina todos los Arboles y Pesos de las estructuras segun su Peso y los vuelve a insertar en la lista
//Cuando solo queda un elemento en dicha lista se retorna el arbol de huffman
BSTree combinar_lista(SList lista){
  SNodo *eliminador;
  while(lista->sig != NULL){
    //Combina los ArPeso colocando el arbol del ArPeso con mayor peso a la izquierda
    ArPeso combinacion = combinar_AP(lista->sig->dato,lista->dato);  //Al estar la lista ordenada de menor a mayor, nodo->sig tendra un peso mayor o igual
    eliminador = lista;
    lista = lista->sig;
    free(eliminador); //Eliminamos los 2 nodos utilizados
    eliminador = lista;
    lista = lista->sig;
    free(eliminador);
    lista = insert_sort(lista,combinacion);
  }
  return lista->dato.arbol;
}

//codigos_arbol(BSTree,Char[],Int,Char**)
//Recorre el arbol hasta llegar a sus hojas guardando en buffer el camino que se toma para cada hoja en un formato string, utilizando altura para ver en que posicion
//tiene que modificar a este buffer
void codigos_arbol(BSTree arbol,char buffer[20],int altura,char **codigos){
  if(arbol != NULL){
    if(es_hoja(arbol)){
      buffer[altura] = '\0';
      codigos[arbol->letra] = malloc(sizeof(char)*(strlen(buffer) + 1));
      strcpy(codigos[arbol->letra],buffer);
      printf("Hoja %i, %s\n",arbol->letra,codigos[arbol->letra]);
      puts("");
    }
    else{
      int siguiente = altura + 1;
      buffer[altura] = '0';
      printf("Rama Izquierda\n");
      buffer[siguiente] = '\0';
      codigos_arbol(arbol->izq,buffer,siguiente,codigos);
      buffer[altura]= '1';
      printf("Rama Derecha\n");
      codigos_arbol(arbol->der,buffer,siguiente,codigos);
    }
  }
}

//Verifica que se creo bien la lista desde el array
void test_hojas_en_lista(SList lista){
  SList temp = lista;
  for(;temp!=NULL;temp = temp->sig){
    assert(es_hoja(temp->dato.arbol) == 1);
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
  test_hojas_en_lista(lista_arb);
  puts("");

  BSTree arbol_huffman = combinar_lista(lista_arb);
  recorrer_arbol_huffman(arbol_huffman);
  puts("\n");
  
  char buffer[20];
  char **codigos = malloc(sizeof(char*)*10);
  codigos_arbol(arbol_huffman,buffer,0,codigos);

  for(int i=0;i<10;i++) printf("%i: %s / ",i,codigos[i]);
  puts("");

  return 0;
}
