#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "io.h"
#include "arboles.h"
#include "arpeso.h"
#include "listas.h"
#include "codificacion.h"

int main( int argc, char **argv){
  assert(argc > 1);
  assert((strcmp(argv[1],"C") == 0) || (strcmp(argv[1],"D") == 0));

  if(strcmp(argv[1],"C") == 0){
    assert(argc == 3);

    int len;
    char* buff = readfile(argv[2],&len);

    int *pesos = arreglo_con_peso();
    peso_arreglo_caracteres(pesos, buff, len);

    SList lista_arb = array_a_lista(pesos);

    test_hojas_en_lista(lista_arb);

    BSTree arbol_huffman = combinar_lista(lista_arb);

    char buffer_codigos[30];
    char **codigos = malloc(sizeof(char*)*256);

    char *estructura_arbol =malloc(sizeof(char)*512);
    char *orden_letras = malloc(sizeof(char)*257);
    int pos_est = 0,pos_letra = 0;

    codigos_arbol(arbol_huffman,buffer_codigos,0,codigos,estructura_arbol,&pos_est,orden_letras,&pos_letra);

    estructura_arbol[pos_est] = '\0';

    orden_letras[pos_letra] = '\0';

    char *tree = unir_arb_let(estructura_arbol,511,orden_letras,256);

    int longitud_bits = longitud_Archivo_final(pesos,codigos,256);

    char *traduccion = traducir(buff,len,codigos,longitud_bits);

    int hlen;
    char *huffman = implode(traduccion,longitud_bits,&hlen);

    char* n_h = strcat(argv[2],".hf");
    writefile(n_h,huffman,hlen);
    argv[2][strlen(argv[2])-3] = '\0';

    char* n_t = strcat(argv[2],".tree");
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
    char *arbol_txt = readfile(argv[3],&alen);

    BSTree arbol = texto_a_arbol(arbol_txt,&pos_arb,&pos_let);

    char *txt_cod = readfile(argv[2],&hlen);
    
    char *txt_bits = explode(txt_cod,hlen,&blen);

    int tlen;
    char* texto_original = decodificar(txt_bits,blen,arbol,&tlen);

    argv[2][strlen(argv[2])-3] = '\0';
    char* nombre_final = strcat(argv[2],".dec");
    
    writefile(nombre_final,texto_original,tlen);

    liberar_arbol(arbol);
    free(texto_original);
    free(txt_bits);
    free(txt_cod);
    free(arbol_txt);
  }

  return 0;
}