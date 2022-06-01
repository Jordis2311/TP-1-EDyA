#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "arboles.h"
#include "arpeso.h"
#include "listas.h"
#include "codificacion.h"

//----------------------------------------------
//Test de funciones de arboles.h

void test_bstee_crear(){
  assert(bstee_crear()==NULL);
}

void test_es_hoja(){
  struct _BST_Nodo *hoja = malloc(sizeof(struct _BST_Nodo));
  hoja->izq = NULL;
  hoja->der = NULL;
  assert(es_hoja(hoja) == 1);
  struct _BST_Nodo *hoja2 = malloc(sizeof(struct _BST_Nodo));
  struct _BST_Nodo *hoja3 = malloc(sizeof(struct _BST_Nodo));
  hoja2->izq = NULL;
  hoja2->der = NULL;
  hoja3->izq = NULL;
  hoja3->der = NULL;
  hoja->izq = hoja2;
  hoja->der = hoja3;  
  assert(es_hoja(hoja) == 0);
  liberar_arbol(hoja);
}

// void test_codigos_arbol()

// void test_texto_a_arbol()

//----------------------------------------------
//Test de funciones de arpeso.h

void test_dato_a_arpeso(){
  ArPeso ap = dato_a_AP(2,5);
  assert((ap.arbol) != NULL);
  assert((ap.arbol->letra) == 2);
  free(ap.arbol);
}

void test_comparar_pesos(){
  ArPeso a = dato_a_AP(2,5);
  ArPeso b = dato_a_AP(2,6);

  assert(comparar_pesos(a,b) == -1);
  assert(comparar_pesos(b,a) == 1);

  free(a.arbol);
  free(b.arbol);
}

void test_combinar_AP(){
  ArPeso a = dato_a_AP(2,5);
  ArPeso b = dato_a_AP(3,6);

  ArPeso c = combinar_AP(a,b);
  assert(c.peso == 11);
  assert(c.arbol->izq->letra == 2);
  assert(c.arbol->der->letra == 3);
  liberar_arbol(c.arbol);
}

//----------------------------------------------
//Test de funciones de listas.h

void test_lista_crear(){
  assert(lista_crear()==NULL);
}

//void test_array_a_lista()

//void test_combinar_lista()

//void test_insert_sort();

//----------------------------------------------
//Test de funciones de codificacion.h

void test_arreglo_con_peso(){
  int* array = arreglo_con_peso();
  for(int i = 0; i<256;i++) assert(array[i] == 0);
  free(array);
}

void test_peso_arreglo_caracteres(){
  char* texto = "AAAABBBCCCCCDDDEEE";
  int* arr = arreglo_con_peso();
  peso_arreglo_caracteres(arr,texto,18);
  assert(arr[65] == 4);
  assert(arr[66] == 3);
  assert(arr[67] == 5);
  assert(arr[68] == 3);
  assert(arr[69] == 3);
  free(arr);
}

void test_traducir(){
  char  *texto = "AAAABBBCCCCCDDDEEE";
  char **codigos = malloc(sizeof(char*)*70);
  codigos[65] = "101";
  codigos[66] = "111";
  codigos[67] = "010";
  codigos[68] = "001";
  codigos[69] = "000";

  char *trad = traducir(texto,18,codigos,54);
  assert(strcmp("101101101101111111111010010010010010001001001000000000",trad)= 0);

  free(trad);
  free(codigos);
}

void test_unir_arb_let(){
  char  *arbol = "0001001111"; 
  char *letras = "ABCDE";
  char *unido = unir_arb_let(arbol,10,letras,6);
  assert(strcmp(unido,"0001001111ABCDE") == 0);
  free(unido);
}

void test_longitud_archivo_final(){
  int *pesos = malloc(sizeof(int)*5);
  for(int i = 0;i<5;i++) pesos[i] = i+1;
  char **codigos = malloc(sizeof(char*)*5);
  codigos[0] = "101";
  codigos[1] = "111";
  codigos[2] = "010";
  codigos[3] = "001";
  codigos[4] = "000";
  assert(longitud_Archivo_final(pesos,codigos,5) == 45);
  free(codigos);
  free(pesos);
}

// test_decodificar();

//----------------------------------------------

int main(){

  //Test de funciones de arboles.h
  test_bstee_crear();
  test_es_hoja();

  //Test de funciones de arpeso.h
  test_dato_a_arpeso();
  test_comparar_pesos();
  test_combinar_AP();

  //test de funciones de listas.h
  test_lista_crear();

  //Test de funciones de codificacion.h
  test_arreglo_con_peso();
  test_peso_arreglo_caracteres();
  test_traducir();
  test_unir_arb_let();
  test_longitud_archivo_final();
}