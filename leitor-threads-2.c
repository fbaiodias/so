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
#include <pthread.h>

#include "consts.h"

/*-------------------------------------------------------------------------------------
| fixed strings
+-------------------------------------------------------------------------------------*/

char* myfiles[N_FILES] = { "SO2014-0.txt",
          "SO2014-1.txt",
          "SO2014-2.txt",
          "SO2014-3.txt",
          "SO2014-4.txt"};

int* threadedFunction(char *file)
{

  int fd;

  fd = open (file, O_RDONLY);

  if (fd == -1) {
    perror ("Error opening file");
    return (void*)-1;
  }
  else {
    char string_to_read[STR_LENGTH];
    char first_string[STR_LENGTH];
    int  i;

    if (read (fd, first_string, STR_LENGTH) == -1) {
      perror ("Error reading file");
      return (void*)-1;
    }
    for (i=0; i<TOTAL_LINES-1; i++) {

      if (read (fd, string_to_read, STR_LENGTH) == -1) {
        perror ("Error reading file");
        return (void*)-1;
      }

      if (strncmp(string_to_read, first_string, STR_LENGTH)) {
        fprintf (stderr, "File %s is inconsistent\n", file);
        return (void*)-1;
      }
    }

    if (close (fd) == -1)  {
      perror ("Error closing file");
      return (void*)-1;
    }
  }

  printf("File %s is consistent\n", file);
  return (void*)0;

}


/*-------------------------------------------------------------------------------------
| main
+-------------------------------------------------------------------------------------*/

int main (int argc, char** argv) {

  pthread_t * serverThreads;
  serverThreads = (pthread_t *) malloc (sizeof (pthread_t) * N_THREADS);
  int i, err;
  char *file;
  void *returnvalue;

  srandom ((unsigned) time(NULL));

  for (i = 0; i < N_THREADS; i++) {
    file = myfiles[get_random(N_FILES)];
    err = pthread_create (&serverThreads[i], NULL, (void*) threadedFunction, (void*)file);
    if (err != 0) {
      perror ("\nerror: thread creation failed\n");
      exit (EXIT_FAILURE);
    }
    printf("Checking file %s\n", file);
  }

  for (i = 0; i < N_THREADS; i++) {
    err = pthread_join (serverThreads[i], &returnvalue);
    printf("Thread %d returned %ld\n", i, (long int)returnvalue);
    if (err != 0) {
      perror ("\nerror: thread creation failed\n");
      exit (EXIT_FAILURE);
    }
  }

  return 0;
}
