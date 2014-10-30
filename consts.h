/* Grupo 55
 * 
 * Cristiano Rocha nº62502
 * Pedro Saraiva nº70848
 * Francisco Dias nº75328
 * 
 * Exercício 3
 * */

#define TOTAL_WRITES 5120
#define TOTAL_LINES 1024
#define N_STRINGS 10
#define STR_LENGTH 10
#define N_FILES 5
#define N_CHILDREN 10
#define get_random(max) rand()%max

const char *str[N_STRINGS];

const char *fileName[N_FILES];
