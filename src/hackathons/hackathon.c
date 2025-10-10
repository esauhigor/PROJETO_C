#include "hackathon.h"
#include "../dados/dados.h"

#include<stdio.h>
#include<string.h>


void criar_hackathon(Hackathon *evento){
    FILE *f = abrir_csv("hackathons.csv", "a");

    if (ftell(f) == 0){
        fprintf(f, "ID,DATA_INICIO,DATA_FIM,TEMA,MAXIMO,VOTACAO,REGRAS\n");
    }
    fprintf(f, "%d,%d,%d,%s,%d,%d,%s\n", evento->id, evento->data_inicio, evento->data_fim, evento->tema, evento->maximo, evento->votacao, evento->regras);

    fclose(f);

}
