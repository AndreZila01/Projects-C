#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "auxMain.c"

typedef struct List_ *List;
typedef struct Node_ *Node;
typedef struct ListP_ *ListP;
typedef struct NodeP_ *NodeP;

void switchcase(List lst, char *line)
{
    char *comando = strtok(line, " ");
    if (strcmp(comando, "RJ") == 0)
    {
        RegistUser(strtok(NULL, " "), lst);
    }
    if (strcmp(comando, "EJ") == 0)
    {
        RemoveUser(lst, strtok(NULL, " "));
    }
    if (strcmp(comando, "LJ") == 0)
    {
        ListUser(lst);
    }
    if (strcmp(comando, "RE") == 0)
    {
        RegistSimSpace(list, strtok(NULL, " "));
    }
    if (strcmp(comando, "EE") == 0)
    {
    }
    if (strcmp(comando, "RP") == 0)
    {
    }
    if (strcmp(comando, "AP") == 0)
    {
    }
    if (strcmp(comando, "S") == 0)
    {
    }
    if (strcmp(comando, "G") == 0)
    {
    }
    if (strcmp(comando, "L") == 0)
    {
    }
}

int main()
{
    List lst = list_createUser();
    while (true)
    {
        char *line = NULL;
        size_t len = 0;
        getline(&line, &len, stdin);
        line[strlen(line) - 1] = '\0';
        if (strlen(line) == 0)
            break;
        switchcase(lst, line);
        free(line);
    }
    return 0;
}
