#ifndef _execute_h_
#define _execute_h_

#include "../include/utils.h"

typedef struct {
    Metodo alg;
    char funcaoExec;
    char *texto;
    char *padrao;
    unsigned char escreverOutput;
    struct Intervalo *intervalos;
    unsigned qtdIntervalos;
    struct Tempo tempo;
} ParamsThread;

void executa_algoritmo_casamento(Metodo alg, const char *texto, const char *padrao, unsigned char escreverOutput, struct Intervalo intervalos[], unsigned qtdIntervalos);
void *thread_executa(void *paramTh);

#endif