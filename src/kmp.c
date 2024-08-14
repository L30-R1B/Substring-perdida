#include <stdlib.h>
#include <string.h>
#include "../include/kmp.h"

/**
 * @brief Prepara o array de prefixos mais longos que também são sufixos (LPS) usado no algoritmo KMP.
 *
 * A função compute_lps_array calcula o array LPS para o padrão fornecido. O array LPS armazena o comprimento do
 * maior prefixo que é também um sufixo para cada prefixo do padrão, o que é usado no algoritmo KMP para evitar
 * comparações redundantes.
 *
 * @param padrao O padrão para o qual o array LPS será calculado.
 * @param m O comprimento do padrão.
 * @param lps O array LPS que será preenchido pela função.
 */
static void compute_lps_array(const char *padrao, int m, int *lps) {
    int len = 0;
    lps[0] = 0;
    int i = 1;

    while (i < m) {
        if (padrao[i] == padrao[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int kmp(const char *texto, const char *padrao) {
    int n = strlen(texto);
    int m = strlen(padrao);
    int lps[m];
    int i = 0, j = 0;

    compute_lps_array(padrao, m, lps);

    while (i < n) {
        if (padrao[j] == texto[i]) {
            j++;
            i++;
        }
        if (j == m) {
            return 1;
        } else if (i < n && padrao[j] != texto[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    return 0;
}
