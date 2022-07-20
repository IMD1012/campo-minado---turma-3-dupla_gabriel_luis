

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "struct.h"
#include "functions.h"


//Função usada apenas para imprimir a matriz.
void print_matriz_status(espaco **matriz){
  printf("  ");
  for(int i = 0; i<20; i++){
    printf("%3d ", i); 
  }
  printf("\n");

  for(int i = 0; i<10; i++){
    printf("  -------------------------------------------------------------------------------\n");
    printf("%2d|", i);
      for(int j = 0; j<20; j++){
        printf("%2c  ", matriz[i][j].status);
      }
    printf("\n");
    
  }
}


//Função responsavel por formar um vetor sorteado aleatoriamente com 40 posições não repetidas as quais as bombas ficarão posicionadas.
void v_minas(int *v_rand) {
  char ja_consta;
  srand(time(NULL));//lembrar de mudar de volta para 
  for (int i = 0; i < 40; i++) {
    v_rand[i] = rand() % 200;
    ja_consta = 'N';
    for (int j = 0; j < i && ja_consta == 'N'; j++) {
      if (v_rand[i] == v_rand[j])
        ja_consta = 'S';
        
    }
    if (ja_consta == 'S')
      i--;
  }
  
}

//Função responsavel por pegar o vetor criado com as posições das bombas de forma aleatoria e alocalas na matriz.
void cria_campo(int *v_rand, espaco **matriz) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 20; j++) {
      matriz[i][j].tipo = 4;
      matriz[i][j].n_minas = 0;
      matriz[i][j].status = '*';
      matriz[i][j].aberto = 0;
    }
  }
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 20; j++) {
      matriz[i][j].pos_sequencial = i * 20 + j;
      for (int k = 0; k < 40; k++) {
        if (matriz[i][j].pos_sequencial == v_rand[k]) {
          matriz[i][j].tipo = 1;
        }
      }
      for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) {
          if (matriz[i][j].tipo != 1) {
            matriz[i][j].tipo = 0;
          }
        }
      }
    }
  }
}

//Função responsavel por identificar no numero de minas alocadas nas pontas da matriz.
void verif_mina_pontas(espaco **matriz) {

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 20; j++) {
      switch (matriz[i][j].pos_sequencial) {
      case 0:
        if (matriz[i][j].tipo == 1) {
          break;
        } else {
          if (matriz[0][1].tipo == 1) {
            matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
          }
          if (matriz[1][0].tipo == 1) {
            matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
          }
          if (matriz[1][1].tipo == 1) {
            matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
          }
          break;
        }

      case 19:
        if (matriz[i][j].tipo == 1) {
          break;
        } else {
          if (matriz[0][18].tipo == 1) {
            matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
          }
          if (matriz[1][19].tipo == 1) {
            matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
          }
          if (matriz[1][18].tipo == 1) {
            matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
          }
          break;
        }

      case 180:
        if (matriz[i][j].tipo == 1) {
          break;
        } else {
          if (matriz[8][0].tipo == 1) {
            matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
          }
          if (matriz[9][1].tipo == 1) {
            matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
          }
          if (matriz[8][1].tipo == 1) {
            matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
          }
          break;
        }

      case 199:
        if (matriz[i][j].tipo == 1) {
          break;
        } else {
          if (matriz[9][18].tipo == 1) {
            matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
          }
          if (matriz[8][19].tipo == 1) {
            matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
          }
          if (matriz[8][18].tipo == 1) {
            matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
          }
          break;
        }
      }
    }
  }
}


