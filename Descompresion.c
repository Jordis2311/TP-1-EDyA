#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "io.h"
#include "arboles.h"

char *decodificar(char* bits,int blen, BSTree arbol,int* tlen){
  *tlen = 0;
  char* original = malloc(sizeof(char)*100000);
  BSTree temp = arbol;
  for(int i = 0; i< blen; i++){
    if(bits[i] == '0')
      temp = temp->izq;
    else
      temp = temp->der;
    
    if(es_hoja(temp)){
      original[*tlen] = (char) temp->letra;
      temp = arbol;
      *tlen = *tlen +1;
    }
  }
  return original;
}

int main(){
  const char* tree = "prueba.txt.tree";
  const char* hf = "prueba.txt.hf";
  int alen,hlen,blen;
  int pos_arb = 0, pos_let = 511;
  char *arbol_txt = readfile(tree,&alen);

  BSTree arbol = texto_a_arbol(arbol_txt,&pos_arb,&pos_let);

  char *txt_cod = readfile(hf,&hlen);
  
  char *txt_bits = explode(txt_cod,hlen,&blen);

  int tlen;
  char* texto_original = decodificar(txt_bits,blen,arbol,&tlen);

  writefile("f.txt.dec",texto_original,tlen);

  liberar_arbol(arbol);
  free(texto_original);
  free(txt_bits);
  free(txt_cod);
  free(arbol_txt);

  return 0;
}
