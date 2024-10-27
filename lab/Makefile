FLAGS = -Wall

main: parametrizacion.o lectura.o nodo.o hough.o lab1.c
	gcc $(FLAGS) -o lab1 lab1.c parametrizacion.o lectura.o nodo.o hough.o -lcfitsio
parametrizacion.o: parametrizacion.c
	gcc $(FLAGS) -c parametrizacion.c -lm 
lectura.o: lectura.c
	gcc $(FLAGS) -c lectura.c -lcfitsio
nodo.o: nodo.c
	gcc $(FLAGS) -c nodo.c
hough.o: hough.c
	gcc $(FLAGS) -c hough.c
clean:
	rm -f *.o lab1
