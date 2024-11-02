FLAGS = -Wall

main: parametrizacion.o lectura.o nodo.o hough.o elipse.o lab1.c
	gcc $(FLAGS) -o lab1 lab1.c parametrizacion.o lectura.o nodo.o hough.o elipse.o -lcfitsio
hough.o: hough.c
	gcc $(FLAGS) -c hough.c
parametrizacion.o: parametrizacion.c
	gcc $(FLAGS) -c parametrizacion.c -lm 
lectura.o: lectura.c
	gcc $(FLAGS) -c lectura.c -lcfitsio
nodo.o: nodo.c elipse.o
	gcc $(FLAGS) -c nodo.c elipse.o
elipse.o: elipse.c
	gcc $(FLAGS) -c elipse.c
clean:
	rm -f *.o lab1
