
#ifndef FUNC_H_
#define FUNC_H_


void print_matriz_status(espaco **matriz);
void v_minas(int *v_rand);
void cria_campo(int *v_rand, espaco **matriz);
void verif_mina_pontas(espaco **matriz);
void verif_mina_extremoz_linhas(espaco **matriz);
void verif_mina_centro(espaco **matriz);
void cria_camp_min(int *vet_rand, espaco **matriz);
int abri_space(espaco **matriz, int linha, int coluna);
int verif_ced_abertas(espaco **matriz);
void jogar(espaco **matriz);
void menu(espaco **matriz, int *vet_rand);
void verif_tempo(time_t inicial);


#endif
