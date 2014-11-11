/* Grupo 55
 *
 * Cristiano Rocha nº62502
 * Pedro Saraiva nº70848
 * Francisco Dias nº75328
 *
 * Exercício 4
 * */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/file.h>

#include "consts.h"

/*-------------------------------------------------------------------------------------
| fixed strings
+-------------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------------------
| main
+-------------------------------------------------------------------------------------*/

int main (int argc, char** argv) {
  pid_t *childPids = NULL; /* array de pids dos filhos */
  pid_t *childReturnValues = NULL; /* array de pids dos filhos */
  pid_t p;

  /* Initialize the seed of random number generator */
  srandom ((unsigned) time(NULL));

  int status, valorExit;

  int i;
  int waitingForChildren;

  childPids = malloc(N_READER_CHILDREN * sizeof(pid_t));
  childReturnValues = malloc(N_READER_CHILDREN * sizeof(int));

  for (i = 0; i < N_READER_CHILDREN; ++i) {
    /* se p == 0 estamos no processo pai por isso criamos um filho. */
    if ((p = fork()) == 0) {
      char c[20];
      sprintf(c, "%d", get_random(N_FILES));

      if(execl("leitor", c, NULL) == -1){
        perror("Could not execute child program.");
        exit(-1);
      }
    }
    /* caso contrário estamos no processo filho e guardamos o pid no array de pids */
    else if(p < 0){
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
    for (i = 0; i < N_READER_CHILDREN; ++i) {
      if (childPids[i] > 0) {
        /* usamos WNOHANG para que o programa não pare à espera que o filho acabe. assim podemos continuar o ciclo e verificar os restantes filhos */
        if (waitpid(childPids[i], &status, WNOHANG) != 0) {
          if (WIFEXITED(status)) {
            valorExit = (char) WEXITSTATUS(status);
            printf("Child: %d ended with return value %d\n", childPids[i], valorExit);
            childPids[i] = 0;
            childReturnValues[i] = valorExit;
          }
          else {
            perror("Child didn't exit or return");
          }
        }
        else {
          /* continuamos à espera que os filhos acabem */
          waitingForChildren = 1;
        }
      }
    }
  } while (waitingForChildren != 0);


  printf("\n\nAll done!\n\n");

  for (i = 0; i < N_READER_CHILDREN; ++i) {
    printf("#%d child returned %d\n", i, childReturnValues[i]);
  }


  /* Cleanup */
  free(childPids);
  free(childReturnValues);

  return 0;
}


