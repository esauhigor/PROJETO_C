#ifndef VOTACAO_H
#define VOTACAO_H

typedef struct votacao{
    int id;         //id da votação
    int id_hack;    //id hackathon
    int control;    //controla se a votação ainda é valida true significa que terminou
    int data;       //data de abertura da votação
    int jurados;    //quantidade de jurados
}Votacao;

typedef struct jurado{
    int id_user;    //id do usuario
    int id_votacao; //id da votação
}Jurado;

int verificar_votacao(int id);
int aderir_jurados();

int abrir_votacao(Votacao *v);
void aderir_pontos();



#endif