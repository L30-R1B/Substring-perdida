#ifndef _shift_and_h_
#define _shift_and_h_

/**
 * @brief Implementa o algoritmo Shift-And para busca de padrões em strings.
 *
 * A função shift_and verifica se um padrão está presente em um texto usando o algoritmo Shift-And. Este algoritmo
 * é baseado em operações bitwise para realizar a busca de maneira eficiente, especialmente quando o alfabeto é pequeno.
 *
 * @param texto O texto no qual o padrão será procurado.
 * @param padrao O padrão que será procurado no texto.
 * @return Retorna 1 se o padrão for encontrado no texto, caso contrário, retorna 0.
 */
int shift_and(const char *texto, const char *padrao);

#endif