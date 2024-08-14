#ifndef KMP_H
#define KMP_H

/**
 * @brief Implementa o algoritmo Knuth-Morris-Pratt (KMP) para busca de padrões em strings.
 *
 * A função kmp verifica se um padrão está presente em um texto usando o algoritmo KMP, que é eficiente para
 * buscas em strings ao evitar comparações redundantes.
 *
 * @param texto O texto no qual o padrão será procurado.
 * @param padrao O padrão que será procurado no texto.
 * @return Retorna 1 se o padrão for encontrado no texto, caso contrário, retorna 0.
 */
int kmp(const char *texto, const char *padrao);

#endif
