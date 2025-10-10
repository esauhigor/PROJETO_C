#ifndef HACKATHON.H
#define HACKATHON.H

#include<stdio.h>

typedef struct hackathon {
    int id;
    int data_inicio;
    int data_fim;
    char tema[50];
    int maximo;
    int votacao;
    char regras[100];
} Hackathon;

void criar_hackathon();

#endif