//Função responsavel por identificar no numero de minas alocadas nas primeiras colunas e linhas da matriz.
void verif_mina_extremoz_linhas(espaco **matriz) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 20; j++) {
      if (matriz[i][j].tipo == 1) {
        continue;
      }
      if (matriz[i][j].pos_sequencial > 0 && matriz[i][j].pos_sequencial < 19) {
        if (matriz[i][j - 1].tipo == 1) {
          matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
        }
        if (matriz[i][j + 1].tipo == 1) {
          matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
        }
        if (matriz[i + 1][j].tipo == 1) {
          matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
        }
        if (matriz[i + 1][j - 1].tipo == 1) {
          matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
        }
        if (matriz[i + 1][j + 1].tipo == 1) {
          matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
        }
      }
      if (matriz[i][j].pos_sequencial > 180 &&
          matriz[i][j].pos_sequencial < 199) {
        if (matriz[i][j - 1].tipo == 1) {
          matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
        }
        if (matriz[i][j + 1].tipo == 1) {
          matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
        }
        if (matriz[i - 1][j].tipo == 1) {
          matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
        }
        if (matriz[i - 1][j - 1].tipo == 1) {
          matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
        }
        if (matriz[i - 1][j + 1].tipo == 1) {
          matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
        }
      }
      if (i > 0 && i < 9 && j == 0) {
        if (matriz[i + 1][j].tipo == 1) {
          matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
        }
        if (matriz[i - 1][j].tipo == 1) {
          matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
        }
        if (matriz[i - 1][j + 1].tipo == 1) {
          matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
        }
        if (matriz[i][j + 1].tipo == 1) {
          matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
        }
        if (matriz[i + 1][j + 1].tipo == 1) {
          matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
        }
      }
      if (i > 0 && i < 9 && j == 19) {
        if (matriz[i + 1][j].tipo == 1) {
          matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
        }
        if (matriz[i - 1][j].tipo == 1) {
          matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
        }
        if (matriz[i - 1][j - 1].tipo == 1) {
          matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
        }
        if (matriz[i][j - 1].tipo == 1) {
          matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
        }
        if (matriz[i + 1][j - 1].tipo == 1) {
          matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
        }
      }
    }
  }
}

//Função responsavel por identificar no numero de minas alocadas no centro da matriz.
void verif_mina_centro(espaco **matriz) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 20; j++) {
      if (matriz[i][j].tipo == 1) {
        continue;
      }
      if (1 && i > 0 && j > 0 && i < 9 && j < 19) {
        if (matriz[i][j - 1].tipo == 1) {
          matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
        }
        if (matriz[i][j + 1].tipo == 1) {
          matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
        }
        if (matriz[i - 1][j].tipo == 1) {
          matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
        }
        if (matriz[i + 1][j].tipo == 1) {
          matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
        }
        if (matriz[i + 1][j - 1].tipo == 1) {
          matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
        }
        if (matriz[i + 1][j + 1].tipo == 1) {
          matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
        }
        if (matriz[i - 1][j - 1].tipo == 1) {
          matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
        }
        if (matriz[i - 1][j + 1].tipo == 1) {
          matriz[i][j].n_minas = matriz[i][j].n_minas + 1;
        }
      }
    }
  }
}

//Função responsavel por reunir todas as pequenas funções para craição da matriz completa.
void cria_camp_min(int *vet_rand, espaco **matriz) {
  v_minas(vet_rand);
  cria_campo(vet_rand, matriz);
  verif_mina_pontas(matriz);
  verif_mina_extremoz_linhas(matriz);
  verif_mina_centro(matriz);
}

