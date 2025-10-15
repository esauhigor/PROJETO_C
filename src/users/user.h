#ifndef USERS_H
#define USERS_H

typedef enum {
    ADMIN = 1,
    GERENTE = 2,
    PADRAO = 3,
    MENTOR = 4,
    JURADO = 5,
    PARTICIPANTE = 6,
    DESCONHECIDO = 7,
} Cargo;

typedef struct {
    int id;
    char nome[50];
    Cargo cargo;
    char senha[50];
} User;

Cargo int_pra_cargo(int valor);
const char* cargo_pra_texto(Cargo c);

User* procura_user(int id);
// essa função retorna NULL quando da erro

int cadastrar_user(User *u);
//essa função retorna 0 quando da erro

void cifrar();

int autenticar();
void login();



#endif