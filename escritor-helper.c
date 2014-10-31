/* Grupo 55
 * 
 * Cristiano Rocha nº62502
 * Pedro Saraiva nº70848
 * Francisco Dias nº75328
 * 
 * Exercício 3
 * */

#include <stdio.h>
#include <fcntl.h>
#include <sys/file.h>
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

  int i, j;
  for(i=0; i<(TOTAL_WRITES/N_CHILDREN); i++) {
    int fileIndex = rand() % N_FILES; /*escolhemos o ficheiro aleatoriamente */
    int strIndex = rand() % N_STRINGS; /*escolhemos a cadeia aleatoriamente */

    int file = open(fileName[fileIndex], O_CREAT | O_RDWR, 0644); /* abrimos o ficheiro ou criamos caso este não exista. caso o ficheiro exista o seu conteúdo é substituído*/
	flock(file, LOCK_EX);
	
	printf("Lock acquired by process %d\n", getpid());

    for(j=0; j<TOTAL_LINES; j++) {
      write(file, str[strIndex], STR_LENGTH); /*escrevemos a cadeia de caracteres escolhida aleatoriamente 1024 vezes */
    }
    
    sleep(1);
    flock(file, LOCK_UN);
    printf("Lock released by process %d\n", getpid());

    close(file);
  }
  return 0;
}
