Compresion_Huffman: Huff.o codificacion.o listas.o arpeso.o arboles.o io.o
	gcc Huff.o codificacion.o listas.o arpeso.o arboles.o io.o -o Compresion_Huffman

Huff.o: Huff.c codificacion.h listas.h arpeso.h arboles.h io.h
	gcc -c Huff.c

codificacion.o: codificacion.c codificacion.h listas.h arpeso.h arboles.h io.h
	gcc -c codificacion.c

listas.o: listas.c listas.h arpeso.h arboles.h
	gcc -c listas.c

arpeso.o: arpeso.c arpeso.h arboles.h
	gcc -c arpeso.c

arboles.o: arboles.c arboles.h
	gcc -c arboles.c

io.o: io.c io.h
	gcc -c io.c