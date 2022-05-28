#include <stdio.h>
#include <stdlib.h>

/*
1 - Abrir el archivo en readfile y se guarda en un char* y aparte guarda su longitud en un int*
2 - Recorrer el texto guardado todas las apariciones de cada caracter en un array de ints donde sus indices son el ascii de las letras (0-255)
(Usar Unsigned referido en la anotacion ultima pagina del pdf)

3- Volver cada letra un Nodo de un ABB en donde y guardarlos en un struct del tipo

Btree{
    int indice;
    Btree izq,der;
}

Hojas{
    BTree Arbol
    int peso
}
En donde peso es cada aparicion de la letra

4 - Guardar todas las Hojas en una Lista enlazada

5 - Recorrer la lista agarrando los arboles de minimo peso y uniendolos, sumando los pesos y uniendolos arboles, volviendolos a insertar a la lista hasta que solo quede 1 Arbol

6 - Recorrer el arbol y guardar el recorrido hasta llegar a cada hoja guardando en un array de strings (char**) utilizando la letra que esta en la hoja como indice, el recorrido

7 - Recorrer y guardar en un texto la estructura del arbol (1 es rama 0 es hoja) para asi ponerlo en un archivo de texto

8 - Recorrer el texto original y cada caracter traducirlo al codigo correspondiente para asi y colocarlo este texto traducido en otro array char*

9 - Utilizar implode para el texto codificado y guardarlo en un archivo con writefile (llamado f.txt.hf siendo f el nombre del archivo original)

10 - guardar la estructura del arbol y las posiciones de las hojas en otro archivo (llamado f.txt.tree)

