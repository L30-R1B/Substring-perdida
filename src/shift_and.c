#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/shift_and.h"
#include "../include/utils.h"

typedef unsigned long long bitarray_t;

static int padraoLen = 0;
static bitarray_t mascaras[256] = {0};

void inicializa_mascaras(const char *padrao){
    padraoLen = strlen(padrao);
    memset(mascaras, 0, sizeof(mascaras));
    for (int i = 0; i < padraoLen; i++) {
        mascaras[(unsigned char)padrao[i]] |= (1ULL << i);
    }
}

int shift_and(const char *texto, const char *padrao) {
    if (!padraoLen) {
        inicializa_mascaras(padrao);
    }

    bitarray_t estado = 0;

    for (int i = 0; texto[i] != '\0'; i++) {
        estado = ((estado << 1) | 1) & mascaras[(unsigned char)texto[i]];
        if (estado & (1ULL << (padraoLen - 1))) {
            return 1;
        }
    }

    return 0;
}