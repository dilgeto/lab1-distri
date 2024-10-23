FLAGS = -Wall


main: parametrizacion.o lab1.c
	gcc $(FLAGS) -o lab1 lab1.c parametrizacion.o -lcfitsio
parametrizacion.o: parametrizacion.c
	gcc $(FLAGS) -c parametrizacion.c 
clean:
	rm -f *.o lab1
