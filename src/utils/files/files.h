#ifndef FILES_H
#define FILES_H

#include "../../users/user.h"
#include <stdio.h>

int ultimo_id(const char *nome_arquivo);
int verifica_cargo(int id, Cargo cargo);
void quicksort(int *lista[], int inicio, int fim);

FILE* abrir_csv(const char* arquivo, const char* modo);
FILE* escrever_no_csv(const char* arquivo, const char* header);

#endif
