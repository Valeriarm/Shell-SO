#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

char *args[99];

void llenarArray(char *argsL[], char comandoL[]){
  int k;
    char *var = strtok(comandoL," ") ;
    for (int i =0; var!=NULL; i++){
        argsL[i]=var;
        k=i;
        var= strtok(NULL, " ");
    }
    argsL[k+1]= NULL;
}


void rdpipe(char comando[]){
    
  int p[2];

    char *primeraParte = strtok(comando, "|");
    char *segundaParte = strtok(NULL, "|");    
    char *args1[90];
    char *args2[90];
    char *r = strstr(segundaParte, ">");

    llenarArray(args1, primeraParte);

  if(r!=NULL){
    r = strtok(segundaParte, ">"); 
    r = strtok(NULL, ">"); 
    close(STDOUT_FILENO);
      open(r, O_EXCL|O_CREAT|O_WRONLY, S_IRWXU);
    llenarArray(args2, segundaParte);   
    
  }else{
    llenarArray(args2, segundaParte);
  }




    pipe(p);
  pid_t id = fork();

  if (id==0){
      close(p[0]);
    dup2(p[1], STDOUT_FILENO);
      execvp(args1[0], args1);

  }else{
    wait(NULL);
    dup2(p[0], STDIN_FILENO);
      close(p[1]);
      execvp(args2[0], args2);
  }

  close(p[0]);
  close(p[1]);
}



void comandoSimple(char comando[]){
    char *var = strtok(comando," ") ;
    for (int i =0; var!=NULL; i++){
        args[i]=var;
        var= strtok(NULL, " ");
    }
    execvp(args[0], args);
}


void redireccion(char comando[]){
    char *archivo = strtok(comando, ">");
    archivo = strtok(NULL, ">");
    close(STDOUT_FILENO);
    open(archivo, O_EXCL|O_CREAT|O_WRONLY, S_IRWXU);
    char *var = strtok(comando," ") ;
    for (int i =0; var!=NULL; i++){
        args[i]=var;
        var= strtok(NULL, " ");
    }
    execvp(args[0], args);
}

void ejecutarComando(char comando[]){
  char *aux =strstr(comando, "|");
  char *aux1 =strstr(comando, ">");
  if (aux!=NULL){
    rdpipe(comando);
  }else if(aux1!=NULL){
    redireccion(comando);
  }else{
    comandoSimple(comando);
  }
}