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

  pid_t *childPids = NULL;
  pid_t p;
  

  char *cwd;
  char buf[PATH_MAX + 1];
  cwd = getcwd(buf, PATH_MAX +1);
  char *execname;
  execname = malloc(sizeof(char)*PATH_MAX);
  strcpy(execname, cwd);
  execname = strcat(execname, "/escritor-helper");
  clock_t start, finish;
  double time_spent;
  
  

int ii;

  childPids = malloc(N_CHILDREN * sizeof(pid_t));
  
  start = clock();
  for (ii = 0; ii < N_CHILDREN; ++ii) {
    if ((p = fork()) == 0) {
	execv(execname, NULL);
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
  finish = clock();
  time_spent = (double) (finish-start) / CLOCKS_PER_SEC;
  printf("Tempo de execução: %f\n", time_spent);
  /* Cleanup */
  free(childPids);

  return 0;
}
