#include "equipe.h"
#include "../users/user.h" 
#include "../utils/files/files.h"
#include "../dados/dados.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==============================
// MENU DE EQUIPES
// ==============================
void menu_equipes(User *usuario_logado) {
    int opcao;

    do {
        printf("\n===== MENU DE EQUIPES =====\n");
        printf("1. Cadastrar nova equipe\n");
        printf("2. Listar equipes desativada\n");
        printf("3. Vincular participante a equipe\n");
        printf("4. Voltar\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) {
            int c; while ((c = getchar()) != '\n' && c != EOF) {}
            opcao = 0;
        }
        getchar(); // limpa buffer

        switch (opcao) {
            case 1:
                cadastrar_equipe(usuario_logado);
                break;
            case 2:
                //listar_equipes();
                printf("Funcao listar equipes desativada\n");
                break;
            case 3:
                vincular_participante(usuario_logado);
                break;
            case 4:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 4 && opcao != 3);
}


// ==============================
// CADASTRAR NOVA EQUIPE
// ==============================
void cadastrar_equipe(User *usuario_logado) {
    if (!(usuario_logado->cargo == ADMIN || usuario_logado->cargo == GERENTE)) {
        printf("Acesso negado! Apenas ADMIN e GERENTE podem cadastrar equipes.\n");
        return;
    }

    int ultimo = ultimo_id("equipes.csv");
    if (ultimo < 0) ultimo = 0;

    FILE *f = abrir_csv("equipes.csv", "a+");
    if (!f) {
        printf("Erro ao abrir o arquivo de equipes.\n");
        return;
    }

    // Adiciona cabeçalho se o arquivo estiver vazio
    fseek(f, 0, SEEK_END);
    long tamanho = ftell(f);
    if (tamanho == 0) {
        fprintf(f, "ID,ID_HACKATHON,ID_MENTOR,NOME_EQUIPE\n");
    }

    Equipe e;
    e.id = ultimo + 1;

    printf("\nDigite o nome da equipe: ");
    fgets(e.nome, sizeof(e.nome), stdin);
    e.nome[strcspn(e.nome, "\n")] = '\0';

    if (equipe_ja_existe(e.nome)) {
        printf("Erro: já existe uma equipe com o nome '%s'.\n", e.nome);
        fclose(f);
        return;
    }

    printf("Digite o ID do hackathon: ");
    scanf("%d", &e.id_hack);
    getchar();
    
    printf("Digite o ID do mentor: ");
    scanf("%d", &e.id_mentor);
    getchar();

    if (!verifica_cargo(e.id_mentor, MENTOR)) {
        printf("Erro: o ID %d não corresponde a um mentor válido.\n", e.id_mentor);
        fclose(f);
        return;
    }

    fprintf(f, "%d,%d,%d,%s\n", e.id, e.id_hack, e.id_mentor, e.nome);
    fclose(f);

    printf("Equipe '%s' cadastrada com sucesso! (ID: %d)\n", e.nome, e.id);
}
/* Listar_equipes desativada
// LISTAR TODAS AS EQUIPES
// ==============================
void listar_equipes() {
    FILE *f = abrir_csv("equipes.csv", "r");
    if (!f) {
        printf("Nenhuma equipe cadastrada.\n");
        return;
    }

    char linha[256];
    printf("\n===== LISTA DE EQUIPES =====\n");
    printf("%-5s | %-10s | %-10s | %-20s\n", "ID", "Hack", "Mentor", "Nome");
    printf("------------------------------------------------------\n");

    while (fgets(linha, sizeof(linha), f)) {
        linha[strcspn(linha, "\n")] = '\0';
        int id, id_hack, id_mentor;
        char nome[50];

        if (sscanf(linha, "%d,%d,%d,%49[^\n]", &id, &id_hack, &id_mentor, nome) == 4) {
            printf("%-5d | %-10d | %-10d | %-20s\n", id, id_hack, id_mentor, nome);
        }
    }

    fclose(f);
}*/
// =====================================
// Verifica se participante já está em alguma equipe
// =====================================
int participante_ja_vinculado(int id_user) {
    FILE *f = abrir_csv("user_equipe.csv", "r");
    if (!f) return 0; // se não existir ainda não tem ue kkk

    char linha[100];
    int id_equipe, id_part;
    while (fgets(linha, sizeof(linha), f)) {
        if (sscanf(linha, "%d,%d", &id_equipe, &id_part) == 2) {
            if (id_part == id_user) {
                fclose(f);
                return 1; // já está em alguma equipe
            }
        }
    }
    fclose(f);
    return 0;
}
// =====================================
// Vincular participante a equipe
// =====================================
void vincular_participante(User *usuario_logado) {
    // apenas ADMIN ou GERENTE podem fazer isso
    if (!(usuario_logado->cargo == ADMIN || usuario_logado->cargo == GERENTE)) {
        printf("Acesso negado! Apenas ADMIN e GERENTE podem vincular participantes.\n");
        return;
    }

    int id_equipe, id_user;
    printf("\nDigite o ID da equipe: ");
    scanf("%d", &id_equipe);
    getchar();

    printf("Digite o ID do participante: ");
    scanf("%d", &id_user);
    getchar();

    // verifica se participante é valido
    if (!verifica_cargo(id_user, PARTICIPANTE)) {
        printf("Erro: o ID %d não pertence a um participante válido.\n", id_user);
        return;
    }

    // Verifica se já está em alguma equipe
    if (participante_ja_vinculado(id_user)) {
        printf("O participante %d já está vinculado a uma equipe!\n", id_user);
        return;
    }

FILE *f = abrir_csv("user_equipe.csv", "a+");
if (!f) {
    printf("Erro ao abrir user_equipe.csv\n");
    return;
}

// Verifica se o arquivo está vazio para inserir cabeçalho
fseek(f, 0, SEEK_END);
long tamanho = ftell(f);
if (tamanho == 0) {
    fprintf(f, "id_equipe,id_participante\n");
}

fprintf(f, "%d,%d\n", id_equipe, id_user);
fclose(f);

printf("Participante %d vinculado com sucesso à equipe %d!\n", id_user, id_equipe);

}
// =====================================
// Verifica duplicidade de equipe
// =====================================
    int equipe_ja_existe(const char *nome) {
        FILE *f = abrir_csv("equipes.csv", "r");
        if (!f) return 0; // se não existir o arquivo não tem duplicidade

        char linha[256];
        int id, id_hack, id_mentor;
        char nome_existente[50];

        while (fgets(linha, sizeof(linha), f)) {
            linha[strcspn(linha, "\n")] = '\0';
            if (sscanf(linha, "%d,%d,%d,%49[^\n]", &id, &id_hack, &id_mentor, nome_existente) == 4) {
                if (strcmp(nome_existente, nome) == 0) {
                    fclose(f);
                    return 1; // nome de equipe já existe
                }
            }
        }  
        fclose(f);
        return 0;// não encontrado
    }