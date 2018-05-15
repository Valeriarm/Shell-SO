#ifndef __FUNCIONES__
#define __FUNCIONES__

void llenarArray(char *argsL[], char comandoL[]);
int rdpipe(char comando[]);
int comandoSimple(char comando[]);
int redireccion(char comando[]);
void ejecutarComando(char comando[]);
#endif