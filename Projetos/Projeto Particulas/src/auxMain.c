#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "api.h"
#include "Structs.h"

List list_create()
{
    List list = malloc(sizeof(struct List_));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

bool CheckExistSameName(List a, char* b);

void RegistarUser(char *user, List list)
{

    if (CheckEmpty(list))
        list = list_create();

    if (CheckExistSameName(list, user))
    {
        Node node = malloc(sizeof(struct Node_));
        node->element = user;
        node->next = NULL;

        if (CheckEmpty(list))
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

bool CheckExistSameName(List list, char* name)
{
    Node node = list->head;
    int check = 0;
    while (list->head != NULL)
    {
        if (CheckEqualString(node->element, name))
            check++;

        if (check == 2)
            return true;

        node = node->next;
    }
    return false;
}