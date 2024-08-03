#include <stdlib.h>
#include <string.h>
#include "../include/kmp.h"

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
    int *lps = (int *)malloc(sizeof(int) * m);
    int i = 0, j = 0;

    compute_lps_array(padrao, m, lps);

    while (i < n) {
        if (padrao[j] == texto[i]) {
            j++;
            i++;
        }
        if (j == m) {
            free(lps);
            return 1;
        } else if (i < n && padrao[j] != texto[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    free(lps);
    return 0;
}
