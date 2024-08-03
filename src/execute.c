#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <time.h>

#include "../include/execute.h"
#include "../include/utils.h"

void executa_algoritmo_casamento(Metodo alg, const char *texto, const char *padrao, unsigned char escreverOutput, struct Intervalo intervalos[], unsigned qtdIntervalos) {    
    FILE *f = NULL;
    if (escreverOutput) {
        f = fopen("output/saida.txt", "w");
        if (f == NULL) {
            perror("Erro ao abrir o arquivo");
            return;
        }
    }
    char *querie = NULL;
    int resul;
    if(escreverOutput)
        for (unsigned i = 0; i < qtdIntervalos; i++) {
            querie = substring(texto, intervalos[i].inicio - 1, intervalos[i].fim - 1);
            if(querie == NULL){
                continue;
            }
            resul = alg(querie, padrao);
            if (escreverOutput) {
                if (resul)
                    fprintf(f, "sim\n");
                else
                    fprintf(f, "nao\n");
            }
            free(querie);
        }
    else
        for (unsigned i = 0; i < qtdIntervalos; i++) {
            querie = substring(texto, intervalos[i].inicio - 1, intervalos[i].fim - 1);
            if(querie == NULL){
                continue;
            }
            alg(querie, padrao);
            free(querie);
        }

    if (escreverOutput) {
        fclose(f);
    }
}

void *thread_executa(void *paramTh) {
    ParamsThread *p = (ParamsThread *)paramTh;

    struct timeval start_time, end_time;
    struct rusage start, end;

    getrusage(RUSAGE_SELF, &start);
    gettimeofday(&start_time, NULL);

    executa_algoritmo_casamento(p->alg, p->texto, p->padrao, p->escreverOutput, p->intervalos, p->qtdIntervalos);

    gettimeofday(&end_time, NULL);
    getrusage(RUSAGE_SELF, &end);

    p->tempo.sistema = retorna_tempo_sistema(&start, &end);
    p->tempo.usuario = retorna_tempo_usuario(&start, &end);
    p->tempo.total = tempo_total(&start_time, &end_time);

    pthread_exit(NULL);
}

