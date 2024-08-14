#ifndef _execute_h_
#define _execute_h_

#include "../include/utils.h"

/**
 * @brief Estrutura para parâmetros de thread.
 *
 * Esta estrutura armazena os parâmetros necessários para executar um algoritmo em uma thread. Inclui o método
 * de busca, informações sobre o texto e o padrão a ser buscado, opções de saída e intervalos de busca.
 */
typedef struct {
    Metodo alg;                  /**< Método de busca a ser utilizado. */
    char funcaoExec;             /**< Função de execução, provavelmente um identificador para a função específica. */
    char *texto;                 /**< Texto onde a busca será realizada. */
    char *padrao;                /**< Padrão a ser buscado no texto. */
    unsigned char escreverOutput; /**< Flag que indica se o resultado deve ser escrito em um arquivo. */
    struct Intervalo *intervalos; /**< Intervalos de busca no texto. */
    unsigned qtdIntervalos;      /**< Quantidade de intervalos de busca. */
    struct Tempo tempo;          /**< Estrutura para armazenar tempos de execução. */
} ParamsThread;
/**
 * @brief Executa um algoritmo de casamento de padrões em intervalos especificados de um texto.
 *
 * Esta função aplica o algoritmo de casamento de padrões fornecido em diferentes intervalos do texto e, se solicitado,
 * escreve os resultados em um arquivo. O resultado da busca para cada intervalo é escrito no arquivo ou apenas
 * executado, dependendo da flag `escreverOutput`.
 *
 * @param alg O método de busca a ser utilizado.
 * @param texto O texto onde o padrão será procurado.
 * @param padrao O padrão que será procurado no texto.
 * @param escreverOutput Flag que indica se o resultado deve ser escrito em um arquivo.
 * @param intervalos Array de intervalos onde a busca será realizada.
 * @param qtdIntervalos Quantidade de intervalos no array.
 */
void executa_algoritmo_casamento(Metodo alg, const char *texto, const char *padrao, unsigned char escreverOutput, struct Intervalo intervalos[], unsigned qtdIntervalos);

/**
 * @brief Função de thread para executar um algoritmo de casamento de padrões.
 *
 * Esta função é executada em uma thread e mede o tempo de execução do algoritmo de casamento de padrões. A função
 * calcula o tempo de CPU e o tempo total gasto na execução do algoritmo, armazenando essas informações na estrutura
 * `ParamsThread`.
 *
 * @param paramTh Ponteiro para uma estrutura `ParamsThread` contendo os parâmetros para a execução.
 * @return Retorna NULL ao finalizar a execução da thread.
 */
void *thread_executa(void *paramTh);

#endif