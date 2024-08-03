#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <pthread.h>

#include "../include/kmp.h"
#include "../include/forca_bruta.h"
#include "../include/shift_and.h"

#include "../include/utils.h"
#include "../include/execute.h"

int main(int argc, char *argv[]) {
    if(argc != 2){
        printf("Uso : ./tp3 <Aquivo de entrada>\n");
        return 1;
    }

    char *texto = NULL;
    char *padrao = NULL;
    struct Intervalo *intervalos = NULL;
    unsigned numIntervalos = 0;

    numIntervalos = ler_arq_input(argv[1], &texto, &padrao, &intervalos);
    if(!numIntervalos)
        return 1;

    if(!strcmp(ler_variavel_ambiente("variaveis_ambiente.env", "EXECUCAO_PARALELA"), "false")){
        struct timeval start_time, end_time;
        struct rusage start, end;
        struct Tempo t;
        
        printf("----------------------------------------------\n");
        
        getrusage(RUSAGE_SELF, &start);
        gettimeofday(&start_time, NULL);

        if(!strcmp(ler_variavel_ambiente("variaveis_ambiente.env", "ALGORITMO_PRINCIPAL"), "kmp")){
            printf("Kmp :\n");
            executa_algoritmo_casamento(kmp, texto, padrao, 1, intervalos, numIntervalos);
        }else if(!strcmp(ler_variavel_ambiente("variaveis_ambiente.env", "ALGORITMO_PRINCIPAL"), "forca-bruta")){
            printf("Força bruta :\n");
            executa_algoritmo_casamento(forca_bruta, texto, padrao, 1, intervalos, numIntervalos);
        }else{
            printf("Shift and :\n");
            executa_algoritmo_casamento(shift_and, texto, padrao, 1, intervalos, numIntervalos);
        }

        gettimeofday(&end_time, NULL);
        getrusage(RUSAGE_SELF, &end);

        t.sistema = retorna_tempo_sistema(&start, &end);
        t.usuario = retorna_tempo_usuario(&start, &end);
        t.total = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
        printf("\tTempo sistema : %lf\n", t.sistema);
        printf("\tTempo usuario : %lf\n", t.usuario);
        printf("\tTempo total   : %lf\n", t.total);
        printf("----------------------------------------------\n");
    }else{

        ParamsThread p[3];
        unsigned qtdFuncoes = 0;

        if(!strcmp(ler_variavel_ambiente("variaveis_ambiente.env", "SHIFT_AND"), "true")){
            p[qtdFuncoes].alg = shift_and;
            p[qtdFuncoes].funcaoExec = 's';
            qtdFuncoes ++;
        }
        if(!strcmp(ler_variavel_ambiente("variaveis_ambiente.env", "KMP"), "true")){
            p[qtdFuncoes].alg = kmp;
            p[qtdFuncoes].funcaoExec = 'k';
            qtdFuncoes ++;
        }
        if(!strcmp(ler_variavel_ambiente("variaveis_ambiente.env", "FORCA_BRUTA"), "true")){
            p[qtdFuncoes].alg = forca_bruta;
            p[qtdFuncoes].funcaoExec = 'f';
            qtdFuncoes ++;
        }

        if(!qtdFuncoes){
            printf("Atrubua \"true\" para algum algoritmo em \"variaveis_ambiente.env\"\n");
            free(texto);
            free(padrao);
            free(intervalos);
            return 1;
        }

        for(unsigned i = 0; i < qtdFuncoes; i ++){
            p[i].escreverOutput = (i == 0) ? 1 : 0;
            p[i].intervalos = intervalos;
            p[i].texto = texto;
            p[i].padrao = padrao;
            p[i].qtdIntervalos = numIntervalos;
        }

        pthread_t threads[qtdFuncoes];

        for (unsigned i = 0; i < qtdFuncoes; i++) {
            if (pthread_create(&threads[i], NULL, thread_executa, &p[i]) != 0) {
                perror("Erro ao criar thread");
                free(texto);
                free(padrao);
                free(intervalos);
                return 1;
            }
        }

        for (unsigned i = 0; i < qtdFuncoes; i++) {
            pthread_join(threads[i], NULL);
        }

        for (unsigned i = 0; i < qtdFuncoes; i++) {
            printf("----------------------------------------------\n");
            if(p[i].funcaoExec == 's')
                printf("Shift and :\n");
            else if(p[i].funcaoExec == 'k')
                printf("Kmp :\n");
            else
                printf("Força bruta : \n");
            
            printf("\tTempo sistema : %lf\n", p[i].tempo.sistema);
            printf("\tTempo usuario : %lf\n", p[i].tempo.usuario);
            printf("\tTempo total   : %lf\n", p[i].tempo.total);
        }
        printf("----------------------------------------------\n");
    }

    free(texto);
    free(padrao);
    free(intervalos);
}
