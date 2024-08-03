#ifndef _utils_h_
#define _utils_h_

typedef int (*Metodo)(const char *, const char *);

struct Tempo{
    double usuario;
    double sistema;
    double total;
};

struct Intervalo {
    unsigned inicio;
    unsigned fim;
};

char *substring(const char* str, int start, int end);
char *ler_variavel_ambiente(const char *nome_arquivo, const char *nome_variavel);

double retorna_tempo_usuario(struct rusage *start, struct rusage *end);
double retorna_tempo_sistema(struct rusage *start, struct rusage *end);

unsigned ler_arq_input(const char *nome, char **texto, char **padrao, struct Intervalo **intervalos);

#endif