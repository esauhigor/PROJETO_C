#ifndef AUTH_H
#define AUTH_H

#include "../utils/result/result.h"

typedef struct {
    int id;
    char nome[50];
    char token[32];
} Token;

Result login_usuario(const char *username, char *senha);
Result autenticar(const char *username, char *senha);
Result criar_token(int id);
Result adicionar_token(Token *t);
void singin();
void login();

#endif
