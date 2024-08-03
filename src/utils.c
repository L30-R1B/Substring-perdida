#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <unistd.h>
#include "../include/utils.h"

#define MAX_LINE_LENGTH 256

char *substring(const char* str, int start, int end) {
    int len = strlen(str);

    if (start < 0 || end >= len || start > end) {
        return NULL;
    }

    int sub_len = end - start + 1;

    char* sub = (char*)malloc((sub_len + 1) * sizeof(char));
    if (!sub) {
        printf("Erro: Falha na alocação de memória.\n");
        return NULL;
    }

    strncpy(sub, str + start, sub_len);
    sub[sub_len] = '\0';

    return sub;
}

char *ler_variavel_ambiente(const char *nome_arquivo, const char *nome_variavel) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    char linha[MAX_LINE_LENGTH];
    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0';

        char *sinal_igual = strchr(linha, '=');
        if (sinal_igual == NULL) {
            continue;
        }

        *sinal_igual = '\0';

        char *nome_variavel = linha;
        char *valor_variavel = sinal_igual + 1;

        if (setenv(nome_variavel, valor_variavel, 1) != 0) {
            perror("Erro ao definir a variável de ambiente");
            fclose(arquivo);
            exit(EXIT_FAILURE);
        }
    }

    fclose(arquivo);

    char *valor = getenv(nome_variavel);
    
    return valor;
}


double retorna_tempo_sistema(struct rusage *start, struct rusage *end) {
    double start_sistema = (double)start->ru_stime.tv_sec + (double)start->ru_stime.tv_usec / 1000000.0;
    double end_sistema = (double)end->ru_stime.tv_sec + (double)end->ru_stime.tv_usec / 1000000.0;
    return end_sistema - start_sistema;
}

double retorna_tempo_usuario(struct rusage *start, struct rusage *end) {
    double start_usuario = (double)start->ru_utime.tv_sec + (double)start->ru_utime.tv_usec / 1000000.0;
    double end_usuario = (double)end->ru_utime.tv_sec + (double)end->ru_utime.tv_usec / 1000000.0;
    return end_usuario - start_usuario;
}

double tempo_total(struct timeval *start_time, struct timeval *end_time) {
    return (end_time->tv_sec - start_time->tv_sec) + (end_time->tv_usec - start_time->tv_usec) / 1000000.0;
}

unsigned ler_arq_input(const char *nome, char **texto, char **padrao, struct Intervalo **intervalos) {
    FILE *file_input = fopen(nome, "r");
    if (file_input == NULL) {
        printf("Arquivo de entrada não encontrado.\n");
        return 0;
    }

    size_t len = 0;
    ssize_t read;
    read = getline(texto, &len, file_input);
    if (read == -1) {
        printf("Erro ao ler o texto.\n");
        fclose(file_input);
        return 0;
    }
    (*texto)[strcspn(*texto, "\n")] = 0; 

    len = 0;
    read = getline(padrao, &len, file_input);
    if (read == -1) {
        printf("Erro ao ler o padrão.\n");
        fclose(file_input);
        return 0;
    }
    (*padrao)[strcspn(*padrao, "\n")] = 0;

    unsigned numIntervalos;
    if (fscanf(file_input, "%u", &numIntervalos) != 1) {
        printf("Erro ao ler o número de intervalos.\n");
        fclose(file_input);
        return 0;
    }

    *intervalos = (struct Intervalo *)malloc(numIntervalos * sizeof(struct Intervalo));
    if (*intervalos == NULL) {
        printf("Erro ao alocar memória para os intervalos.\n");
        fclose(file_input);
        return 0;
    }

    for (unsigned intervaloAtual = 0; intervaloAtual < numIntervalos; intervaloAtual++) {
        if (fscanf(file_input, "%u %u", &(*intervalos)[intervaloAtual].inicio, &(*intervalos)[intervaloAtual].fim) != 2) {
            printf("Erro ao ler o intervalo %u.\n", intervaloAtual);
            free(*intervalos);
            fclose(file_input);
            return 0;
        }
    }

    fclose(file_input);
    return numIntervalos;
}