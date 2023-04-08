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

bool CheckExistSameName(List a, char *b);
int CheckExistUser(List a, char *b);
void* list_remove_first(List list);

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

void RemoveUser(List list, char *user)
{
    Node node = list->head;
    Node prevNode = NULL;
    int i = 0, position = CheckExistUser(list, user);
    if (position != -1)
        while (node != NULL)
        {
            if (position == 0)
            {
                void *removedElement = list_remove_first(list);
                printf("Utilizador removido com sucesso.");
                list->head = node->next;
                return removedElement;
            }
            if (i == position)
            {
                prevNode->next = node->next;
                void *removedElement = node->element;
                free(node);
                printf("Utilizador removido com sucesso.");
                return removedElement;
            }
            prevNode = node;
            node = node->next;
            i++;
        }
    printf("Utilizador não existente.");
    return NULL;
}

bool CheckExistSameName(List list, char *name)
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

int CheckExistUser(List list, char *name)
{
    Node node = list->head;
    int i = 0;
    while (node != NULL)
    {
        if (CheckEqualString(node->element, name))
            return i;

        node = node->next;
        i++;
    }
    return -1;
}

void ListarJogador(List list)
{
    Node node = list->head;
    if(node==NULL)
        printf("Não existem utilizadores registados.");
    else
    while (node != NULL)
    {
        printf(node->element);
        node = node->next;
    }
}

void* list_remove_first(List list) {
    
    Node node = list->head;
    list->head = node->next;
    void* element = node->element;
    free(node);
    return element;
}