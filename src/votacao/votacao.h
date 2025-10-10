#ifndef VOTACAO_H
#define VOTACAO_H

typedef struct votacao{
    int id;
    int id_hack;
    int data;
    int control;
    int jurados;
}Votacao;

int verificar_votacao();
int aderir_jurados();

void abrir_votacao();
void aderir_pontos();



#endif