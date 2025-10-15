#include "user.h"
#include "../dados/dados.h"
#include "../utils/files/files.h"

#include <stdio.h>
#include <string.h>

Cargo int_pra_cargo(int valor) {
    switch (valor) {
        case 1: return ADMIN;
        case 2: return GERENTE;
        case 3: return PADRAO;
        case 4: return MENTOR;
        case 5: return JURADO;
        case 6: return PARTICIPANTE;
        default: return DESCONHECIDO;
    }
}

Cargo cargo_pra_int(int valor) {
    switch (valor) {
        case 1: return ADMIN;
        case 2: return GERENTE;
        case 3: return PADRAO;
        case 4: return MENTOR;
        case 5: return JURADO;
        case 6: return PARTICIPANTE;
        default: return DESCONHECIDO;
    }
}

const char* cargo_pra_texto(Cargo c) {
    switch (c) {
        case ADMIN: return "ADMIN";
        case GERENTE: return "GERENTE";
        case PADRAO: return "PADRAO";
        case MENTOR: return "MENTOR";
        case JURADO: return "JURADO";
        case PARTICIPANTE: return "PARTICIPANTE";
        default: return "DESCONHECIDO";
    }
}

int cadastrar_user(User *u){
    FILE *f = escrever_no_csv("users.csv", "ID,NOME,CARGO,SENHA\n");

    if (f == NULL) return 0;

    fprintf(f,"%d,%s,%d,%s\n",ultimo_id("users.csv")+1, u->nome, u->cargo,u->senha);

    fclose(f);
    return 1;
}

User* procura_user(int id){
    FILE *f = abrir_csv("users.csv");
    char linha[256];
    
    static User user;
    int id_lido, cargo_lido;
    char nome[50], senha[50];

    // Ignora o cabeçalho
    fgets(linha, sizeof(linha), f);

    while (fgets(linha, sizeof(linha), f)) {
        // CSV: ID,NOME,CARGO,SENHA
        if (sscanf(linha, "%d,%49[^,],%d,%49[^\n]", &id_lido, nome, &cargo_lido, senha) == 4) {
            if (id_lido == id) {
                user.id = id_lido;
                strcpy(user.nome, nome);
                user.cargo = int_pra_cargo(cargo_lido);
                strcpy(user.senha, senha);
                fclose(f);
                return &user;
            }
        }
    }

    fclose(f);
    return NULL;
}