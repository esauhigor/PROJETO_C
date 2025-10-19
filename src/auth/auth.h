#ifndef AUTH_H
#define AUTG_H

typedef struct {
    int id;
    char nome[50];
    char token[50];
}Token;

void singin();
// fluxo de cadastro de user


#endif