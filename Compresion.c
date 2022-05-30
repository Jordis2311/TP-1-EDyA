#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "io.h"

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

//array_a_lista(int*) -> SList
//Toma la lista de ints que representan los pesos de cada caracter
//y los insterta utilizando insertsort de menor a mayor en una lista simple de ArPeso
//en donde el indice es el caracter y lo que esta dentro del array en su posicion es el peso del caracter (cuantas veces aparece)
//Cada ArPeso contiene un arbol que se inicializa en 1 hoja conteniendo a el caracter (es decir el indice) y tambien contiene dicho pero
SList array_a_lista(int* array){
  SList lista = slist_crear();

  for(int i=0;i<256;i++){ //la lista tiene una longitud predeterminada pues cada indice representa un caracter (0-255) y lo que contiene ese indice es el peso de dicho caracter
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
  BSTree arbol_final = lista->dato.arbol;
  free(lista);
  return arbol_final;
}

//codigos_arbol(BSTree,Char[],Int,Char**)
//Recorre el arbol hasta llegar a sus hojas guardando en buffer el camino que se toma para cada hoja en un formato string, utilizando altura para ver en que posicion
//tiene que modificar a este buffer
//Ademas mientras recorre el arbol, guarda la estructura de este en un char* utilizando un puntero a int para ver en que posicion tiene que estar
//Y guarda en otro char* el orden de aparicion de los caracteres
void codigos_arbol(BSTree arbol,char buffer[],int altura,char **codigos,char* est_arb,int *pos_est,char *orden_letras,int*pos_let){
  if(arbol != NULL){
    if(es_hoja(arbol)){
      est_arb[*pos_est] = '0';
      *pos_est = *pos_est + 1;
      orden_letras[*pos_let] = (unsigned char) (arbol->letra);
      *pos_let = *pos_let + 1;

      buffer[altura] = '\0';
      codigos[arbol->letra] = malloc(sizeof(char)*(strlen(buffer) + 1));
      strcpy(codigos[arbol->letra],buffer);
      //printf("Hoja %i, %s\n",arbol->letra,codigos[arbol->letra]);
      //puts("");
    }
    else{
      est_arb[*pos_est] = '1';
      *pos_est = *pos_est + 1;
      int siguiente = altura + 1;
      buffer[altura] = '0';
      //printf("Rama Izquierda\n");
      codigos_arbol(arbol->izq,buffer,siguiente,codigos,est_arb,pos_est,orden_letras,pos_let);
      buffer[altura]= '1';
      //printf("Rama Derecha\n");
      codigos_arbol(arbol->der,buffer,siguiente,codigos,est_arb,pos_est,orden_letras,pos_let);
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

/**
 * peso_arreglo_caracteres lee todo el arreglo de carcateres que contiene el
 * texto y guarda cuantas apariciones hay de cada uno en un arreglo de enteros
 * donde cada indice de este arreglo es un caracter ASCII.
 */

int * peso_arreglo_caracteres(int *arreglo, char *buff, int len) {
  char c;
  for (int i = 0; i < len; i++) {
    c = buff[i];
    //unsigned char cc = c;
    arreglo[(unsigned char)c] += 1;
  }
  return arreglo;
}

/**
 * arreglo_con_peso es solamente un arreglo de 256 enteros, el número de
 * caracteres ASCII que existen.
 * nota: verificar si esta función debería estar dentro del main
 */

int * arreglo_con_peso() {
  int * arreglo = malloc(sizeof(int)*256);
  for (int i = 0; i < 256; i++) {
    arreglo[i] = 0;
  }
  return arreglo;
}

char* concatenar(char *cad1,char *cad2){
  int len1 = strlen(cad1), len2 = strlen(cad2), i,b;
  char *conc = malloc(sizeof(char)*(len1 + len2 + 2));
  for(i = 0; i<len1;i++){
    conc[i] = cad1[i];
  }
  for(b = 0;b<len2;b++){
    conc[i+b] = cad2[b];
  }
  conc[i+b] = '\0';
  return conc;
}

char *traducir(char* texto,int len,char** codigos_arbol){
  char* traduccion = malloc(1);
  *traduccion = 0;

  for(int i = 0;i<len;i++){
    unsigned char c = texto[i];
    char* anterior = traduccion;
    traduccion = concatenar(traduccion,codigos_arbol[c]);
    free(anterior);
  }
  return traduccion;
}

void liberar_arbol(BSTree arbol){
  if(arbol != NULL){
    liberar_arbol(arbol->izq);
    liberar_arbol(arbol->der);
    free(arbol);
  }
}

char* unir_arb_let(char* arbol,char* ord){
  char* unido = malloc(sizeof(char)*(767));
  int i,b;
  for(i = 0;i<511;i++) unido[i] = arbol[i];
  for(b=0;b<256;b++) unido[i+b] = ord[b];
  return unido;
}

int main(){
  const char* path = "prueba.txt";
  int len;
  char* buff = readfile(path,&len);

  int *pesos = arreglo_con_peso();
  peso_arreglo_caracteres(pesos, buff, len);

  SList lista_arb = array_a_lista(pesos);

  //slist_recorrer(lista_arb);
  test_hojas_en_lista(lista_arb);
  //puts("");

  BSTree arbol_huffman = combinar_lista(lista_arb);
  //recorrer_arbol_huffman(arbol_huffman);
  //puts("\n");

  char buffer_codigos[30];
  char **codigos = malloc(sizeof(char*)*256);

  char *estructura_arbol =malloc(sizeof(char)*512);
  char *orden_letras = malloc(sizeof(char)*257);
  int pos_est = 0,pos_letra = 0;

  codigos_arbol(arbol_huffman,buffer_codigos,0,codigos,estructura_arbol,&pos_est,orden_letras,&pos_letra);

  //for(int i=0;i<256;i++) printf("%c: %s / ",(unsigned char) i,codigos[i]);
  puts("");

  estructura_arbol[pos_est] = '\0';
  //printf("Estructura Arbol \n%s\n",estructura_arbol);
  puts("");
  orden_letras[pos_letra] = '\0';
  //printf("Orden Letras \n%s\n",orden_letras);

  char *tree = unir_arb_let(estructura_arbol,orden_letras);

  char *traduccion = traducir(buff,len,codigos);

  //printf("Traduccion\n%s\n",traduccion);

  int hlen;
  char *huffman = implode(traduccion,strlen(traduccion),&hlen);
  //printf("Traduccion Final\n%s\n",huffman);

  writefile("hf.txt",huffman,hlen);
  writefile("tree.txt",tree,767);

  free(tree);
  free(huffman);
  free(traduccion);
  for(int i=0;i<256;i++) free(codigos[i]);
  free(codigos);
  free(orden_letras);
  free(estructura_arbol);
  liberar_arbol(arbol_huffman);
  free(pesos);
  free(buff);

  printf("Termino\n");
  return 0;
}
