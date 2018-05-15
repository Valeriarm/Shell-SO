/*
Integrantes: 
Valeria Rivera - 1626837
Cristian Perafan - 1625690
Walter Santacruz -

Fecha: 8 Mayo 2018
*/


#include <stdio.h>                                                                                                                              
#include <unistd.h>                                                                
#include <string.h>                                                                
#include <sys/wait.h>
#include "funciones.h"


int main(int argc, char const *argv[]){
	int pid;
	char comando[90];

   while (1){  

	printf("Ingrese el comando: ");
	scanf(" %99[^\n]",comando);

	if (!strcmp("exit",comando)){
	   break;
	}

	pid = fork();

	if (!pid){
		ejecutarComando(comando);
	}else{
	    wait(NULL);
	    }
    }

   return 0;
}
