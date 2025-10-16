#ifndef EQUIPE_H
#define EQUIPE_H

#include "../users/user.h"

// Estrutura principal
typedef struct {
    int id;
    int id_hack;
    int id_mentor;
    char nome[50];
} Equipe;  

// Funções principais
void menu_equipes(User *usuario_logado);// Menu geral de equipes
int cadastrar_equipe(User *usuario_logado);// Cadastrar nova equipe
void listar_equipes();// Listar todas as equipes
void vincular_participante(User *usuario_logado);// Vincular participante a uma equipe existente
int participante_ja_vinculado(int id_user);// Verificar se participante já está em alguma equipe
int equipe_ja_existe(const char *nome);// Verificar duplicidade de nome de equipe

#endif