// Função responsavel por abrir os espaços e fazer a chamada recursiva da função.
int abri_space(espaco **matriz, int linha, int coluna) {
 
  int help = 0;
  if (matriz[linha][coluna].tipo == 0 && matriz[linha][coluna].n_minas == 0) {
      if(linha == 0 && coluna == 0){
          matriz[linha][coluna].status = matriz[linha][coluna].n_minas + '0';
          matriz[linha][coluna].aberto =1;
          matriz[linha][coluna+1].status = matriz[linha][coluna+1].n_minas + '0';
          matriz[linha+1][coluna].status = matriz[linha+1][coluna].n_minas + '0';
          matriz[linha+1][coluna+1].status = matriz[linha+1][coluna+1].n_minas + '0';
          if(matriz[linha][coluna+1].tipo == 0){
            if(matriz[linha][coluna+1].aberto == 0){
              abri_space(matriz,linha,coluna+1);
            };
          }
          if(matriz[linha+1][coluna].tipo == 0){
            if(matriz[linha+1][coluna].aberto == 0){
              abri_space(matriz,linha+1,coluna);
            };
          }
          if(matriz[linha+1][coluna+1].tipo == 0){
            if(matriz[linha+1][coluna+1].aberto == 0){
              abri_space(matriz,linha+1,coluna+1);
            };
          }
        }
        else if(linha == 9 && coluna == 0){
          matriz[linha][coluna].status = matriz[linha][coluna].n_minas + '0';
          matriz[linha][coluna].aberto =1;
          matriz[linha][coluna+1].status = matriz[linha][coluna+1].n_minas + '0';
          matriz[linha-1][coluna].status = matriz[linha-1][coluna].n_minas + '0';
          matriz[linha-1][coluna+1].status = matriz[linha-1][coluna+1].n_minas + '0';
          if(matriz[linha][coluna+1].tipo == 0){
            if(matriz[linha][coluna+1].aberto == 0){
              abri_space(matriz,linha,coluna+1);
            };
          }
          if(matriz[linha-1][coluna].tipo == 0){
            if(matriz[linha-1][coluna].aberto == 0){
              abri_space(matriz,linha-1,coluna);
            };
          }
          if(matriz[linha-1][coluna+1].tipo == 0){
            if(matriz[linha-1][coluna+1].aberto == 0){
              abri_space(matriz,linha-1,coluna+1);
            };
          }
        }
        else if(linha == 9 && coluna == 19){
          matriz[linha][coluna].status = matriz[linha][coluna].n_minas + '0';
          matriz[linha][coluna].aberto =1;
          matriz[linha][coluna-1].status = matriz[linha][coluna-1].n_minas + '0';
          matriz[linha-1][coluna].status = matriz[linha-1][coluna].n_minas + '0';
          matriz[linha-1][coluna-1].status = matriz[linha-1][coluna-1].n_minas + '0';
          if(matriz[linha][coluna-1].tipo == 0){
            if(matriz[linha][coluna-1].aberto == 0){
              abri_space(matriz,linha,coluna-1);
            };
          }
          if(matriz[linha-1][coluna].tipo == 0){
            if(matriz[linha-1][coluna].aberto == 0){
              abri_space(matriz,linha-1,coluna);
            };
          }
          if(matriz[linha-1][coluna-1].tipo == 0){
            if(matriz[linha-1][coluna-1].aberto == 0){
              abri_space(matriz,linha-1,coluna-1);
            };
          }
        }
        else if(linha == 0 && coluna == 19){
          matriz[linha][coluna].status = matriz[linha][coluna].n_minas + '0';
          matriz[linha][coluna].aberto =1;
          matriz[linha][coluna-1].status = matriz[linha][coluna-1].n_minas + '0';
          matriz[linha+1][coluna].status = matriz[linha+1][coluna].n_minas + '0';
          matriz[linha+1][coluna-1].status = matriz[linha+1][coluna-1].n_minas + '0';
          if(matriz[linha][coluna-1].tipo == 0){
            if(matriz[linha][coluna-1].aberto == 0){
              abri_space(matriz,linha,coluna-1);
            };
          }
          if(matriz[linha+1][coluna].tipo == 0){
            if(matriz[linha+1][coluna].aberto == 0){
              abri_space(matriz,linha+1,coluna);
            };
          }
          if(matriz[linha+1][coluna-1].tipo == 0){
            if(matriz[linha+1][coluna-1].aberto == 0){
              abri_space(matriz,linha+1,coluna-1);
            };
          }
        }
        else if(linha >0 &&linha <9 && coluna ==0){
          matriz[linha][coluna].status = matriz[linha][coluna].n_minas + '0';
          matriz[linha][coluna].aberto =1;
          matriz[linha-1][coluna].status = matriz[linha-1][coluna].n_minas + '0';
          matriz[linha+1][coluna].status = matriz[linha+1][coluna].n_minas + '0';
          matriz[linha][coluna+1].status = matriz[linha][coluna+1].n_minas + '0';
          matriz[linha+1][coluna+1].status = matriz[linha+1][coluna+1].n_minas + '0';
          matriz[linha-1][coluna+1].status = matriz[linha-1][coluna+1].n_minas + '0';  
          
          if(matriz[linha-1][coluna].tipo == 0){
            if(matriz[linha-1][coluna].aberto == 0){
              abri_space(matriz,linha-1,coluna);
            };
          }
          if(matriz[linha+1][coluna].tipo == 0){
            if(matriz[linha+1][coluna].aberto == 0){
              abri_space(matriz,linha+1,coluna);
            };
          }
          if(matriz[linha][coluna+1].tipo == 0){
            if(matriz[linha][coluna+1].aberto == 0){
              abri_space(matriz,linha,coluna+1);
            };
          }
          if(matriz[linha+1][coluna+1].tipo == 0){
            if(matriz[linha+1][coluna+1].aberto == 0){
              abri_space(matriz,linha+1,coluna+1);
            };
          }
          if(matriz[linha-1][coluna+1].tipo == 0){
            if(matriz[linha-1][coluna+1].aberto == 0){
              abri_space(matriz,linha-1,coluna+1);
            };
          }
          
        }
        else if(linha == 0 && coluna > 0 && coluna <19){
          matriz[linha][coluna].status = matriz[linha][coluna].n_minas + '0';
          matriz[linha][coluna].aberto =1;
          matriz[linha+1][coluna].status = matriz[linha+1][coluna].n_minas + '0';
          matriz[linha][coluna+1].status = matriz[linha][coluna+1].n_minas + '0';
          matriz[linha][coluna-1].status = matriz[linha][coluna-1].n_minas + '0';
          matriz[linha+1][coluna+1].status = matriz[linha+1][coluna+1].n_minas + '0';
          matriz[linha+1][coluna-1].status = matriz[linha+1][coluna-1].n_minas + '0';    
          if(matriz[linha+1][coluna].tipo == 0){
            if(matriz[linha+1][coluna].aberto == 0){
              abri_space(matriz,linha+1,coluna);
            };
          }
          if(matriz[linha][coluna+1].tipo == 0){
            if(matriz[linha][coluna+1].aberto == 0){
              abri_space(matriz,linha,coluna+1);
            };
          }
          if(matriz[linha][coluna-1].tipo == 0){
            if(matriz[linha][coluna-1].aberto == 0){
              abri_space(matriz,linha,coluna-1);
            };
          }
          if(matriz[linha+1][coluna+1].tipo == 0){
            if(matriz[linha+1][coluna+1].aberto == 0){
              abri_space(matriz,linha+1,coluna+1);
            };
          }
          if(matriz[linha+1][coluna-1].tipo == 0){
            if(matriz[linha+1][coluna-1].aberto == 0){
              abri_space(matriz,linha+1,coluna-1);
            };
          }
        }
        else if(linha == 9 && coluna > 0 && coluna <19){
          matriz[linha][coluna].status = matriz[linha][coluna].n_minas + '0';
          matriz[linha][coluna].aberto =1;
          matriz[linha-1][coluna].status = matriz[linha-1][coluna].n_minas + '0';
          matriz[linha][coluna-1].status = matriz[linha][coluna-1].n_minas + '0';
          matriz[linha][coluna+1].status = matriz[linha][coluna+1].n_minas + '0';
          matriz[linha-1][coluna-1].status = matriz[linha-1][coluna-1].n_minas + '0';
          matriz[linha-1][coluna+1].status = matriz[linha-1][coluna+1].n_minas + '0';    
          if(matriz[linha-1][coluna].tipo == 0){
            if(matriz[linha-1][coluna].aberto == 0){
              abri_space(matriz,linha-1,coluna);
            };
          }
          if(matriz[linha][coluna-1].tipo == 0){
            if(matriz[linha][coluna-1].aberto == 0){
              abri_space(matriz,linha,coluna-1);
            };
          }
          if(matriz[linha][coluna+1].tipo == 0){
            if(matriz[linha][coluna+1].aberto == 0){
              abri_space(matriz,linha,coluna+1);
            };
          }
          if(matriz[linha-1][coluna-1].tipo == 0){
            if(matriz[linha-1][coluna-1].aberto == 0){
              abri_space(matriz,linha-1,coluna-1);
            };
          }
          if(matriz[linha-1][coluna+1].tipo == 0){
            if(matriz[linha-1][coluna+1].aberto == 0){
              abri_space(matriz,linha-1,coluna+1);
            }
          }
        }
        else if(linha > 0 && linha <9 && coluna == 19){
          matriz[linha][coluna].status = matriz[linha][coluna].n_minas + '0';
          matriz[linha][coluna].aberto =1;
          matriz[linha-1][coluna].status = matriz[linha-1][coluna].n_minas + '0';
          matriz[linha+1][coluna].status = matriz[linha+1][coluna].n_minas + '0';
          matriz[linha][coluna-1].status = matriz[linha][coluna-1].n_minas + '0';
          matriz[linha+1][coluna-1].status = matriz[linha+1][coluna-1].n_minas + '0';
          matriz[linha-1][coluna-1].status = matriz[linha-1][coluna-1].n_minas + '0';    
          if(matriz[linha-1][coluna].tipo == 0){
            if(matriz[linha-1][coluna].aberto == 0){
              abri_space(matriz,linha-1,coluna);
            }
          }
          if(matriz[linha+1][coluna].tipo == 0){
            if(matriz[linha+1][coluna].aberto == 0){
              abri_space(matriz,linha+1,coluna);
              }
          }
          if(matriz[linha][coluna-1].tipo == 0){
            if(matriz[linha][coluna-1].aberto == 0){
              abri_space(matriz,linha,coluna-1);
            }
          }
          if(matriz[linha+1][coluna-1].tipo == 0){
            if(matriz[linha+1][coluna-1].aberto == 0){
              abri_space(matriz,linha+1,coluna-1);
            }
          }
          if(matriz[linha-1][coluna-1].tipo == 0){
            if(matriz[linha-1][coluna-1].aberto == 0){
              abri_space(matriz,linha-1,coluna-1);
            }
          }
        }
        else{
          matriz[linha][coluna].status = matriz[linha][coluna].n_minas + '0';
          matriz[linha][coluna].aberto =1;
          matriz[linha+1][coluna].status = matriz[linha+1][coluna].n_minas + '0';
          matriz[linha-1][coluna].status = matriz[linha-1][coluna].n_minas + '0';
          matriz[linha][coluna+1].status = matriz[linha][coluna+1].n_minas + '0';
          matriz[linha][coluna-1].status = matriz[linha][coluna-1].n_minas + '0';
          matriz[linha+1][coluna+1].status = matriz[linha+1][coluna+1].n_minas + '0';
          matriz[linha+1][coluna-1].status = matriz[linha+1][coluna-1].n_minas + '0';
          matriz[linha-1][coluna+1].status = matriz[linha-1][coluna+1].n_minas + '0';
          matriz[linha-1][coluna-1].status = matriz[linha-1][coluna-1].n_minas + '0';    
          if(matriz[linha-1][coluna].tipo == 0){
            if(matriz[linha-1][coluna].aberto == 0){
              abri_space(matriz,linha-1,coluna);
            }
          }
          if(matriz[linha+1][coluna].tipo == 0){
            if(matriz[linha+1][coluna].aberto == 0){
              abri_space(matriz,linha+1,coluna);
            }
          }
          if(matriz[linha][coluna-1].tipo == 0){
            if(matriz[linha][coluna-1].aberto == 0){
              abri_space(matriz,linha,coluna-1);
            }
          }
          if(matriz[linha][coluna+1].tipo == 0){
            if(matriz[linha][coluna+1].aberto == 0){
              abri_space(matriz,linha,coluna+1);
            }
          }
          if(matriz[linha+1][coluna+1].tipo == 0){
            if(matriz[linha+1][coluna+1].aberto == 0){
              abri_space(matriz,linha+1,coluna+1);
            }
          }
          if(matriz[linha+1][coluna-1].tipo == 0){
            if(matriz[linha+1][coluna-1].aberto == 0){
              abri_space(matriz,linha+1,coluna-1);
            }
          }
          if(matriz[linha-1][coluna+1].tipo == 0){
            if(matriz[linha-1][coluna+1].aberto == 0){
              abri_space(matriz,linha-1,coluna+1);
            }
          }
          if(matriz[linha-1][coluna-1].tipo == 0){
            if(matriz[linha-1][coluna-1].aberto == 0){
              abri_space(matriz,linha-1,coluna-1);
            }
          }
        }
   
    return help;
  } else if (matriz[linha][coluna].tipo == 1) {
    matriz[linha][coluna].status = matriz[linha][coluna].n_minas + '0';
    help = 1;
   
    return help;
  } else {
    matriz[linha][coluna].status = matriz[linha][coluna].n_minas + '0';
    matriz[linha][coluna].aberto =1;
    return help; 
  }
}



