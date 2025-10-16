#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "users/user.h"

int main() {
    /*int qtd;
    User *admins = lista_users_por_cargo(PADRAO, &qtd);

    if (!admins) {
        printf("Nenhum usuário encontrado.\n");
        return 0;
    }

    printf("Usuários com cargo ADMIN:\n");
    for (int i = 0; i < qtd; i++) {
        printf("ID: %d, Nome: %s\n", admins[i].id, admins[i].nome);
    }

    free(admins); // sempre liberar memória*/

    singin();
    
    return 0;
}
