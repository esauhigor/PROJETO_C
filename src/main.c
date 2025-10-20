#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "users/user.h"
#include "equipes/equipe.h"
#include "auth/auth.h"


// Função principal
int main() {
    setlocale(LC_ALL, "Portuguese"); // acentos no terminal
    User u = {22,"higor",ADMIN, "1234"};

    cadastrar_user(&u);

    //singin();
    //login();


    
    return 0;
}
