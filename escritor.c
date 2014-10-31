/* Grupo 55
 * 
 * Cristiano Rocha nº62502
 * Pedro Saraiva nº70848
 * Francisco Dias nº75328
 * 
 * Exercício 3
 * */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <sys/time.h>
#include <time.h>
#include <sys/file.h>
#include "consts.h"

int main(int argc, char *argv[]) {
  str[0] = "aaaaaaaaa\n";
  str[1] = "bbbbbbbbb\n";
  str[2] = "ccccccccc\n";
  str[3] = "ddddddddd\n";
  str[4] = "eeeeeeeee\n";
  str[5] = "fffffffff\n";
  str[6] = "ggggggggg\n";
  str[7] = "hhhhhhhhh\n";
  str[8] = "iiiiiiiii\n";
  str[9] = "jjjjjjjjj\n";

  fileName[0] = "SO2014-0.txt";
  fileName[1] = "SO2014-1.txt";
  fileName[2] = "SO2014-2.txt";
  fileName[3] = "SO2014-3.txt";
  fileName[4] = "SO2014-4.txt";

  char *childExecPath;

  pid_t *childPids = NULL; /* array de pids dos filhos */
  pid_t p;
  
  if (argc >=2)
    childExecPath = argv[1];
  else
    childExecPath = DEFAULT_CHILD_EXEC_PATH;

  struct timeval tvstart; /* data de inicio */
  struct timeval tvend; /* data de fim */
  struct timeval tvduration; /* diferenca entre as duas datas */
  unsigned int duration; /* diferenca entre as datas em microssegundos */

  int status, valorExit;

  time_t curtime; /* tempo em formato time_t para conversao de formatos */
  char buffer[30]; /* para escrever a data em formato legivel */
  
  int i;
  int waitingForChildren;

  childPids = malloc(N_CHILDREN * sizeof(pid_t));
  
  /* ler data actual */

  if (gettimeofday(&tvstart, NULL) == -1) {
    perror("Could not get time of day, exiting.");
    exit(-1);
  }
  /* converter e imprimir a data */
  curtime=tvstart.tv_sec;
  strftime(buffer,30,"%m-%d-%Y  %T.",localtime(&curtime));
  printf("inicio: %s%ld\n",buffer,tvstart.tv_usec);
  
  /* se p == 0 estamos no processo pai por isso criamos um filho. caso contrário estamos no processo filho e guardamos o pid no array de pids */

  for (i = 0; i < N_CHILDREN; ++i) {
    if ((p = fork()) == 0) {
	if(execl(childExecPath,CHILD_ARG0, NULL) == -1){
	perror("Could not execute child program.");
	exit(-1);
	}
    }
    else if(p < -0){
      perror("Could not fork a child.");
      exit(-1);
    }
    else {
      childPids[i] = p;
    }
  }

  /* ciclo "infinito" para esperar que todos os filhos acabem. enquanto um dos filhos não tiver acabado o ciclo continua */
  do {
    waitingForChildren = 0;
    for (i = 0; i < N_CHILDREN; ++i) {
	if (childPids[i] > 0) {
		/* usamos WNOHANG para que o programa não pare à espera que o filho acabe. assim podemos continuar o ciclo e verificar os restantes filhos */
		if (waitpid(childPids[i], &status, WNOHANG) != 0) {
			if (WIFEXITED(status)) {
			  valorExit = (char) WEXITSTATUS(status);
			  printf("Child: %d ended with return value %d\n", childPids[i], valorExit);
			  childPids[i] = 0;
        		}
			else {printf("Child didn't exit or return\n");} 

        }
        else {
          /* continuamos à espera que os filhos acabem */
          waitingForChildren = 1;
        }
      }
    }
  } while (waitingForChildren != 0);

  gettimeofday(&tvend, NULL); /* ler a data actual */
  /* converter e imprimir a data */
  curtime=tvend.tv_sec;
  strftime(buffer,30,"%m-%d-%Y  %T.",localtime(&curtime));
  printf("fim: %s%ld\n",buffer,tvend.tv_usec);

  /* calcular e imprimir a diferenca de datas */
  tvduration.tv_sec = tvend.tv_sec - tvstart.tv_sec;
  tvduration.tv_usec = tvend.tv_usec - tvstart.tv_usec;
  duration = tvduration.tv_sec * 1000000 + tvduration.tv_usec;
  printf("duracao: %d microssegundos\n", duration);
  /* Cleanup */
  free(childPids);


  return 0;
}
