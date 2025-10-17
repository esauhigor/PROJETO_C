#ifndef EQUIPE_H
#define EQUIPE_H

#include "../users/user.h"

// ==============================
// ESTRUTURA PRINCIPAL
// ==============================
typedef struct {
    int id;
    int id_hack;
    int id_mentor;
    char nome[50];
} Equipe;

// ==============================
// FUNÇÕES DE MENU
// ==============================
void menu_equipes(User *usuario_logado);

// ==============================
// FUNÇÕES DE CADASTRO DE EQUIPE
// ==============================
int cadastrar_equipe(User *usuario_logado);
int salvar_equipe(const Equipe *e);
int equipe_ja_existe(const char *nome);

// ==============================
// FUNÇÕES DE VÍNCULO PARTICIPANTE-EQUIPE
// ==============================
void vincular_participante(User *usuario_logado);
int coletar_vinculo_participante(int *id_equipe, int *id_user);
int salvar_vinculo_participante(int id_equipe, int id_user);
int participante_ja_vinculado(int id_user);

#endif
