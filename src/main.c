#include <stdio.h>

#include "hackathons/hackathon.h"
#include "equipes/equipe.h"
#include "users/user.h"
#include "utils/files/files.h"

int main(){
    User *u = procura_user(0);

    int r = verifica_cargo(0, PADRAO);
    printf("resultado %d\n", r);
    if ( u != NULL){
        printf("%s: %s", u->nome, cargo_pra_texto(u->cargo));
    }else{
        printf("Sem user!\n");
    }
    

    return 0;
}
