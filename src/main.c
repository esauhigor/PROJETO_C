#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "auth/auth.h"


// Função principal
int main() {
    setlocale(LC_ALL, "Portuguese"); // acentos no terminal


    singin();
    login();


    
    return 0;
}
