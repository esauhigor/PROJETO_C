#include "files.h"
#include "../../dados/dados.h"
#include "../../users/user.h"
#include "../../auth/auth.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


Result validar_token(char *t) {
    if (!t || strlen(t) == 0)
        return erro(ERRO_INVALIDO, "Token vazio!\nFN: validar_token()\n");

    FILE *f = abrir_csv("login.csv");
    if (!f)
        return erro(ERRO_ARQUIVO, "Erro ao abrir o arquivo\nFN: validar_token()\n");

    int id;
    char nome[50], token[50], linha[256];

    // Ignora cabeçalho
    fgets(linha, sizeof(linha), f);

    while (fgets(linha, sizeof(linha), f)) {
        if (sscanf(linha, "%d,%49[^,],%49[^\n]", &id, nome, token) == 3) {
            if (strcmp(token, t) == 0) {
                Token *tok = malloc(sizeof(Token));
                if (!tok) {
                    fclose(f);
                    return erro(ERRO_MEMORIA, "Erro ao alocar memória para o token\nFN: validar_token()\n");
                }

                tok->id = id;
                strcpy(tok->nome, nome);
                strcpy(tok->token, token);

                fclose(f);
                return ok_data(tok);
            }
        }
    }

    fclose(f);
    return erro(ERRO_LOGICA, "Token inválido!\nFN: validar_token()\n");
}


int ultimo_id(const char *nome_arquivo){

    FILE *f = abrir_csv(nome_arquivo);
    if (!f) return -1;

    char linha[256];
    int ultimo = -1;

    fgets(linha, sizeof(linha), f);
    
    while( fgets(linha, sizeof(linha), f) ){
        linha[strcspn(linha, "\n")] = '\0';
        int id;
        if (sscanf(linha, "%d,", &id) == 1){
            ultimo = id;
        }
    }
    fclose(f);
    return ultimo;
}

int verifica_cargo(int id, Cargo cargo){
    User *u_interno = (User*)procura_user(id).data;
    if (u_interno != NULL){
        if(u_interno->cargo == cargo){
            return 1;
        }
    }
    return 0;
}

void trocar(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int particionar(int *lista[], int inicio, int fim){
    int pivo = *lista[fim];
    int i = inicio - 1;

    int j;
    for (j = inicio; j < fim; j++) {
        if (*lista[j]< pivo){
            i++;
            trocar(lista[j], lista[i]);
        }
    }
    i++;
    trocar(lista[fim], lista[i]);
    return i;
}

void quicksort(int *lista[], int inicio, int fim){
    if(inicio >= fim) return;
    
    int indicePivo = particionar(lista, inicio, fim);
    quicksort(lista, inicio, indicePivo-1);
    quicksort(lista, indicePivo+1, fim);
}