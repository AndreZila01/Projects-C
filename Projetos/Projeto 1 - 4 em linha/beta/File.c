#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

//
// Problemas em ler varias linhas do ficheiro, o que é ssize_t, o que é sprintf
//

struct Jogador
{
        char *Nome;
        int Vitoria;
        int Jogadas;
} jogador[50];

struct JogoAtivo
{
        int Tabuleiro[50][50];
        char *Jogador0;
        char *Jogador1;
        bool Jogando; // false - Por Inciar || true - A decorrer
} Ativo[1];

void WriteFile(char *Text)
{
        FILE *fptr;
        // https://stackoverflow.com/a/29510380/19921747
        if ((fptr = fopen("fprintf_test.txt", "r")) == NULL)
        {
                fptr = fopen("fprintf_test.txt", "w+");
                fclose(fptr);
        }
        char *buff;
        fptr = fopen("fprintf_test.txt", "r");
        ssize_t read;
        size_t len = 0;
        while ((read = getline(&buff, &len, fptr)) != -1)
        {
                strcpy(buff, read);
                printf("Retrieved line of length %zu:\n", read);
                printf("%s", buff);
        }

        fgets(buff, 100000, (FILE *)fptr);
        printf("%s\n", buff);
        fclose(fptr); // é necessário fazer fclose, tendo em conta que está só a ler??
        fptr = fopen("fprintf_test.txt", "w+");
        if (strcmp(buff, "\001") == 0)
                fprintf(fptr, "%s", Text);
        else
                fprintf(fptr, "%s\n%s", buff, Text);
        fclose(fptr);
}

int main()
{
        char *texto = NULL;
        FILE *fptr;
        jogador[0].Nome = "Andre";
        jogador[0].Vitoria = 0;
        jogador[0].Jogadas = 0;
        jogador[1].Nome = "Rui";
        jogador[1].Vitoria = 01;
        jogador[1].Jogadas = 10;
        jogador[2].Nome = "Pedro";
        jogador[2].Vitoria = 02;
        jogador[2].Jogadas = 02;
        jogador[3].Nome = "Cesar";
        jogador[3].Vitoria = 10;
        jogador[3].Jogadas = 10;
        jogador[4].Nome = "Juliana";
        jogador[4].Vitoria = 5;
        jogador[4].Jogadas = 5;
        jogador[5].Nome = "Rodrigo";
        jogador[5].Vitoria = 1;
        jogador[5].Jogadas = 1;
        jogador[6].Nome = "Bernardo";
        jogador[6].Vitoria = 0;
        jogador[6].Jogadas = 10;

       /**/ for (int count = 0; count < 7; count++)
        {
                printf("%s,%d,%d", jogador[count].Nome, jogador[count].Jogadas, jogador[count].Vitoria);
                texto = malloc(20000);
                sprintf(texto, "%s,%d,%d", jogador[count].Nome, jogador[count].Jogadas, jogador[count].Vitoria);

                WriteFile(texto);
                free(texto);
        }

        // strcpy(jogadores, ("%s,%d,%d", jogador[0].Nome, jogador[0].Jogadas, jogador[0].Vitoria));
        //  strcpy(jogadores, ("%s,%d,%d", *jogador[0].Nome, jogador[0].Jogadas, jogador[0].Vitoria));
        /* */

        // printf("%s", jogadores);

        /* int tabuleiro=0;
         for(int col=0; col<20; col++)
                 for(int lin=0; lin<20; lin++)
                         tabuleiro = lin<19 ? ("%c%d,",tabuleiro, Ativo[0].Tabuleiro[col][lin]) : ("%c%c\n",tabuleiro, Ativo[0].Tabuleiro[col][lin]); //Tabuleiro[col][lin] = 0;
         fptr = fopen("fprintf_test.txt", "w+");
         //fprintf(fptr, "%d\n%c\n%c\n%c\n%c\n%c", (sizeof jogador / sizeof jogador[0]), jogadores, tabuleiro, );
         fclose(fptr);*/
}