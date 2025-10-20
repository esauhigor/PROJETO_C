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
        printf("2. Vincular participante a equipe\n");
        printf("3. Voltar\n");
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
                vincular_participante(usuario_logado);
                break;
            case 3:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 3);
}

// ==============================
// CADASTRAR NOVA EQUIPE (Interface)
// ==============================
int cadastrar_equipe(User *usuario_logado) {
    if (!(usuario_logado->cargo == ADMIN || usuario_logado->cargo == GERENTE)) {
        printf("Acesso negado! Apenas ADMIN e GERENTE podem cadastrar equipes.\n");
        return 0;
    }

    Equipe e;

    FILE *f = escrever_no_csv("equipes.csv", "ID,ID_HACKATHON,ID_MENTOR,NOME_EQUIPE\n");
    if (!f) {
        printf("Erro ao abrir o arquivo de equipes.\n");
        return 0;
    }

    printf("\nDigite o nome da equipe: ");
    fgets(e.nome, sizeof(e.nome), stdin);
    e.nome[strcspn(e.nome, "\n")] = '\0';

    if (equipe_ja_existe(e.nome)) {
        printf("Erro: já existe uma equipe com o nome '%s'.\n", e.nome);
        fclose(f);
        return 0;
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
        return 0;
    }

    int ok = salvar_equipe(&e);
    fclose(f);

    if (ok) {
        printf("Equipe '%s' cadastrada com sucesso! (ID: %d)\n", e.nome, e.id);
        return 1;
    }

    printf("Erro ao salvar equipe.\n");
    return 0;
}

// ==============================
// SALVAR EQUIPE NO CSV
// ==============================
int salvar_equipe(Equipe *e) {
    FILE *f = escrever_no_csv("equipes.csv", "ID,ID_HACKATHON,ID_MENTOR,NOME_EQUIPE\n");
    if (!f) return 0;

    int ultimo = ultimo_id("equipes.csv"); 
    if (ultimo < 0) return 0;

    fprintf(f, "%d,%d,%d,%s\n", ultimo +1, e->id_hack, e->id_mentor, e->nome);
    fclose(f);
    return 1;
}


// ==============================
// VERIFICAR DUPLICIDADE DE EQUIPE
// ==============================
int equipe_ja_existe(const char *nome) {
    FILE *f = abrir_csv("equipes.csv");
    if (!f) return 0;

    char linha[256];
    int id, id_hack, id_mentor;
    char nome_existente[50];

    while (fgets(linha, sizeof(linha), f)) {
        linha[strcspn(linha, "\n")] = '\0';
        if (sscanf(linha, "%d,%d,%d,%49[^\n]", &id, &id_hack, &id_mentor, nome_existente) == 4) {
            if (strcmp(nome_existente, nome) == 0) {
                fclose(f);
                return 1;
            }
        }
    }

    fclose(f);
    return 0;
}

// ==============================
// PARTICIPANTE JÁ VINCULADO
// ==============================
int participante_ja_vinculado(int id_user) {
    FILE *f = abrir_csv("user_equipe.csv");
    if (!f) return 0;

    char linha[100];
    int id_equipe, id_part;
    while (fgets(linha, sizeof(linha), f)) {
        if (sscanf(linha, "%d,%d", &id_equipe, &id_part) == 2) {
            if (id_part == id_user) {
                fclose(f);
                return 1;
            }
        }
    }
    fclose(f);
    return 0;
}

// ==============================
// COLETAR DADOS PARA VÍNCULO
// ==============================
int coletar_vinculo_participante(int *id_equipe, int *id_user) {
    printf("\n===== VINCULAR PARTICIPANTE =====\n");

    printf("Digite o ID da equipe: ");
    if (scanf("%d", id_equipe) != 1) {
        int c; while ((c = getchar()) != '\n' && c != EOF) {}
        return 0;
    }
    getchar();

    printf("Digite o ID do participante: ");
    if (scanf("%d", id_user) != 1) {
        int c; while ((c = getchar()) != '\n' && c != EOF) {}
        return 0;
    }
    getchar();

    if (!verifica_cargo(*id_user, PARTICIPANTE)) {
        printf("Erro: o ID %d não pertence a um participante válido.\n", *id_user);
        return 0;
    }

    if (participante_ja_vinculado(*id_user)) {
        printf("Erro: o participante %d já está vinculado a uma equipe.\n", *id_user);
        return 0;
    }

    return 1;
}

// ==============================
// SALVAR VÍNCULO PARTICIPANTE↔EQUIPE
// ==============================
int salvar_vinculo_participante(int id_equipe, int id_user) {
    FILE *f = escrever_no_csv("user_equipe.csv", "ID_EQUIPE,ID_PARTICIPANTE\n");
    if (!f) {
        printf("Erro ao abrir user_equipe.csv\n");
        return 0;
    }

    fprintf(f, "%d,%d\n", id_equipe, id_user);
    fclose(f);
    return 1;
}

// ==============================
// CONTROLADOR: VINCULAR PARTICIPANTE
// ==============================
void vincular_participante(User *usuario_logado) {
    if (!(usuario_logado->cargo == ADMIN || usuario_logado->cargo == GERENTE)) {
        printf("Acesso negado! Apenas ADMIN e GERENTE podem vincular participantes.\n");
        return;
    }

    int id_equipe, id_user;
    if (!coletar_vinculo_participante(&id_equipe, &id_user)) {
        printf("Falha na coleta dos dados do vínculo.\n");
        return;
    }

    if (salvar_vinculo_participante(id_equipe, id_user)) {
        printf("Participante %d vinculado com sucesso à equipe %d!\n", id_user, id_equipe);
    } else {
        printf("Erro ao salvar vínculo no arquivo CSV.\n");
    }
}
