#include <stdio.h>
#include <stdbool.h>
#include <string.h>
struct Jogador {
    char Nome [50];
    int Vitoria;
    int Jogadas;
};

struct Jogador jogador [50];


void RegistarJog(){
    //strcpy(arr[idx].name, name);
    //strcpy(jogador[sizeof(jogador)/sizeof(jogador[0])].Nome, "Test");
    //printf(jogador[0].Nome);
}

int main()
{
    while (true)
    {
        //char cargo[300];
        char* cargo;
        fgets(cargo, 300, stdin);

        if (cargo[0] == 'R' && cargo[1] == 'J')
            RegistarJog();
        else if (cargo[0] == 'E' && cargo[1] == 'J')
            puts("Chefe");
        else if (cargo[0] == 'L' && cargo[1] == 'J')
            puts("operario");
        else if (cargo[0] == 'D')
            puts("inspetor");
        else if (cargo[0] == 'I' && cargo[1] == 'J')
            puts("inspetor");
        else if (cargo[0] == 'D' && cargo[1] == 'J')
            puts("mecanico");
        else if (cargo[0] == 'C' && cargo[1] == 'P')
            puts("mecanico");
        else if (cargo[0] == 'V' && cargo[1] == 'R')
            puts("mecanico");
        else if (cargo[0] == 'G')
            puts("mecanico");
        else if (cargo[0] == 'L')
            puts("mecanico");
        else
            puts("O valor inserido nao tem correspondencia.");

        /*char str[] = "Geeks for Geeks";
        char* token;
        char* rest = str;*/

        char *string;
        char *tofree;

        string = strdup(cargo);

        if (string != NULL)
            while ((tofree = strsep(&string, " ")) != NULL)
                printf("%s\n", tofree);
        
    }
}
