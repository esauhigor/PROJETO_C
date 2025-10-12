#include <stdio.h>
#include "equipe.h"
#include "../utils/files/files.h"

void cadastrar_equipe(){
    int id = ultimo_id("hackathons.csv");
    printf("id hackathon: %d\n", id);
}