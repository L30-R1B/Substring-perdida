#ifndef _forca_bruta_h_
#define _forca_bruta_h_

/**
 * @brief Implementa a busca de padrões em strings usando o algoritmo de força bruta.
 *
 * A função forca_bruta procura um padrão no texto usando o método de força bruta, que compara o padrão com cada
 * substring do texto de comprimento igual ao padrão. Este método é simples, mas pode ser ineficiente para textos
 * e padrões grandes, pois verifica todas as possíveis posições no texto.
 *
 * @param texto O texto no qual o padrão será procurado.
 * @param padrao O padrão que será procurado no texto.
 * @return Retorna 1 se o padrão for encontrado no texto, caso contrário, retorna 0.
 */
int forca_bruta(const char *texto, const char *padrao);

#endif