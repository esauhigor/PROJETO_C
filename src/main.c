#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "users/user.h"
#include "equipes/equipe.h"

// Função principal
int main() {
    setlocale(LC_ALL, "Portuguese"); // acentos no terminal

    // Cria um usuário logado fictício (ADMIN)
    User usuario_logado;
    usuario_logado.id = 1;
    usuario_logado.cargo = ADMIN;
    snprintf(usuario_logado.nome, sizeof(usuario_logado.nome), "Administrador");

    printf("========================================\n");
    printf(" SISTEMA DE GESTÃO DE EQUIPES - TESTE \n");
    printf(" Usuário logado: %s (Cargo: ADMIN)\n", usuario_logado.nome);
    printf("========================================\n");

    // Chama o menu principal de equipes
    menu_equipes(&usuario_logado);

    printf("\nEncerrando o programa...\n");
    return 0;
}
