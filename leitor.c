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


char* myfiles[N_FILES] = { "SO2014-0.txt",
			    "SO2014-1.txt",
			    "SO2014-2.txt",
			    "SO2014-3.txt",
			    "SO2014-4.txt"};


/*-------------------------------------------------------------------------------------
| main
+-------------------------------------------------------------------------------------*/

int main (int argc, char** argv) {
  char  *file_to_open;
  int   fd;
  int   file_to_open_index;

  if (argc > 2)
		{
    	perror("Too many arguments");
			exit(-1);
		}
	file_to_open_index = atoi(argv[1]);

	if(file_to_open_index > 4 || file_to_open_index < 0)
		{
			perror("Index out of bounds");
			exit(-1);
		}


  file_to_open = myfiles[file_to_open_index];
  fd = open (file_to_open, O_RDONLY);


  printf("Lock acquired by process %d\n", getpid());

  printf("Monitor will check if file %s is consistent...\n", file_to_open);

  if (fd == -1) {
    perror ("Error opening file");
    exit (-1);
  }
  else if (flock(fd, LOCK_SH) == -1) {
		perror ("Error getting lock");
		exit (-1);
	}
	 else{
    char string_to_read[STR_LENGTH];
    char first_string[STR_LENGTH];
    int  i;

    if (read (fd, first_string, STR_LENGTH) == -1) {
      perror ("Error reading file");
      exit (-1);
    }
    for (i=0; i<TOTAL_LINES-1; i++) {

      if (read (fd, string_to_read, STR_LENGTH) == -1) {
    		perror ("Error reading file");
    		exit (-1);
      }

      if (strncmp(string_to_read, first_string, STR_LENGTH)) {
    		fprintf (stderr, "Inconsistent file: %s\n", file_to_open);
    		exit (-1);
      }
    }

    if(flock(fd, LOCK_UN) == -1)
			{
				perror("Error releasing lock");
				exit(-1);
			}

    printf("Lock released by process %d\n", getpid());

    if (close (fd) == -1)  {
      perror ("Error closing file");
      exit (-1);
    }
  }

  printf("YES.\n");

  return 0;
}
