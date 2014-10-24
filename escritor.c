/* Grupo 55
 * 
 * Cristiano Rocha nº62502
 * Pedro Saraiva nº70848
 * Francisco Dias nº75328
 * 
 * Exercício 1
 * */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <sys/time.h>
#include <time.h>
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

  char *execparms[1];

  pid_t *childPids = NULL;
  pid_t p;
  
  char *execname; /* variável para guardar o caminho para o executável */
  execname = malloc(sizeof(char)*PATH_MAX);
  char buf[PATH_MAX + 1]; /* buffer para obtermos o cwd */
  execname = getcwd(buf, PATH_MAX +1);
  execname = strcat(execname, "/escritor-helper");
  execparms[0] = execname;
  double time_spent;

  struct timeval tvstart; /* data de inicio */
  struct timeval tvend; /* data de fim */
  struct timeval tvduration; /* diferenca entre as duas datas */
  unsigned int duration; /* diferenca entre as datas em microssegundos */

  time_t curtime; /* tempo em formato time_t para conversao de formatos */
  char buffer[30]; /* para escrever a data em formato legivel */
  
  int ii;
  int stillWaiting;

  childPids = malloc(N_CHILDREN * sizeof(pid_t));
  
  gettimeofday(&tvstart, NULL); /* ler a data actual */
  /* converter e imprimir a data */
  curtime=tvstart.tv_sec;
  strftime(buffer,30,"%m-%d-%Y  %T.",localtime(&curtime));
  printf("inicio: %s%ld\n",buffer,tvstart.tv_usec);
  for (ii = 0; ii < N_CHILDREN; ++ii) {
    if ((p = fork()) == 0) {
	execv(execparms[0], execparms);
    }
    else {
      childPids[ii] = p;
    }
  }
  /* Wait for children to exit */
  
  do {
    stillWaiting = 0;
    for (ii = 0; ii < N_CHILDREN; ++ii) {
	if (childPids[ii] > 0) {
        if (waitpid(childPids[ii], NULL, WNOHANG) != 0) {
          /* Child acabou */
		printf("%d ended\n", childPids[ii]);
          childPids[ii] = 0;
        }
        else {
          /* Still waiting on this child */
          stillWaiting = 1;
        }
      }
      /* Give up timeslice and prevent hard loop: this may not work on all flavors of Unix */
      sleep(0);
    }
  } while (stillWaiting);
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
