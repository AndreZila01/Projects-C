#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int tabuleiro[20][20];

char *Jogador1 = "Jogador1";

char *ColocarPeca(int numbjogador, int coluna, char *sentido, int tamanhopeca)
{

    // int col = strcmp(sentido, "D") == 0 : col = (sizeof tabuleiro / sizeof tabuleiro[0][0])-coluna : col = coluna;
    int col = -1;
    if (strcmp(sentido, "D") == 0)
        col = (sizeof tabuleiro / sizeof tabuleiro[0][0]) - coluna;
    else
        col = coluna;
    int linha = -1;
    for (int count = 0; count < (sizeof tabuleiro / sizeof tabuleiro[0][0]); count++)
        if (tabuleiro[count][col] == -1 || tabuleiro[count][col] == 0)
        {
            tabuleiro[count][col] = numbjogador;
            break;
        }
}

bool CheckWin(int numjogador)
{
    char *comb[400];
    int count = 0;
    // Compara 0x0, 0x1, 0x2, 0x3, 0x4 ...
    for (int col = 0; col < 21; col++)
        for (int lin = 0; lin < 21; lin++)
            if (tabuleiro[col][lin] == numjogador)
            {
                comb[count] = "%s,%s", col, lin;
                count++;
            }

    int linhaigual = 0;
    for (int value = 0; value <= (sizeof comb / sizeof comb[0]); value)
    {
        if (value != 0)
        {
            int c0 = atoi(strtok(comb[count--], ','));
            int l0 = atoi(strtok(NULL, ','));

            if (atoi(strtok(comb[value--], ',')) == c0 && atoi(strtok(NULL, ',')) + 1 == l0)
                linhaigual++;
        }
    }

    // Compara 0x0, 1x0, 2x0, 3x0, 4x0, ...
    for (int col = 0; col < 21; col++)
        for (int lin = 0; lin < 21; lin++)
            if (tabuleiro[lin][col] == numjogador)
            {
                comb[count] = "%s,%s", lin, col;
                count++;
            }

    int colungual = 0;
    for (int value = 0; value <= (sizeof comb / sizeof comb[0]); value)
    {
        if (value != 0)
        {
            int c0 = atoi(strtok(comb[count--], ','));
            int l0 = atoi(strtok(NULL, ','));

            if (atoi(strtok(comb[value--], ',')) == c0 && atoi(strtok(NULL, ',')) + 1 == l0)
                colungual++;
        }
    }

    if (linhaigual == 3 || colungual == 3)
    {
    }
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
            tabuleiro[0][0] = 1;
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