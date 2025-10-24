#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "auth.h"
#include "../users/user.h"
#include "../dados/dados.h"
#include "../utils/result/result.h"



Result login_usuario(const char *username, char *senha) {
    Result r = autenticar(username, senha);
    if (r.code != OK)
        return r;

    Token *t = malloc(sizeof(Token));
    if (!t)
        return erro(ERRO_MEMORIA, "Falha ao alocar memória para Token");

    // Copia dados do usuário autenticado
    Token *user = r.data;
    t->id = user->id;
    strcpy(t->nome, user->nome);
    free(user);

    // Cria token
    Result rtoken = criar_token(t->id);
    if (rtoken.code != OK) {
        free(t);
        return rtoken;
    }
    strcpy(t->token, rtoken.data);
    free(rtoken.data);

    // Salva no CSV
    Result radd = adicionar_token(t);
    if (radd.code != OK) {
        free(t);
        return radd;
    }

    return ok_data(t);
}

Result autenticar(const char *username, char *senha){
    FILE *f = abrir_csv("users.csv");

    if (!f)
        return erro(ERRO_ARQUIVO, "Erro ao abrir o arquivo users.csv!\n");
    

    char linha[256];
    int id_lido, cargo_lido;
    char nome[50], senha_lido[50];
    
    // Ignora o cabeçalho
    fgets(linha, sizeof(linha), f);

    while (fgets(linha, sizeof(linha), f)) {
        if (sscanf(linha, "%d,%49[^,],%d,%49[^\n]", &id_lido, nome, &cargo_lido, senha_lido) == 4) {
            if (strcmp(username, nome) == 0) {
                fclose(f);
                cifra_idiota(senha);

                if (strcmp(senha_lido, senha) != 0)
                    return erro(ERRO_LOGICA, "Senha incorreta!\n");
                

                Token *t = malloc(sizeof(Token));
                    if (t == NULL) {
                        return erro(ERRO_MEMORIA, "Falha ao alocar memória para User\n");
                    }
                strcpy(t->nome, nome);
                t->id = id_lido;
                //falta colocar o token dentro de login
        
                return ok_data(t);
            }
        }
    }

    fclose(f);
    return erro(ERRO_LOGICA, "Username incorreto!\n");
}

//função criada pelo chat pra gerar tokens
Result criar_token(int id) {
    if (!id) return erro(ERRO_INVALIDO, "User nulo");

    char *token = malloc(16); // 15 caracteres + '\0'
    if (!token) return erro(ERRO_MEMORIA, "Falha ao alocar memória para token");

    const char caracteres[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int tamanho = sizeof(caracteres) - 1;

    // Semente estática, inicializada apenas na primeira chamada
    static int rand_inicializado = 0;
    if (!rand_inicializado) {
        srand((unsigned int)(time(NULL) ^ clock()));
        rand_inicializado = 1;
    }

    // Mistura id do usuário, timestamp e rand() para maior unicidade
    unsigned int mix = (unsigned int)(id ^ time(NULL) ^ clock());

    for (int i = 0; i < 15; i++) {
        mix = (mix * 1664525 + 1013904223) % 0xFFFFFFFF; // LCG simples
        token[i] = caracteres[mix % tamanho];
    }
    token[15] = '\0';

    return ok_data(token);
}

Result adicionar_token(Token *t){
    if (!t)
        return erro(ERRO_INVALIDO, "Token nulo\n");

    FILE *f = escrever_no_csv("login.csv", "ID_USER,NOME,TOKEN");

    if (!f)
        return erro(ERRO_ARQUIVO, "Erro ao abrir login.csv\n");

    if (fprintf(f, "%d,%s,%.16s\n", t->id,t->nome, t->token) < 0) {
        fclose(f);
        return erro(ERRO_ARQUIVO, "Erro ao escrever em login.csv\n");
    }

    fclose(f);
    return ok();
}


void singin() {
    User e;

    // Leitura e validação do username
    printf("###Cadastro ###\n");
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
    
    cifra_idiota(e.senha);

    Result r = cadastrar_user(&e);

    if (r.code == OK) {
        printf("Usuário criado: %s (%s)\n", e.nome, cargo_pra_texto(e.cargo));
    } else {
        print_err(&r);
    }

}

void login() {
    char nome[50], senha[50]; // sem const!

    // Leitura e validação do username
    printf("###Login###\n");
    while (1) {
        
        printf("Username: ");
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = '\0';

        if (validar_username(nome)) break; // válido -> sai do loop
        printf("Tente novamente.\n\n");
    }

    // Leitura e validação da senha
    while (1) {
        printf("Senha: ");
        fgets(senha, sizeof(senha), stdin);
        senha[strcspn(senha, "\n")] = '\0';

        if (validar_senha(senha)) break; // válido -> sai do loop
        printf("Tente novamente.\n\n");
    }

    Result r = login_usuario(nome, senha);
    
    if (r.code == OK) {
        Token *t = (Token *) r.data;  // converte void* para Token*
        printf("Login realizado com sucesso: %s (ID: %d, Token: %s)\n", t->nome, t->id, t->token);
        free(t);
    } else {
        print_err(&r);
    }
}