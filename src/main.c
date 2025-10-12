#include <stdio.h>

#include "hackathons/hackathon.h"
#include "equipes/equipe.h"
#include "users/user.h"
#include "utils/files/files.h"

int main(){

    int r = verifica_cargo(0, ADMIN);
    printf("resultado %d\n", r);

    return 0;
}
