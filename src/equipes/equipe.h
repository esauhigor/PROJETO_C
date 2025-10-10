#ifndef EQUIPE_H
#define EQUIPE_H

typedef struct{
    int id;
    int id_hack;
    int id_mentor;
    char nome[50];
}Equipe;

//declare as funções aqui tipo "void cadastrar_equipe();", use o ponto e virgula no final, depois faça a logica no outro arquivo .c
void cadastrar_equipe();



#endif