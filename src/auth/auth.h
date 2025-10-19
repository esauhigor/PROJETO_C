#ifndef AUTH_H
#define AUTG_H

#include "../utils/result/result.h"

typedef struct {
    int id;
    char nome[50];
    char token[50];
}Token;

void singin();
// fluxo de cadastro de user

Result login_usuario(const char *username, char *senha);


#endif