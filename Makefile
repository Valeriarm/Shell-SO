
main: libfunciones.a
	gcc -L. -o main main.c -lfunciones
libfunciones.a: funciones.o
	ar -cvq libfunciones.a funciones.o
funciones.o:
	gcc -c funciones.c
clean:
	rm -f main a.out lib*.a *.o 