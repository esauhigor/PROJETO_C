#include <stdio.h>

#include "hackathons/hackathon.h"

int main(){

    Hackathon h = {1,20000,30000,"labe05",5,3,"não pode o que não pode!"};

    criar_hackathon(&h);
    printf("Tudo certo!");
    return 0;
}