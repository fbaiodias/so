/* Grupo 55
 * 
 * Cristiano Rocha nº62502
 * Pedro Saraiva nº70848
 * Francisco Dias nº75328
 * 
 * Exercício 2
 * */

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
  
  int fileIndex = rand() % N_FILES;
  
  int file = open(fileName[fileIndex], O_RDONLY, 0644);
  
  timesRead = 0;
  
  nbytes = sizeof(buffer);
  
  /* não conseguimos abrir o ficheiro por isso paramos a execução */
  
  if(file == -1)
  {
	  return -2;
  }
  
  read(file, buffer, nbytes); /* lemos a primeira linha para comparação */
  strcpy(firstLine, buffer); /* guardamos a primeira linha */
  
  for(i=0; i<TOTAL_LINES; i++) {
	  if(strncmp(firstLine, buffer, STR_LENGTH) == 0) /* comparação da primeira linha com cada uma das restantes */
	  {
		  timesRead++;
	  }
	  read(file, buffer, nbytes);
  }
  
  close(file);
  if(timesRead == TOTAL_LINES-1) /* verifica que se existe a mesma cadeia de caracteres repetida 1024 e devolve 0 se true e -1 se false */
  {
	printf("Ficheiros estão correctos\n");
	return 0;
  }
  else{
	printf("Existem ficheiros incorrectos\n");
	return -1;
  }

}
