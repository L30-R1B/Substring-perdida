#include <stdio.h>
#include <string.h>
#include "../include/forca_bruta.h"

int forca_bruta(const char *texto, const char *padrao) {
    int textoLen = strlen(texto);
    int padraoLen = strlen(padrao);

    if (padraoLen > textoLen) {
        return 0;
    }

    for (int i = 0; i <= textoLen - padraoLen; i++) {
        int j;
        for (j = 0; j < padraoLen; j++) {
            if (texto[i + j] != padrao[j]) {
                break;
            }
        }
        if (j == padraoLen) {
            return 1;
        }
    }
    return 0;
}