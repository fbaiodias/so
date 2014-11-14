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

struct arg_struct {
    char* file;
    int offset;
    int size;
    char stringToCompare[STR_LENGTH];
    int i;
}args;

int sectionsRead[N_THREADS];

void initSectionsRead(){
  int i;

  for(i = 0; i < N_THREADS; i++)
    {
      sectionsRead[i] = 0;
    }
}
int* threadedFunction(void *arguments)
{

  int fd, i, j, section = -1;

  int offset, end;

  struct arg_struct *args = (struct arg_struct *)arguments;

  for(i = 0; i < N_THREADS || section == -1; i++)
  {
    if(sectionsRead[i] == 0)
      {
        printf("section %i is not read\n", i);
        section = i;
      }
  }

  printf("section %i is read\n", section);
  sectionsRead[section] = 1;
  offset = i*args->offset;

  fd = open (args->file, O_RDONLY);

  if (fd == -1) {
    perror ("Error opening file");
    return (void*)-1;
  }
  else {
    lseek(fd, (off_t) offset, SEEK_SET);
    char string_to_read[STR_LENGTH];
    if(i = N_THREADS -1)
      {
        end = TOTAL_LINES - args->offset;
      }
      else
        {
          end = args->offset;
        }

    for (j=0; j < args->offset; j = args->offset / STR_LENGTH) {

      if (read (fd, string_to_read, STR_LENGTH) == -1) {
        perror ("Error reading file");
        return (void*)-1;
      }
      printf("j: %d %d\n", j, args->offset);

      if (strncmp(string_to_read, args->stringToCompare, STR_LENGTH)) {
        printf("read: %s || compare: %s\n", string_to_read, args->stringToCompare);
        fprintf (stderr, "Inconsistent file: %s\n", args->file);
        return (void*)-1;
      }
    }

    if (close (fd) == -1)  {
      perror ("Error closing file");
      return (void*)-1;
    }
  }

  printf("Section %i of the file %s is consistent\n", i, args->file);
  return (void*)0;

}


/*-------------------------------------------------------------------------------------
| main
+-------------------------------------------------------------------------------------*/

int main (int argc, char** argv) {

  pthread_t * serverThreads;
  serverThreads = (pthread_t *) malloc (sizeof (pthread_t) * N_THREADS);
  int i, random, err, status, linesPerThread, fd;
  char *file;
  void *returnvalue;

  struct arg_struct args;

  srandom ((unsigned) time(NULL));
  file = myfiles[get_random(N_FILES)];


  printf("%d\n", args.offset);

  fd = open (file, O_RDONLY);
  char string_to_read[STR_LENGTH];


  args.file = file;
  if (read (fd, args.stringToCompare, STR_LENGTH) == -1) {
    perror ("Error reading file");
    exit (-1);
  }
  args.size = lseek(fd, (off_t) 0, SEEK_END);
  args.offset = args.size/N_THREADS;
  close(fd);
  for (i = 0; i < N_THREADS; i++) {
    err = pthread_create (&serverThreads[i], NULL, (void*) threadedFunction, (void*)&args);
    if (err != 0) {
      perror ("\nerror: thread creation failed\n");
      exit (EXIT_FAILURE);
    }
    printf("Checking file %s\n", file);
  }

  for (i = 0; i < N_THREADS; i++) {
    err = pthread_join (serverThreads[i], &returnvalue);
    if (err != 0) {
      perror ("\nerror: thread creation failed\n");
      exit (EXIT_FAILURE);
    }
  }

  return 0;
}
