#include "hackathon.h"
#include "../dados/dados.h"

#include<stdio.h>
#include<string.h>


void criar_hackathon(Hackathon *evento){
    FILE *f = escrever_no_csv("hackathons.csv", "ID,DATA_INICIO,DATA_FIM,TEMA,MAXIMO,VOTACAO,REGRAS");

    if (!f){
        printf("erro\n");
    }


    fprintf(f, "%d,%d,%d,%s,%d,%d,%s\n", evento->id, evento->data_inicio, evento->data_fim, evento->tema, evento->maximo, evento->votacao, evento->regras);

    fclose(f);

}
