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

typedef struct {
  int offset;
  int linesToRead;
} offset_table;

/* declarações globais.
   variáveis que vão ser acedidas por todas as threads */

offset_table *offsetTable;        /*tabela com N_THREADS posições e que contem em casa posição o offset e o número de linhas a ler */
char *file;                       /*nome do ficheiro a ser aberto */
char stringToCompare[STR_LENGTH]; /*primeira string do ficheiro a ser comparado */

void initOffsetTable(int size)
{
  int i, offset;
  offset = size / N_THREADS;

  for(i = 0; i < N_THREADS-1; i++)
    {
      offsetTable[i].offset = i * (offset - (offset % STR_LENGTH));
      offsetTable[i].linesToRead = TOTAL_LINES / N_THREADS;
    }
    offsetTable[i].offset = i * (offset - (offset % STR_LENGTH));
    offsetTable[i].linesToRead = TOTAL_LINES - ((N_THREADS-1) * (int)(TOTAL_LINES / N_THREADS)); /* no caso da última thread que vai verificar a parte final do ficheiro pode ter de ler mais linhas do que as outras */
}

int* threadedFunction(void *arguments)
{
  int fd,j;
  long i = (long) arguments;

  fd = open (file, O_RDONLY);

  if (fd == -1) {
    perror ("Error opening file");
    return (void*)-1;
  }
  else {
    if(lseek(fd, (off_t) offsetTable[i].offset, SEEK_SET) == -1)
      {
        perror("Error moving the file pointer");
        exit(-1);
      }
    char string_to_read[STR_LENGTH];
    for (j = 0; j < offsetTable[i].linesToRead; j++ ){

      if (read (fd, string_to_read, STR_LENGTH) == -1) {
        perror ("Error reading file");
        return (void*)-1;
      }
      if (strncmp(string_to_read, stringToCompare, STR_LENGTH)) {
        fprintf (stderr, "Section %ld of the file %s is inconsistent\n",i, file);
        return (void*)-1;
      }

    }

    if (close (fd) == -1)  {
      perror ("Error closing file");
      return (void*)-1;
    }
  }

  printf("Section %ld of the file %s is consistent\n", i, file); /* pode ficar ou nao */
  return (void*)0;

}


/*-------------------------------------------------------------------------------------
| main
+-------------------------------------------------------------------------------------*/

int main (int argc, char** argv) {

  pthread_t * serverThreads;
  serverThreads = (pthread_t *) malloc (sizeof (pthread_t) * N_THREADS);
  offsetTable = (offset_table *) malloc(sizeof (offset_table) * N_THREADS);
  int err, fd, size, random;
  long i;
  void *returnvalue;

  srandom ((unsigned) time(NULL));

  random = get_random(N_FILES);

  file = myfiles[random]; /* para testar alterar para myfiles[0] e alterar ficheiro SO2014-0.txt */

  fd = open (file, O_RDONLY);

  if (read (fd, stringToCompare, STR_LENGTH) == -1) {
    perror ("Error reading file");
    exit (-1);
  }

  if((size = lseek(fd, (off_t) 0, SEEK_END)) ==-1 )
    {
      perror("Error while getting the file size");
      exit(-1);
    }

  initOffsetTable(size);

  if (close (fd) == -1)  {
    perror ("Error closing file");
    exit (-1);
  }
  
  for (i = 0; i < N_THREADS; i++) {
    err = pthread_create (&serverThreads[i], NULL, (void*) threadedFunction, (void*)i);
    if (err != 0) {
      perror ("\nerror: thread creation failed\n");
      exit (EXIT_FAILURE);
    }
  }

  for (i = 0; i < N_THREADS; i++) {
    err = pthread_join (serverThreads[i], &returnvalue);
    if (err != 0) {
      perror ("\nerror: thread creation failed\n");
      exit (EXIT_FAILURE);
    }
    if((long int)returnvalue != 0)
      {
        perror("File is inconsistent");
        exit(-1);
      }
  }

  printf("File %s is consistent\n", file);


  return 0;
}
