main: parametrizacion.o lectura.o nodo.o hough.o elipse.o lab1.c
	gcc -o lab1 lab1.c parametrizacion.o lectura.o nodo.o hough.o elipse.o -lcfitsio -lm -fopenmp
hough.o: hough.c parametrizacion.o
	gcc -c hough.c parametrizacion.o -fopenmp -lm
parametrizacion.o: parametrizacion.c
	gcc -c parametrizacion.c -lm 
lectura.o: lectura.c
	gcc -c lectura.c -lcfitsio -fopenmp
nodo.o: nodo.c elipse.o
	gcc -c nodo.c elipse.o
elipse.o: elipse.c
	gcc -c elipse.c
clean:
	rm -f *.o lab1
