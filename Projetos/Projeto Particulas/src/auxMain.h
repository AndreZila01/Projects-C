#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "api.h"

typedef struct List_ *List;
typedef struct Node *Node;

List list_create()
{
    List list = malloc(sizeof(struct List_));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void RegistarUser(char *user, List list)
{

    if (checkempty(list))
        list = list_create();

    if (checkexistsamename(list, *user))
    {
        Node node = malloc(sizeof(struct Node));
        node->element = user;
        node->next = NULL;

        if (checkempty(list))
        {
            list->head = node;
            list->tail = node;
        }
        else
            list->tail->next = node;

        list->size++;

        printf("Utilizador registado com sucesso.");
    }
    else
        printf("Utilizador existente.");
}