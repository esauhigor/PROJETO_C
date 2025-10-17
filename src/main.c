#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "users/user.h"
#include "equipes/equipe.h"

// Função principal
int main() {
    setlocale(LC_ALL, "Portuguese"); // acentos no terminal

    singin();
    
    return 0;
}
