#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "struct.h"
#include "functions.h"


int main() {
  // matriz do jogo
  FILE *manual;
  char texto_manual[800];
  espaco **matriz;
  int *vet_rand;
  manual = fopen("instrucoes.txt", "r");
  while(fgets(texto_manual,1100,manual)!= NULL){
    printf("%s", texto_manual);
  }
  fclose(manual);
  menu(matriz, vet_rand);
  return 0;
}
