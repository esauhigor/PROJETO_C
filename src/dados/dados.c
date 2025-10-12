#include "dados.h"
#include <stdio.h>
#include <string.h>

#define DATA_DIR "./dados/"

FILE* abrir_csv(const char* arquivo, const char* modo) {
    char caminho[256];
    snprintf(caminho, sizeof(caminho), "%s%s", DATA_DIR, arquivo);

    FILE* f = fopen(caminho, modo);
    if (!f) {
        printf("Erro ao abrir arquivo %s\n", caminho);
        return NULL;
    }

    return f;
}
