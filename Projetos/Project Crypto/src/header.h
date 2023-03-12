#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

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

Date atodate(char *dateS){
    LstDate date = realloc(NULL, sizeof(Date));

    date->Ano = atoi(strtok(dateS, "-"));
    date->Mes = atoi(strtok(NULL, "-"));
    date->Dia = atoi(strtok(NULL, "-"));

    return *date;
}

void ReadFile(FILE *filename)
{
    char line[1000];

    fgets(line, sizeof(line), filename);
    LstCrypto Lstcry = realloc(NULL, sizeof(Crypto));
    
    int value = 0;
    while (fgets(line, sizeof(line), filename) != NULL)
    {
        LstCrypto cryp = (LstCrypto)malloc(sizeof(Crypto));
        printf("%s", line);
        char* date=NULL;

        date = strtok(line, ";");
        cryp->open = atof(strtok(NULL, ";"));
        cryp->high = atof(strtok(NULL, ";"));
        cryp->low = atof(strtok(NULL, ";"));
        cryp->close = atof(strtok(NULL, ";"));
        cryp->Volume = atoll(strtok(NULL, ";"));
        cryp->MarketCap = atof(strtok(NULL, ";"));
        value++;
        cryp->date = atodate(date);

        Lstcry = realloc(Lstcry, sizeof(Crypto) * value);
        Lstcry[value-1] = *cryp;
    }
    free(cryp);
}