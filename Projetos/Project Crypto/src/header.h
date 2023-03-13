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

Date atodate(char *dateS)
{
    LstDate date = realloc(NULL, sizeof(Date));

    date->Ano = atoi(strtok(dateS, "-"));
    date->Mes = atoi(strtok(NULL, "-"));
    date->Dia = atoi(strtok(NULL, "-"));

    return *date;
}

int compare_highest_close(void* a, void* b);
int compare_lowest_close(void* a, void* b);
void sort(void** records, int num_records, int (*cmp)(void*, void*));



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
        //fazer a valorizacao
        soma += cryp->close;
        cryp->date = atodate(date);

        Lstcry = realloc(Lstcry, sizeof(Crypto) * value);
        Lstcry[value - 1] = *cryp;
    }
    printf("A media do valor no fim do mês foi %ld", (soma/(sizeof(Lstcry) / sizeof(Crypto))));
    sort(Lstcry, value, compare_highest_close);
    sort(Lstcry, value, compare_lowest_close);
    free(Lstcry);
}

int compare_highest_close(void* a, void* b) {
    Crypto r1 = a;
    Crypto r2 = b;
    return r1->close - r2->close;
}

int compare_lowest_close(void* a, void* b) {
    Crypto r1 = a;
    Crypto r2 = b;
    return r2.close - r1.close;
}

int compare_dates(void* a, void* b) {
    Crypto r1 =  a;
    Crypto r2 =  b;
    if(r1->date->Ano == r2->date->Ano) {
        if(r1->date->mes == r2->date->mes) {
            return r1->date->dia - r2->date->dia;
        }
        return r1->date->mes - r2->date->mes;
    }
    return r1->date->Ano - r2->date->Ano;
}

void sort(void** records, int num_records, int (*cmp)(void*, void*)) {
    for(int i = 0; i < num_records; i++) {
        for(int j = i + 1; j < num_records; j++) {
            if(cmp(records[i], records[j]) > 0) {
                void* tmp = records[i];
                records[i] = records[j];
                records[j] = tmp;
            }
        }
    }
}

