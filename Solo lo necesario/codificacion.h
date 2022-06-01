#ifndef __CODIFICACION_H__
#define __CODIFICACION_H__

#include "listas.h"
#include "io.h"

/**
 * peso_arreglo_caracteres lee todo el arreglo de carcateres que contiene el
 * texto y guarda cuantas apariciones hay de cada uno en un arreglo de enteros
 * donde cada indice de este arreglo es un caracter ASCII.
 */

int *peso_arreglo_caracteres(int *arreglo, char *buff, int len);

/**
 * arreglo_con_peso es solamente un arreglo de 256 enteros, el número de
 * caracteres ASCII que existen.
 * nota: verificar si esta función debería estar dentro del main
 */
int * arreglo_con_peso();

char *traducir(char* texto,int len,char** codigos,int longitud);

char* unir_arb_let(char* arbol,char* ord);

int longitud_Archivo_final(int* pesos,char **codigos);

char *decodificar(char* bits,int blen, BSTree arbol,int* tlen);

#endif