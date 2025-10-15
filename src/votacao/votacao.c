#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "votacao.h"
#include "../dados/dados.h"
#include "../users/user.h"
#include "../utils/files/files.h"

int verificar_votacao(int id){

    FILE *f = abrir_csv("votacao.csv");
    char linha[256];

    while (fgets(linha, sizeof(linha), f)){

        int id_vot, id_hack, control;
        if (sscanf(linha,"%d,%d,%d", &id_vot, &id_hack, &control) == 3 ){
            if (id_hack==id && control == 1){
            return 1;
            }
        }
        
    }
    fclose(f);
    return 0;

}

int aderir_jurados(){
    /*
    entradas:
    endereço de usuario, ou só o id dele.

    retorno: 
    um inteiro pra verificar se deu certo ou não.

    Essa função escreve no arquivo "jurados.csv", usando a função abrir_csv() e mandando o nome do arquivo e o modo como "a", temos que verificar se o id do usuario em questão é mentor ou jurado
    */
   return 1;
}

int abrir_votacao(Votacao *v){
    
    if (verificar_votacao(v->id_hack)){
        return 0;
    }

    FILE *f = escrever_no_csv("votacao.csv", "ID,ID_HACK,CONTROL,DATA,JURADOS\n");

    int id = ultimo_id("votacao.csv") +1;

    if ( id < 0){
        fclose(f);
        return 0;
    }

    fprintf(f, "%d,%d,%d,%d,%d\n", id, v->id_hack, v->control, v->data, v->jurados);

    printf("Print teste: abrir_votacao()");
    fclose(f);
    return 1;
}

void aderir_pontos(){
    /*
    use a função "abrir_csv("pontos.csv", "a")" ela vai abrir um arquivo e retornar um endereço  de FILE

    Função que acessa o arquivo “dados/votacao.csv” para verificar se existe alguma votação em aberto desse hackathon. Caso encontre, retorna a struct dessa votação e adiciona uma nova linha no arquivo “dados/pontos.csv” com os campos “id”, “id_equipe”, “id_hackathon”, “id_votacao”, “comentário” e “ponto”. Antes de inserir a linha, é necessário garantir que o usuário em questão seja um mentor, utilizando a função “verifica_cargo()”, verificar se o mentor ainda não votou, se já votou verificar se todos já votaram, pra mudar a flag da votação.

    */
   printf("Print teste: aderir_pontos()");
}

void fechar_votacao(){
    /*
    entrada:
    endereço de uma entidade de votacao 

    saida:
    inteiro como booleano

    Função vai no arquivo “dados/pontos.csv”, puxa a quantide de rows existente com o id da votação de entrada, equipara o campo "jurados" (é a quantidade de jurados dessa votação
    ), da entedidade de entrada com o quantidade de rows existente com esse id, se for igual ou superior 


    */
}