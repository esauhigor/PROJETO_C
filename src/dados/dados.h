#ifndef DADOS_H
#define DADOS_H

#include <stdio.h>

FILE* abrir_csv(const char* arquivo, const char* modo);
FILE* escrever_no_csv(const char* arquivo, const char* header);

#endif