//Verificar e retornar o valor de cedulas ja abertas no programa.
int verif_ced_abertas(espaco **matriz){ 
  int contador = 0;
  for(int i = 0; i<10; i++){
    for(int j = 0; j<20; j++){
      if(matriz[i][j].aberto == 1){
        contador++;
      }
    }
  }
  return contador;
}
void verif_tempo(time_t inicial){
  int tempo=0;
  time_t finall = time(NULL);
  tempo = finall - inicial;
  int minutos = tempo/60;
  int horas = minutos/60;
      
  if(tempo ==1){
    printf("%d segundo\n\n",tempo);
  }
  else if(tempo < 60){
    printf("%d segundos\n\n",tempo);
  }else if(tempo >60 && tempo <3600){
    printf("%d minutos e %d segundos\n\n",tempo/60,tempo - (60*minutos));
  }else if(tempo ==60){
    printf("%d minuto\n\n",tempo/60);
  }else if(tempo ==3600){
    printf("%d hora\n\n",tempo/3600);
  }else if( tempo>3600){
    printf("%d horas %d minutos e %d segundos\n\n",tempo/3600,tempo - (60* horas),tempo - (60*minutos));
  }
}

void jogar(espaco **matriz) {
  int l;
  int c;
  int aux = 0;
  int contador = 0;
  int n_bombas = 40;
  char select[255];
  time_t inicial = time(NULL);
  printf("Numero de bombas não marcadas: %d\n", n_bombas); // Aparecera na primeira jogada e toda vez que ele marcar bomba.
  print_matriz_status(matriz);
  printf("\n");
  printf("\n");
  
  while (aux == 0 || contador < 160) {
    
    printf("Tiro, bomba, tempo ou ajuda? ");
    scanf("%s", select);
    printf("\n");
    if (strcmp(select, "bomba") == 0) {
      scanf("%d", &l);
      scanf("%d", &c);
      printf("\n");
      matriz[l][c].status = 'B';
      n_bombas--;
      printf("Numero de bombas não marcadas: %d\n", n_bombas); // Controle de quantas bombas ainda existiria para ele marcar.
      print_matriz_status(matriz);
      printf("\n");
      printf("\n");
    }
    else if (strcmp(select, "tempo") == 0){
      printf("Tempo de jogo: ");
      verif_tempo(inicial);
      printf("\n");
    }
    else {

      scanf("%d", &l);
      scanf("%d", &c);
      printf("\n");
      aux = abri_space(matriz, l, c);
      contador = verif_ced_abertas(matriz);
      if(contador >= 160){
        
        printf("PARABENS VOCÊ GANHOU!!!!\n"); //Se o jogador conseguir desbloquear 160 cedulas sem clicar em nenhuma bomba ele vence o jogo.
        printf("Tempo de jogo: ");
        verif_tempo(inicial);
        printf("\n");
        break;
      }
      else{
        printf(" %d no momento\n", contador);
      
      if (aux == 0) {
        print_matriz_status(matriz);
        printf("\n");
        printf("\n");
      } else {
        printf("BOOM\n");
        print_matriz_status(matriz);
        verif_tempo(inicial);
        printf("PERDEU\n");
        printf("Tempo de jogo: ");
        verif_tempo(inicial);
        printf("\n");
        break;
      }

      }
      
    }
  }
 
}


