#include "files.h"
#include "../../dados/dados.h"
#include "../../users/user.h"

#include <string.h>

int ultimo_id(const char *nome_arquivo){

    FILE *f = abrir_csv(nome_arquivo, "r");
    if (!f) return -2;

    char linha[256];
    int ultimo = -1;

    fgets(linha, sizeof(linha), f);
    
    while( fgets(linha, sizeof(linha), f) ){
        linha[strcspn(linha, "\n")] = '\0';
        int id;
        if (sscanf(linha, "%d,", &id) == 1){
            ultimo = id;
        }
    }
    fclose(f);
    return ultimo;
}

int verifica_cargo(int id, Cargo cargo){

    User *u_interno = procura_user(id);

    if (u_interno != NULL){
        if(u_interno->cargo == cargo){
            return 1;
        }
    }

    return 0;
}