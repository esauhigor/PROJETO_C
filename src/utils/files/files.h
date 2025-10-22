#ifndef FILES_H
#define FILES_H

#include "../../users/user.h"
#include "../result/result.h"

#include <stdio.h>


Result validar_token(char *t);
int ultimo_id(const char *nome_arquivo);
int verifica_cargo(int id, Cargo cargo);
void quicksort(int *lista[], int inicio, int fim);


#endif
