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

    //essa foi ideia do chat
    // Só vai pro fim se o modo for de escrita ou leitura+escrita
    if (strchr(modo, 'a') || strchr(modo, '+')) {
        fseek(f, 0, SEEK_END);
    }

    return f;
}
