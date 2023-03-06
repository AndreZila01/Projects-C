#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char *date;
    float open;
    float high;
    float low;
    float close;
    long long Volume;
    char *MarketCap;
} Crypto, *LstCrypto;

bool CheckFile()
{
    FILE *fp = fopen("btc.txt", "r");

    if (fp != NULL)
    {
        fclose(fp);
        return true;
    }
    else
        return false;
}

char *ReadFile()
{
    LstCrypto cryp = realloc(NULL, sizeof(Crypto));

    FILE *fp = fopen("btc.txt", "r");
    char line[1000];

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        int value=0;
            printf("%s", line);
            //strcmp(comando, "EJ") == 0
        if (strcmp(strtok(line, ";"), "Date"))
        {
            cryp->date = strtok(line, ";");
            cryp->open = atof(strtok(NULL, ";"));
            cryp->high = atof(strtok(NULL, ";"));
            cryp->low = atof(strtok(NULL, ";"));
            cryp->close = atof(strtok(NULL, ";"));
            cryp->Volume, atoll(strtok(NULL, ";"));
            strcpy(cryp->MarketCap, strtok(NULL, ";"));
            value++;

            cryp = realloc(cryp, sizeof(Crypto) * value);
        }
    }
}