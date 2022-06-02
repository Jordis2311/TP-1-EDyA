-----------------------------------------#
Estructura de Datos y Algoritmos	 |
Alumnos: Santiago Casa, Jordi Solá	 |
-----------------------------------------#
---------------------------------------------------------------------------#
Trabajo Practico 1: Codificacion de Huffman				   |
---------------------------------------------------------------------------#								   |
Este programa es un compresor de datos que funciona para cualquier
tipo de archivos sin perdida

El compresor se basa en la codificacion de Huffman, que analiza
la frecuencia de aparicion de los caracteres en el texto de entrada
y optimiza aquellos que son mas frecuentes

---------------------------------------#
Como Ejecutar el programa	       |
---------------------------------------#

Primero deberemos compilar nuestro codigo
Esto se hara con el comando "make" dentro de la consola de linux
este detectara el archivo makefile y compilara el ejecutable con
el nombre "Compresion_Huffman"

Para comprimir un archivo (en este caso dejamos uno a mano llamado "prueba.txt")
deberemos escribir en consola

./Compresion_Huffman C prueba.txt

Este comando creara los archivos comprimidos con los nombres "prueba.txt.hf" y "prueba.txt.tree"

Para descomprimirlos tendremos que ejecutar la siguiente linea

./Compresion_Huffman D prueba.txt.hf prueba.txt.tree

y nos creara el archivo prueba.txt.dec que es el mismo que el original