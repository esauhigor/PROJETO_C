#include "user.h"
#include "../dados/dados.h"
#include "../utils/files/files.h"

#include <stdio.h>
#include <string.h>

#define MIN_USERNAME_LEN 3
#define MAX_USERNAME_LEN 20

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
    for (int i = 0; i < len; i++) {
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

    for (int i = 0; i < len; i++) {
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

void singin() {
    User e;

    // Leitura e validação do username
    while (1) {
        printf("Username: ");
        fgets(e.nome, sizeof(e.nome), stdin);
        e.nome[strcspn(e.nome, "\n")] = '\0';

        if (validar_username(e.nome)) break; // válido -> sai do loop
        printf("Tente novamente.\n\n");
    }

    // Leitura da senha
    while(1){
    printf("Senha: ");
    fgets(e.senha, sizeof(e.senha), stdin);
    e.senha[strcspn(e.senha, "\n")] = '\0';

    if (validar_senha(e.senha)) break; // válido -> sai do loop
        printf("Tente novamente.\n\n");
    }


    e.cargo = PADRAO;

    if (cadastrar_user(&e)) {
        printf("✅ Cadastrado com sucesso!\n");
    } else {
        printf("❌ Erro ao cadastrar.\n");
    }

    printf("Usuário criado: %s (%s)\n", e.nome, cargo_pra_texto(e.cargo));
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