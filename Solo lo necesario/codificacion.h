#ifndef __CODIFICACION_H__
#define __CODIFICACION_H__

#include "listas.h"
#include "io.h"

/**
 * peso_arreglo_caracteres lee todo el arreglo de carcateres que contiene el
 * texto y guarda cuantas apariciones hay de cada uno en un arreglo de enteros
 * donde cada indice de este arreglo es un caracter ASCII.
 */
void peso_arreglo_caracteres(int *arreglo, char *buff, int len);

/**
 * arreglo_con_peso es solamente un arreglo de 256 enteros, el número de
 * caracteres ASCII que existen.
 * nota: verificar si esta función debería estar dentro del main
 */
int * arreglo_con_peso();

/**
 * traducir(char*,int ,char** ,int)-> char*
 * Recorre el archivo original y guarda en un nuevo texto
 * el codigo asignado por el arbol de huffman a cada caracter
 * donde:
 * texto es el archivo a comprimir. len es la longitud de dicho archivo
 * codigos es una lista de strings conteniendo el codigo de cada caracter ordenada segun el caracter que representan
 * long_bits es la cantidad de '1' y '0' que va a tener el texto traducido
 */
char *traducir(char* texto,int len,char** codigos,int long_bits);

/**
 * unir_arb_let(char*,char*) -> char*
 * combina el array que contiene la estructura del arbol
 * con el array que contiene el orden de aparicion de cada caracter
 * para asi poderlo escribir en el .tree 
 */
char* unir_arb_let(char* arbol,int alen,char* ord,int llen);

/**
 * longitud_Archivo_final(int*,char **) -> int
 * Calcula mediante la aparicion de cada caracter (el peso)
 * y la longitud de su codigo correspondiente
 * el tamaño final que tendra nuestra traduccion antes del implode
 */
int longitud_Archivo_final(int* pesos,char **codigos,int len);

/**
 * decodificar(char* ,int ,BSTree ,int*) -> char*
 * utilizando la cadena de bits (bits) como guia, recorre el arbol
 * hasta encontrar una hoja, procediendo a escribir en un array el caracter
 * que se encuentra en dicha hoja, volviendo al inicio del arbol 
 * esto se repite hasta que no haya mas bits
 * retornando el array escrito y guardando en un *int su longitud.
 * Dicho array es nuestro archivo original
 */
char *decodificar(char* bits,int blen, BSTree arbol,int* tlen);

#endif