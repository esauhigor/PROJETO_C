#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "auth/auth.h"
#include "utils/files/files.h"

int main() {
    setlocale(LC_ALL, "Portuguese"); // acentos no terminal

    char *t = "Ls18PoBwjcH09EB";

    Result r = validar_token(t);

    if (r.code == OK) {
        if (r.data) {
            Token *tok = r.data;
            printf("ID: %d\nNOME: %s\nTOKEN: %s\n\n", tok->id, tok->nome, tok->token);
            free(tok);
        } else {
            printf("r.data nulo\n");
        }
    } else {
        print_err(&r);
    }

    return 0;
}

