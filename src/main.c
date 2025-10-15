#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "users/user.h"
#include "equipes/equipe.h"
#include "utils/files/files.h"
#include "dados/dados.h"

int main(){
    User u = {0,"higor", ADMIN, "1234"};

    if (cadastrar_user(&u)){
        printf("Usuario cadastrado com sucesso!\n");
    }else{
        printf("Erro\n");
    }


    return 0;
}
