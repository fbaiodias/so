#include <stdio.h>
#include <fcntl.h>
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
  for(i=0; i<TOTAL_WRITES; i++) {
    int fileIndex = rand() % N_FILES;
    int strIndex = rand() % N_STRINGS;

    /*printf("%d - writing %s on %s\n\n", i+1, str[strIndex], fileName[fileIndex]);*/

    int file = open(fileName[fileIndex], O_CREAT | O_RDWR, 0644);

    for(j=0; j<TOTAL_LINES; j++) {
      write(file, str[strIndex], STR_LENGTH);
    }

    close(file);
  }
  return 0;
}
