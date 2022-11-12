#include <stdio.h>
#include <stdbool.h>
#include <string.h>

char *espacamento(char texto[], const char caract[1])
{
    return strtok_r(texto, caract, &texto);
}

int main()
{
    char cargo[150];
    fgets(cargo, 150, stdin);

    if (cargo[0] == 'E' && cargo[1] == 'J')
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
    {
        while ((tofree = strsep(&string, " ")) != NULL)
        {
            printf("%s\n", tofree);
        }
    }
}
