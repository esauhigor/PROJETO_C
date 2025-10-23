#include <stdio.h>
#include <stdlib.h>
#include "result.h"

// ==========================================================
// Funções utilitárias para criar resultados
// ==========================================================

// Retorno de sucesso (sem mensagem)
Result ok() {
    return (Result){ OK, NULL, NULL};
}

// Retorno de sucesso com dados dinamicos de retorno
Result ok_data(void *data){
    return (Result){ OK, NULL, data};
}


// Retorno de erro com código e mensagem
Result erro(Res code, const char *msg) {
    return (Result){ code, msg, NULL};
}

// Imprime o erro no terminal
void print_err(Result *r){
    if (r->code != OK)
        printf("Erro (%d): %s\n", r->code, r->msg);
    else
        printf("Operação concluída com sucesso!\n");
        
}






/*
// ==========================================================
// EXEMPLOS DE USO
// ==========================================================

// 1️⃣ Exemplo simples — validar argumento
Result salvar_nome(const char *nome) {
    if (nome == NULL)
        return erro(ERRO_INVALIDO, "Nome não pode ser nulo");

    printf("Nome salvo: %s\n", nome);
    return ok();
}

// 2️⃣ Exemplo com arquivo — abrir um CSV
Result abrir_arquivo(const char *caminho) {
    FILE *f = fopen(caminho, "r");
    if (!f)
        return erro(ERRO_ARQUIVO, "Não foi possível abrir o arquivo");

    printf("Arquivo '%s' aberto com sucesso!\n", caminho);
    fclose(f);
    return ok();
}

// 4️⃣ Exemplo encadeado — função que chama outras
Result carregar_dados(void) {
    Result r;

    // Abrir arquivo
    r = abrir_arquivo("dados.csv");
    if (r.code != OK) return r;

    // Alocar memória
    r = alocar_memoria(1024);
    if (r.code != OK) return r;

    // Tudo certo
    return ok();
}
    */