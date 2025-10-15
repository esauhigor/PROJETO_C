#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "users/user.h"
#include "equipes/equipe.h"
#include "utils/files/files.h"
#include "dados/dados.h"

// =====================================
// SIMULAÇÃO DE LOGIN
// =====================================
User* simular_login() {
    static User u;
    int opcao;

    printf("===== SIMULAÇÃO DE LOGIN =====\n");
    printf("1. ADMIN\n");
    printf("2. GERENTE\n");
    printf("3. PARTICIPANTE\n");
    printf("4. JURADO\n");
    printf("Escolha um tipo de usuário para testar: ");
    scanf("%d", &opcao);
    getchar();

    u.id = 1; // ID fixo apenas para simulação
    strcpy(u.nome, "UsuarioTeste");
    strcpy(u.senha, "123");
    
    switch (opcao) {
        case 1: u.cargo = ADMIN; break;
        case 2: u.cargo = GERENTE; break;
        case 3: u.cargo = PARTICIPANTE; break;
        case 4: u.cargo = JURADO; break;
        default: 
            printf("Opção inválida. Logando como PARTICIPANTE.\n");
            u.cargo = PARTICIPANTE;
    }

    printf("Usuário logado como: %s\n", cargo_pra_texto(u.cargo));
    return &u;
}

// =====================================
// FUNÇÃO PRINCIPAL
// =====================================
int main() {
    printf("===== SISTEMA DE HACKATHON =====\n");

    User *usuario_logado = simular_login();

    int opcao;
    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Menu de Equipes\n");
        printf("2. Sair\n");
        printf("Escolha: ");
        
        if (scanf("%d", &opcao) != 1) {
            int c; while ((c = getchar()) != '\n' && c != EOF) {}
            opcao = 0;
        }
        getchar();

        switch (opcao) {
            case 1:
                menu_equipes(usuario_logado);
                break;
            case 2:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 2);

    return 0;
}
