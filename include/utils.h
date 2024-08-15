#ifndef _utils_h_
#define _utils_h_

#include <sys/resource.h>

#define MAX_LINE_LENGTH 256 /**< Tamanho máximo da linha para leitura de variáveis de ambiente. */

/**
 * @brief Tipo de função para métodos de busca.
 *
 * Define um tipo de função que recebe dois parâmetros do tipo `const char*` e retorna um `int`. Usado para passar
 * algoritmos de busca para outras funções.
 */
typedef int (*Metodo)(const char *, const char *);

/**
 * @brief Estrutura para armazenar tempos de execução.
 *
 * Esta estrutura contém três campos para armazenar tempos de execução: o tempo de CPU do usuário, o tempo de CPU do
 * sistema e o tempo total decorrido.
 */
struct Tempo {
    double usuario; /**< Tempo de CPU do usuário em segundos. */
    double sistema; /**< Tempo de CPU do sistema em segundos. */
    double total; /**< Tempo total decorrido em segundos. */
};

/**
 * @brief Estrutura para definir um intervalo de busca.
 *
 * Esta estrutura define um intervalo em um texto, especificado por um início e um fim.
 */
struct Intervalo {
    unsigned inicio; /**< Posição inicial do intervalo (1 baseado). */
    unsigned fim; /**< Posição final do intervalo (1 baseado). */
};

/**
 * @brief Extrai um substring de uma string.
 *
 * Esta função extrai um substring de uma string original, começando na posição `start` e terminando na posição `end`.
 *
 * @param str A string original da qual o substring será extraído.
 * @param start Posição inicial do substring.
 * @param end Posição final do substring.
 * @return Um ponteiro para o substring extraído, ou NULL em caso de erro.
 */
char *substring(const char* str, int start, int end);

/**
 * @brief Lê variáveis de ambiente de um arquivo e define no ambiente do processo.
 *
 * Esta função lê um arquivo contendo variáveis de ambiente no formato "NOME=VALOR", define essas variáveis no ambiente
 * do processo e retorna o valor da variável solicitada.
 *
 * @param nome_arquivo O nome do arquivo contendo as variáveis de ambiente.
 * @param nome_variavel O nome da variável de ambiente a ser retornada.
 * @return O valor da variável de ambiente solicitada.
 */
char *ler_variavel_ambiente(const char *nome_arquivo, const char *nome_variavel);

/**
 * @brief Calcula o tempo de CPU do sistema entre dois pontos de medição.
 *
 * Esta função calcula a diferença entre o tempo de CPU do sistema registrado em dois pontos de medição, representados
 * pelas estruturas `rusage`.
 *
 * @param start Ponteiro para a estrutura `rusage` representando o início da medição.
 * @param end Ponteiro para a estrutura `rusage` representando o fim da medição.
 * @return O tempo de CPU do sistema em segundos.
 */
double retorna_tempo_sistema(struct rusage *start, struct rusage *end);

/**
 * @brief Calcula o tempo de CPU do usuário entre dois pontos de medição.
 *
 * Esta função calcula a diferença entre o tempo de CPU do usuário registrado em dois pontos de medição, representados
 * pelas estruturas `rusage`.
 *
 * @param start Ponteiro para a estrutura `rusage` representando o início da medição.
 * @param end Ponteiro para a estrutura `rusage` representando o fim da medição.
 * @return O tempo de CPU do usuário em segundos.
 */
double retorna_tempo_usuario(struct rusage *start, struct rusage *end);

/**
 * @brief Calcula o tempo total decorrido entre dois pontos de medição.
 *
 * Esta função calcula a diferença total entre dois pontos de medição de tempo, representados pelas estruturas `timeval`.
 *
 * @param start_time Ponteiro para a estrutura `timeval` representando o início da medição.
 * @param end_time Ponteiro para a estrutura `timeval` representando o fim da medição.
 * @return O tempo total decorrido em segundos.
 */
double tempo_total(struct timeval *start_time, struct timeval *end_time);

/**
 * @brief Lê um arquivo de entrada e carrega dados para processamento.
 *
 * Esta função lê um arquivo contendo o texto, o padrão a ser buscado e intervalos de busca, e aloca memória para armazenar
 * esses dados. Retorna o número de intervalos lidos.
 *
 * @param nome O nome do arquivo de entrada.
 * @param texto Ponteiro para armazenar o texto lido.
 * @param padrao Ponteiro para armazenar o padrão lido.
 * @param intervalos Ponteiro para armazenar um array de intervalos lidos.
 * @return O número de intervalos lidos do arquivo. Retorna 0 em caso de erro.
 */
unsigned ler_arq_input(const char *nome, char **texto, char **padrao, struct Intervalo **intervalos);

#endif