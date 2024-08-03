#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/shift_and.h"

typedef unsigned long long bitarray_t;

int shift_and(const char *texto, const char *padrao) {
    int padraoLen = strlen(padrao);
    if (padraoLen == 0) {
        return 0;
    }

    bitarray_t *mascaras = (bitarray_t *)calloc(256, sizeof(bitarray_t));
    if (!mascaras) {
        perror("Erro ao alocar memória para as máscaras");
        return 0;
    }

    for (int i = 0; i < padraoLen; i++) {
        mascaras[(unsigned char)padrao[i]] |= (1ULL << i);
    }

    bitarray_t estado = 0;

    for (int i = 0; texto[i] != '\0'; i++) {
        estado = ((estado << 1) | 1) & mascaras[(unsigned char)texto[i]];
        if (estado & (1ULL << (padraoLen - 1))) {
            free(mascaras);
            return 1;
        }
    }

    free(mascaras);
    return 0;
}
