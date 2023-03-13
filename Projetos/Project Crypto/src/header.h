#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "bubble.h"

typedef struct
{
    int Dia;
    int Mes;
    int Ano;
} Date, *LstDate;

typedef struct
{
    Date date;
    float open;
    float high;
    float low;
    float close;
    long long Volume;
    double MarketCap;
} Crypto, *LstCrypto;

bool CheckFile(FILE *filename)
{
    if (filename != NULL)
        return true;
    else
        return false;
}

Date atodate(char *dateS)
{
    LstDate date = realloc(NULL, sizeof(Date));

    date->Ano = atoi(strtok(dateS, "-"));
    date->Mes = atoi(strtok(NULL, "-"));
    date->Dia = atoi(strtok(NULL, "-"));

    return *date;
}

int maior(LstCrypto Lstcry, int value);
int menor(LstCrypto Lstcry, int value);
int diferenca(LstCrypto Lstcry, int value);

void ReadFile(FILE *filename)
{
    char line[1000];

    fgets(line, sizeof(line), filename);
    LstCrypto Lstcry = realloc(NULL, sizeof(Crypto));

    int value = 0, soma;

    while (fgets(line, sizeof(line), filename) != NULL)
    {
        LstCrypto cryp = (LstCrypto)malloc(sizeof(Crypto));
        printf("%s", line);
        char *date = NULL;

        date = strtok(line, ";");
        cryp->open = atof(strtok(NULL, ";"));
        cryp->high = atof(strtok(NULL, ";"));
        cryp->low = atof(strtok(NULL, ";"));
        cryp->close = atof(strtok(NULL, ";"));
        cryp->Volume = atoll(strtok(NULL, ";"));
        cryp->MarketCap = atof(strtok(NULL, ";"));
        value++;
        soma += cryp->close;
        cryp->date = atodate(date);

        Lstcry = realloc(Lstcry, sizeof(Crypto) * value);
        Lstcry[value - 1] = *cryp;
    }
    printf("A media do valor no fim do mês foi %d", (soma / (sizeof(Lstcry) / sizeof(Crypto))));
    maior(Lstcry, value);
    menor(Lstcry, value);
    diferenca(Lstcry, value);
    free(Lstcry);
}

void maior(LstCrypto Lstcry, int value)
{
    int posicao[5] = {0, 1, 2, 3, 4};
    BubbleSort(Lstcry, posicao);

    for (int i = 4; i <= value; i++)
    {
        if (Lstcry[i].close > Lstcry[posicao[0]].close)
            for (int index = 0; index > 5; index++)
            {
                if (Lstcry[i].close > Lstcry[posicao[index]].close)
                {
                    posicao[index] = i;
                    BubbleSort(Lstcry, posicao);
                }
            }
    }
    printf("O maior preço é %f no dia %s\nO segundo maior preço é %f no dia %s\nO terceiro maior preço é %f no dia %s\nO quarto maior preço é %f no dia %s\nO quinto maior preço é %f no dia %s", Lstcry[posicao[0]].close, Lstcry[posicao[0]].date, Lstcry[posicao[1]].close, Lstcry[posicao[1]].date, Lstcry[posicao[2]].close, Lstcry[posicao[2]].date, Lstcry[posicao[3]].close, Lstcry[posicao[3]].date, Lstcry[posicao[4]].close, Lstcry[posicao[4]].date);
}

void maior(LstCrypto Lstcry, int value)
{
    int posicao[5] = {0, 1, 2, 3, 4};
    BubbleSortM(Lstcry, posicao);
    for (int i = 4; i <= value; i++)
    {
        if (Lstcry[i].close < Lstcry[posicao[4]].close)
            for (int index = 0; index < 5; index++)
            {
                if (Lstcry[i].close < Lstcry[posicao[index]].close)
                {
                    posicao[index] = i;
                    BubbleSort(Lstcry, posicao);
                }
            }
    }
    printf("O maior preço é %f no dia %s\nO segundo maior preço é %f no dia %s\nO terceiro maior preço é %f no dia %s\nO quarto maior preço é %f no dia %s\nO quinto maior preço é %f no dia %s", Lstcry[posicao[0]].close, Lstcry[posicao[0]].date, Lstcry[posicao[1]].close, Lstcry[posicao[1]].date, Lstcry[posicao[2]].close, Lstcry[posicao[2]].date, Lstcry[posicao[3]].close, Lstcry[posicao[3]].date, Lstcry[posicao[4]].close, Lstcry[posicao[4]].date);
}

void diferenca(LstCrypto Lstcry, int value)
{
    int posicao[5] = {0, 1, 2, 3, 4};
    BubbleSortm(Lstcry, posicao);

    for (int i = 4; i <= value; i++)
    {
        if (Lstcry[i].close < Lstcry[posicao[0]].close)
            for (int index = 0; index < 5; index++)
            {
                if (Lstcry[i].close < Lstcry[posicao[index]].close)
                {
                    posicao[index] = i;
                    BubbleSort(Lstcry, posicao);
                }
            }
    }
}