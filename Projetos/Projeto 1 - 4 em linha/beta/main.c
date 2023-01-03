#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int tabuleiro[20][20];

char *Jogador1 = "Jogador1";

bool CheckWin(int numjogador, int coluna, int linha, char *sentido)
{

    int linhaigual = 0;
    for (int value = linha - 4; value <= linha + 4; value++)
    {
        if (linha > 19)
            break;
        if (linha > -1)
        {
            if (tabuleiro[coluna][value] == numjogador)
                linhaigual++;
            else
                linhaigual = 0;

            if (linhaigual == 4)
            {
                printf("Acabou o jogo\n");
                break;
            }
        }
    }

    for (int value = coluna - 4; value <= coluna + 4; value++)
    {
        if (coluna > 19)
            break;

        if (coluna > -1)
        {
            if (tabuleiro[value][linha] == numjogador)
                linhaigual++;
            else
                linhaigual = 0;

            if (linhaigual == 4)
            {
                printf("Acabou o jogo\n");
                break;
            }
        }
    }

    for (int value = -4; value <= 4; value++)
    {
        if (coluna + value > 19 & linha + value > 19)
            break;
        if (coluna + value > -1 && linha + value > -1)
        {
            if (tabuleiro[coluna + value][linha + value] == numjogador)
                linhaigual++;
            else
                linhaigual = 0;

            if (linhaigual == 4)
            {
                printf("Acabou o jogo\n");
                break;
            }
        }
    }
    for (int value = 0; value <= 6; value++)
    {
        if (tabuleiro[coluna - value][linha - value] == numjogador)
            linhaigual++;
        else
            linhaigual = 0;

        if (linhaigual == 3)
        {
            printf("Acabou o jogo\n");
            break;
        }
    }
}

char *ColocarPeca(int numbjogador, int coluna, char *sentido, int tamanhopeca)
{

    // int col = strcmp(sentido, "D") == 0 : col = (sizeof tabuleiro / sizeof tabuleiro[0][0])-coluna : col = coluna;
    int col = -1;
    if (strcmp(sentido, "D") == 0)
        col = 20 - coluna;
    else
        col = coluna;
    int linha = -1;
    for (int count = 19; count < 20; count--)
        if (tabuleiro[col][count] == -1 || tabuleiro[col][count] == 0)
        {
            tabuleiro[col][count] = numbjogador;
            linha = count;
            break;
        }

    bool s = CheckWin(numbjogador, col, linha, sentido);
}

int main()
{
    while (true)
    {
        char *line = NULL;
        size_t len = 0;
        getline(&line, &len, stdin);
        const char *text = line;
        line[strlen(line) - 1] = '\0';
        char *comando = strtok(line, " ");
        if (strcmp(comando, "CP") == 0)
        {
            tabuleiro[1][1] = 1;
            tabuleiro[2][2] = 1;
            tabuleiro[3][3] = 1;

            char *jogador = strtok(NULL, " ");
            int tamanho = atoi(strtok(NULL, " "));
            int coluna = atoi(strtok(NULL, " "));
            char *sentido = strtok(NULL, " ");

            /*int numb = strcmp(jogador,Jogador1)==0 ? numb = 0 : numb = 1;*/
            int numb = 0;

            if (strcmp(jogador, Jogador1) == 0)
                numb = 0;
            else
                numb = 1;

            ColocarPeca(numb, coluna, sentido, tamanho);
        }
    }
}
