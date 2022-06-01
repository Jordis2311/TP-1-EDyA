#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "io.h"
#include "arboles.h"
#include "arpeso.h"
#include "listas.h"
#include "codificacion.h"

/**
 * Alumnos: Santiago Casa, Jordi Solá
 * Estructura de Datos y Algoritmos 1
 * Trabajo Practico 1
 * Compresion de Huffman
 */

int main( int argc, char **argv){
  assert(argc > 1);
  assert((strcmp(argv[1],"C") == 0) || (strcmp(argv[1],"D") == 0));

  if(strcmp(argv[1],"C") == 0){
    assert(argc == 3);

    int len;
    // Leemos el archivo y lo guardamos junto con su longitud
    // char* buff: contenido del archivo a comprimir
    // int len: longitud del archivo
    char* buff = readfile(argv[2],&len);

    // Creamos la lista que contiene a las apariciones de cada caracter
    // int *pesos: array que contiene las repeticiones de los caracteres
    int *pesos = arreglo_con_peso();
    peso_arreglo_caracteres(pesos, buff, len);

    // SList lista_arb: lista enlazada cuyos datos son del tipo ArPeso
    // Estos ArPeso contienen a los caracteres y su peso
    // Esta lista queda ordenada utilizando insert_sort 
    SList lista_arb = array_a_lista(pesos);

    // verificamos que se hayan creado bien la lista y los nodos
    test_hojas_en_lista(lista_arb);

    // Creamos el arbol de huffman combinando los arboles de
    // los Datos de cada lista, liberando el espacio ocupado por esta
    BSTree arbol_huffman = combinar_lista(lista_arb);

    // char** codigos: array de strings que contendran los codigos de
    // cada caracter ordenados segun el ASCII de dicho caracter
    char buffer_codigos[30];
    char **codigos = malloc(sizeof(char*)*256);

    // char* estructura_arbol: array de 1 y 0 que representa
    // como es el arbol (1 = hoja,0 = rama)
    char *estructura_arbol =malloc(sizeof(char)*512);
    // char* orden_letras: array que contiene a las caracteres segun
    // aparecen en el arbol recorriendolo inorder
    char *orden_letras = malloc(sizeof(char)*257);
    int pos_est = 0,pos_letra = 0;

    // Definimos los codigos de cada caracter utilizando el arbol
    // de Huffman guardandolos en codigos
    // tambien guarda la estructura del arbol en estructura_arbol
    // y los caracteres en el orden que aparecen
    codigos_arbol(arbol_huffman,buffer_codigos,0,codigos
                  ,estructura_arbol,&pos_est,orden_letras,&pos_letra);

    estructura_arbol[pos_est] = '\0';

    orden_letras[pos_letra] = '\0';

    // char* tree: es el texto que contendra el archivo .tree
    // la concatenacion de estructura_arbol y orden_letras
    char *tree = unir_arb_let(estructura_arbol,511,orden_letras,256);

    // int longitud_bits: es la longitud que tendra la cadena de bits
    // que representa al texto original antes del implode
    int longitud_bits = longitud_Archivo_final(pesos,codigos,256);

    // char* traduccion: es el archivo original cuyos caracteres fueron
    // cambiados por sus codigos correspondientes
    char *traduccion = traducir(buff,len,codigos,longitud_bits);

    int hlen;
    // char* huffman: es el texto que ira dentro del archivo .hf
    // es decir la traduccion luego de convertirse en caracteres
    char *huffman = implode(traduccion,longitud_bits,&hlen);

    // char* n_h y n_t fueron creados para modificar el nombre
    // del archivo original (agregandole .hf y .tree)
    char* n_h = strcat(argv[2],".hf");

    // Escribimos en "nombre_archivo.hf" la compresion realizada
    writefile(n_h,huffman,hlen);
    argv[2][strlen(argv[2])-3] = '\0';

    char* n_t = strcat(argv[2],".tree");
    // Escribimos en "nombre_archivo.tree" la estructura del arbol de Huffman
    // que utilizamos para comprimirlo
    writefile(n_t,tree,767);

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
  } 
  else{
    assert(argc == 4);

    int alen,hlen,blen;
    int pos_arb = 0, pos_let = 511;
    // char* arbol_txt: es la codificacion en texto del arbol
    // que utilizamos para comprimir el archivo
    char *arbol_txt = readfile(argv[3],&alen);

    // BSTree arbol: es el arbol de huffman que se utilizo 
    // para comprimir el texto
    BSTree arbol = texto_a_arbol(arbol_txt,&pos_arb,&pos_let);

    // char* txt_cod: es el texto implosionado de la traduccion
    // a bits del archivo original
    char *txt_cod = readfile(argv[2],&hlen);
    
    // char* txt_bits: es el binario del archivo comprimido
    char *txt_bits = explode(txt_cod,hlen,&blen);

    int tlen;
    // char* texto_original: es (valga la redundancia) el texto
    // del archivo original
    char* texto_original = decodificar(txt_bits,blen,arbol,&tlen);

    argv[2][strlen(argv[2])-3] = '\0';
    char* nombre_final = strcat(argv[2],".dec");
    
    // escribimos devuelta el archivo descomprimido en "nombre_archivo.dec"
    writefile(nombre_final,texto_original,tlen);

    liberar_arbol(arbol);
    free(texto_original);
    free(txt_bits);
    free(txt_cod);
    free(arbol_txt);
  }

  return 0;
}