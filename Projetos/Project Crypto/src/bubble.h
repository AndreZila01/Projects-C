#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

LstCrypto BubbleSortM(LstCrypto array, int posicao[5])
{
    Crypto aux;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5 - 1; j++)
        {
            if (array[posicao[j]].close > array[posicao[j + 1]].close)
            {
                aux = array[posicao[j]];
                array[posicao[j]] = array[posicao[j + 1]];
                array[posicao[j + 1]] = aux;
            }
        }
    }
    return array;
}

LstCrypto BubbleSortm(LstCrypto array, int posicao[5])
{
    Crypto aux;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5 - 1; j++)
        {
            if (array[posicao[j]].close < array[posicao[j + 1]].close)
            {
                aux = array[posicao[j]];
                array[posicao[j]] = array[posicao[j + 1]];
                array[posicao[j + 1]] = aux;
                //as posições não são alteradas em nenhuma delas!!
            }
        }
    }
    return array;
}

LstCrypto BubbleSortdif(LstCrypto array, int posicao[5])
{
    Crypto aux;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5 - 1; j++)
        {
            if (array[posicao[j]].close < array[posicao[j + 1]].close)
            {
                aux = array[posicao[j]];
                array[posicao[j]] = array[posicao[j + 1]];
                array[posicao[j + 1]] = aux;
            }
        }
    }
    return array;
}