void menu(espaco **matriz, int *vet_rand){
  int selecionado, linha, coluna;
  printf("              MENU\n  Jogar - 0\n  Jogar-Automaticamente - 1 \n  "
         "Instrucoes - 2 \nDigte uma das opções acima:\n  ");
  scanf("%d", &selecionado);
  if (selecionado == 2) {
    printf(" 1. Uma mina é revelada: nesse caso, o jogo encerra com a derrota "
           "do usuário;\n 2. Um número é revelado: o valor indica a quantidade "
           "de minas adjacentes considerando as 8 células ao redor de uma "
           "posição (vertical, horizontal e diagonais);\n 3. Uma posição vazia "
           "é revelada: nesse caso, o jogo aplica a ação revelar sobre todas "
           "as células adjacentes a essa posição, visto que ela não possui "
           "minas adjacentes.");
  }
  if (selecionado == 0) {
    vet_rand = malloc(sizeof(int) * 40);

    matriz = malloc(sizeof(espaco *) * 10);
    for (int i = 0; i < 10; i++) {
      matriz[i] = malloc(sizeof(espaco) * 20);
    }

    cria_camp_min(vet_rand, matriz);
    free(vet_rand);

    // criar jogo
    jogar(matriz);
  }
  if (selecionado == 1) {
    // criar jogo automatico
  }

  for (int i = 0; i < 10; i++) {
    free(matriz[i]);
  }
  free(matriz);
}
