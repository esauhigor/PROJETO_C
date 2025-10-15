#include "dados.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#define DATA_DIR "./dados/"

int arquivo_existe(const char* arquivo) {
    char caminho[256];
    snprintf(caminho, sizeof(caminho), "%s%s", DATA_DIR, arquivo);
    struct stat buffer;
    return (stat(caminho, &buffer) == 0);
}


FILE* abrir_csv(const char* arquivo, const char* modo, const char* header) {
    char caminho[256];
    snprintf(caminho, sizeof(caminho), "%s%s", DATA_DIR, arquivo);

    // Verifica se o arquivo já existe antes de abrir
    int novo_arquivo = !arquivo_existe(arquivo);

    FILE* f = fopen(caminho, modo);
    if (!f) {
        printf("Erro ao abrir arquivo %s\n", caminho);
        return NULL;
    }

    // Se o arquivo é novo e um cabeçalho foi fornecido, escreve-o
    if (novo_arquivo == 1 && header != NULL && strlen(header) > 0) {
        fprintf(f, "%s", header);
        fflush(f); // garante que o cabeçalho seja realmente gravado
    }

    return f;
}
