#include "user.h"
#include "../dados/dados.h"
#include "../utils/files/files.h"
#include "../utils/result/result.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define MIN_USERNAME_LEN 3
#define MAX_USERNAME_LEN 20

#define MIN_SENHA_LEN 6
#define MAX_SENHA_LEN 20

#define SHIFT_LETRA 3
#define SHIFT_NUMERO 4

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

int validar_username(const char *username) {
    int len = strlen(username);

    // comprimento mínimo e máximo
    if (len < MIN_USERNAME_LEN || len > MAX_USERNAME_LEN) {
        printf("O username deve ter entre %d e %d caracteres.\n",
               MIN_USERNAME_LEN, MAX_USERNAME_LEN);
        return 0;
    }

    // só permite letras, números e _
    int i;
    for (i = 0; i < len; i++) {
        if (!isalnum(username[i]) && username[i] != '_') {
            printf("O username só pode conter letras, números ou '_'.\n");
            return 0;
        }
    }

    return 1; // válido
}

int validar_senha(const char *senha) {
    int len = strlen(senha);
    int tem_letra = 0, tem_numero = 0, tem_especial = 0;

    // comprimento mínimo e máximo
    if (len < MIN_SENHA_LEN || len > MAX_SENHA_LEN) {
        printf("A senha deve ter entre %d e %d caracteres.\n", MIN_SENHA_LEN, MAX_SENHA_LEN);
        return 0;
    }

    int i;
    for (i = 0; i < len; i++) {
        if (isalpha(senha[i])) tem_letra = 1;
        else if (isdigit(senha[i])) tem_numero = 1;
        else if (strchr("!@#$%&*_-+=?.", senha[i])) tem_especial = 1; // caracteres especiais permitidos
        else {
            printf("Caractere inválido: '%c'\n", senha[i]);
            return 0;
        }
    }

    if (!tem_letra || !tem_numero || !tem_especial) {
        printf("A senha deve conter pelo menos uma letra, um numero e um caractere especial (!@#$%%&*_-+=.?).\n");
        return 0;
    }

    return 1; // válida
}

void cifra_idiota(char *senha) {
    while (*senha != '\0') {
        char c = *senha;

        if (isalpha(c)) {
            if (isupper(c))
                *senha = ((c - 'A' + SHIFT_LETRA) % 26) + 'A';
            else
                *senha = ((c - 'a' + SHIFT_LETRA) % 26) + 'a';
        }
        else if (isdigit(c)) {
            *senha = ((c - '0' + SHIFT_NUMERO) % 10) + '0';
        }
        else if (strchr("!@#$%&*_-+=?.", c)) {
            const char *especial = "!@#$%&*_-+=?.";
            int len = strlen(especial);
            const char *pos = strchr(especial, c);
            if (pos)
                *senha = especial[(pos - especial + 2) % len];
        }
        senha++;
    }
}

Result existe_nome(const char *username){
    FILE *f = abrir_csv("users.csv");
    char linha[256];

    if (!f){
        return erro(ERRO_ARQUIVO, "Erro ao abrir o arquivo users.csv!\n");
    }
    
    int id_lido;
    char nome[50];

    // Ignora o cabeçalho
    fgets(linha, sizeof(linha), f);

    while (fgets(linha, sizeof(linha), f)) {
        // CSV: ID,NOME,CARGO,SENHA
        if (sscanf(linha, "%d,%49[^,],", &id_lido, nome) == 2) {
            if (strcmp(username, nome) == 0) {
                fclose(f);
                return ok();
            }
        }
    }

    fclose(f);
    return erro(ERRO_LOGICA, "Usuario não existe\n");
}

Result cadastrar_user(User *u){
    FILE *f = escrever_no_csv("users.csv", "ID,NOME,CARGO,SENHA\n");

    if (f == NULL) return erro(ERRO_ARQUIVO, "erro ao abrir o arquivo users.csv");

    Result r = existe_nome(u->nome);
    if (r.code != OK) {
        return erro(r.code, r.msg);
    }
    //if ( u->cargo == NULL) u->cargo = PADRAO;
    int id = ultimo_id("users.csv")+1;


    fprintf(f,"%d,%s,%d,%s\n",id , u->nome, PADRAO,u->senha);

    fclose(f);
    u->id = id;
    return ok_data(u);
}

Result procura_user(int id){
    FILE *f = abrir_csv("users.csv");
    if (f == NULL) return erro(ERRO_ARQUIVO, "erro ao abrir o arquivo users.csv");
    char linha[256];

    int id_lido, cargo_lido;
    char nome[50], senha[50];

    // Ignora o cabeçalho
    fgets(linha, sizeof(linha), f);

    while (fgets(linha, sizeof(linha), f)) {
        // CSV: ID,NOME,CARGO,SENHA
        if (sscanf(linha, "%d,%49[^,],%d,%49[^\n]", &id_lido, nome, &cargo_lido, senha) == 4) {
            if (id_lido == id) {
                User *user = malloc(sizeof(User));
                if (user == NULL) {
                    fclose(f);
                    return erro(ERRO_MEMORIA, "Falha ao alocar memória para User");
                }
                user->id = id_lido;
                strcpy(user->nome, nome);
                user->cargo = int_pra_cargo(cargo_lido);
                strcpy(user->senha, senha);
                fclose(f);
                return ok_data(user);
            }
        }
    }

    fclose(f);
    return erro(ERRO_LOGICA, "Usuario não encontrado!\n");
}

User* lista_users_por_cargo(Cargo cargo, int *quantidade) {
    FILE *f = abrir_csv("users.csv");
    if (!f) return NULL;

    char linha[256];
    *quantidade = 0;
    User *lista = NULL;

    // Ignora cabeçalho
    fgets(linha, sizeof(linha), f);

    while (fgets(linha, sizeof(linha), f)) {
        int id_lido, cargo_lido;
        char nome[50], senha[50];

        if (sscanf(linha, "%d,%49[^,],%d,%49[^\n]", &id_lido, nome, &cargo_lido, senha) == 4) {
            if (int_pra_cargo(cargo_lido) == cargo) {
                User *tmp = realloc(lista, sizeof(User) * (*quantidade + 1));
                if (!tmp) {
                    free(lista);
                    fclose(f);
                    return NULL;
                }
                lista = tmp;
                lista[*quantidade].id = id_lido;
                strcpy(lista[*quantidade].nome, nome);
                lista[*quantidade].cargo = int_pra_cargo(cargo_lido);
                strcpy(lista[*quantidade].senha, senha);
                (*quantidade)++;
            }
        }
    }

    fclose(f);

    if (*quantidade == 0) {
        free(lista);
        return NULL;
    }

    return lista;
}
