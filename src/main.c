#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "auth/auth.h"
#include "utils/files/files.h"

int main() {
    setlocale(LC_ALL, "Portuguese"); // acentos no terminal

    login();

    return 0;
}

