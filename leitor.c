#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include "consts.h"

int main(int argc, char *argv[]) {

  fileName[0] = "SO2014-0.txt";
  fileName[1] = "SO2014-1.txt";
  fileName[2] = "SO2014-2.txt";
  fileName[3] = "SO2014-3.txt";
  fileName[4] = "SO2014-4.txt";

  int i, timesRead;
  
  char buffer[STR_LENGTH];
  char firstLine[STR_LENGTH];
  size_t nbytes;
  
  timesRead = 0;
  
  nbytes = sizeof(buffer);
 
  int fileIndex = rand() % N_FILES;
  
  int file = open(fileName[fileIndex], O_RDONLY, 0644);
  
  if(file == -1)
  {
	  return -1;
  }
  
  read(file, buffer, nbytes); /* ler a primeira linha para comparação */
  strcpy(firstLine, buffer);
  
  for(i=0; i<TOTAL_LINES; i++) {
	  read(file, buffer, nbytes);
	  if(strcmp(firstLine, buffer) == 0)
	  {
		  timesRead++;
	  }
  }
  
  close(file);
  
  if(timesRead == TOTAL_LINES)
  {
	  puts("0");
	return 0;
  }
  else{
	 puts("-1");
	return -1;
  }

}
