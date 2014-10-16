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

  pid_t *childPids = NULL;
  pid_t p;

int ii;

  childPids = malloc(N_CHILDREN * sizeof(pid_t));

  for (ii = 0; ii < N_CHILDREN; ++ii) {
    if ((p = fork()) == 0) {
 
      int i, j;
      for(i=0; i<TOTAL_WRITES/N_CHILDREN; i++) {
        int fileIndex = rand() % N_FILES; /*escolhemos o ficheiro aleatoriamente */
        int strIndex = rand() % N_STRINGS; /*escolhemos a cadeia aleatoriamente */

        int file = open(fileName[fileIndex], O_CREAT | O_WRONLY | O_TRUNC, 0644); /* abrimos o ficheiro ou criamos caso este não exista. caso o ficheiro exista o seu conteúdo é substituído*/

        for(j=0; j<TOTAL_LINES; j++) {
          write(file, str[strIndex], STR_LENGTH); /*escrevemos a cadeia de caracteres escolhida aleatoriamente 1024 vezes */
        }

        close(file);
      }

      exit(0);
    }
    else {
      childPids[ii] = p;
    }
  }

  /* Wait for children to exit */
  int stillWaiting;
  do {
    stillWaiting = 0;
    for (ii = 0; ii < N_CHILDREN; ++ii) {
      if (childPids[ii] > 0) {
        if (waitpid(childPids[ii], NULL, WNOHANG) != 0) {
          /* Child acabou */
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

  /* Cleanup */
  free(childPids);

  return 0;
}
