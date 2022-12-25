#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char txt[80];
    int i;
    int j;
} tRecord, *pRecord;

typedef struct
{
    pRecord *records;
    int num_records;
    int a;
} tData, *pData;

void save(pData data, char *filename)
{
    FILE *fp = fopen(filename, "w");
    fprintf(fp, "%d\n", data->num_records);
    for (int i = 0; i < data->num_records; i++)
    {
        fprintf(fp, "%s,", data->records[i]->txt);
        fprintf(fp, "%d,", data->records[i]->i);
        fprintf(fp, "%d\n", data->records[i]->j);
    }
    fprintf(fp, "%d\n", data->a);
    fclose(fp);
}

void read(char *filename)
{
    FILE *file = fopen(filename, "r");
    char currentline[100];

    while (fgets(currentline, sizeof(currentline), file) != NULL)
    {
        fprintf(stderr, "got line: %s\n", currentline);
        /* Do something with `currentline` */
        /* strtok */
    }
}

int main()
{

    int num_elems = 3;
    pData data = malloc(sizeof(tData));
    data->records = malloc(sizeof(pRecord) * num_elems);

    data->records[0] = malloc(sizeof(tRecord));
    strcpy(data->records[0]->txt, "Texto A");
    data->records[0]->i = 1;
    data->records[0]->j = 30;

    data->records[1] = malloc(sizeof(tRecord));
    strcpy(data->records[1]->txt, "Texto B");
    data->records[1]->i = 2;
    data->records[1]->j = 40;

    data->records[2] = malloc(sizeof(tRecord));
    strcpy(data->records[2]->txt, "Texto C");
    data->records[2]->i = 3;
    data->records[2]->j = 50;

    data->num_records = 3;
    data->a = 42;

    save(data, "teste.txt");

    read("teste.txt");

    for (int i = 0; i < data->num_records; i++)
    {
        free(data->records[i]);
    }
    free(data->records);
    free(data);

    return 0;
}