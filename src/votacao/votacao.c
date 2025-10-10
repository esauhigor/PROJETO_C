#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "votacao.h"
#include "../dados/dados.h"

int verificar_votacao(){

    /*
    use a função "abrir_csv("votacao.csv", "r")" ela vai abrir um arquivo e retornar um FILE

    Essa função deve verificar se exite alguma votação em aberto, apartir de um id_hackathon que sera passado pra essa função e retornar 1 se true e 0 se false.
    Essa função deve abrir o aquivo "votacao.csv" e ir de row em row até finazilar o arquivo, procurando o id_hackathon e verificar o control

    notas higor: use ponteiros, sempre chamee outras funções passando o ponteiro de alguma coisa

    */

}

void aderir_jurados(){
    /*
    entradas:
    endereço de usuario, ou só o id dele.

    retorno: 
    um inteiro pra verificar se deu certo ou não.

    Essa função escreve no arquivo "jurados.csv", usando a função abrir_csv() e mandando o nome do arquivo e o modo como "a", temos que verificar se o id do usuario em questão é mentor ou jurado
    */
}

void abrir_votacao(){

    /*
    use a função "abrir_csv("votacao.csv", "a")" ela vai abrir um arquivo e retornar um endereço de FILE

    Função que cria uma nova linha no arquivo “dados/votacao.csv”, garantindo que não temos outra votação desse hackathon em aberto (Hackathon.control), se tiver erro, print uma descrição no terminal e retorne o id da votação em aberto.

    */

    printf("Print teste: abrir_votacao()");

}

void aderir_pontos(){
    /*
    use a função "abrir_csv("pontos.csv", "a")" ela vai abrir um arquivo e retornar um endereço  de FILE

    Função que acessa o arquivo “dados/votacao.csv” para verificar se existe alguma votação em aberto desse hackathon. Caso encontre, retorna o ID dessa votação e adiciona uma nova linha no arquivo “dados/pontos.csv” com os campos “id”, “id_equipe”, “id_hackathon”, “id_votacao”, “comentário” e “ponto”. Antes de inserir a linha, é necessário garantir que o usuário em questão seja um mentor, utilizando a função “verifica_cargo()”, verificar se o mentor ainda não votou, se já votou verificar se todos já votaram, pra mudar a flag da votação.

    */
   printf("Print teste: aderir_pontos()");
}