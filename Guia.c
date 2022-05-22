#include <stdio.h>
#include <stdlib.h>

/*
1 - Abrir el archivo en readfile y se guarda en un char* y aparte guarda su longitud en un int*
2 - Recorrer el texto guardado todas las apariciones de cada caracter en un array de ints donde sus indices son el ascii de las letras (0-255)
(Usar Unsigned referido en la anotacion ultima pagina del pdf)

3- Volver cada letra un Nodo de un ABB en donde y guardarlos en un struct del tipo

Hojas{
    BTree Arbol
    int peso, indice
}
En donde peso es cada aparicion de la letra

4 - Guardar todas las Hojas en una Lista enlazada

5 - Recorrer la lista agarrando los arboles de minimo peso y uniendolos, sumando los pesos y uniendolos arboles, volviendolos a insertar a la lista hasta que solo quede 1 Arbol