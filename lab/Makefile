FLAGS = -Wall

main: parametrizacion.o lectura.o lab1.c
	gcc $(FLAGS) -o lab1 lab1.c parametrizacion.o lectura.o -lcfitsio
parametrizacion.o: parametrizacion.c
	gcc $(FLAGS) -c parametrizacion.c -lm 
lectura.o: lectura.c
	gcc $(FLAGS) -c lectura.c
clean:
	rm -f *.o lab1
