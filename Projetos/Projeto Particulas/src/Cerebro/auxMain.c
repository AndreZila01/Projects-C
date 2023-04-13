#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "Cerebro/api.h"
#include "Cerebro/Structs.c"


bool CheckExistSameName(List a, char *b);
void *list_remove_first(List list);

void RegistUser(char *user, List list)
{

    if (CheckEmpty(list))
        list = list_createUser();

    if (!CheckExistSameName(list, user))
    {
        Node node = malloc(sizeof(struct Node_));
        node->element = user;
        node->next = NULL;

        if (CheckEmpty(list))
        {
            list->head = node;
        }
        else
            list->tail->next = node;

        list->tail = node;
        list->size++;

        printf("Utilizador registado com sucesso.\n");
    }
    else
        printf("Utilizador existente.\n");
}

void RemoveUser(List list, char *user)
{
    Node node = list->head;
    Node prevNode = NULL;
    int i = 0, position = CheckExistSameName(list, user);
    if (position != -1)
        while (node != NULL)
        {
            if (position == 0)
            {
                void *removedElement = list_remove_first(list);
                printf("Utilizador removido com sucesso.\n");
                list->head = node->next;
                break;
            }
            if (i == position)
            {
                prevNode->next = node->next;
                void *removedElement = node->element;
                free(node);
                printf("Utilizador removido com sucesso.\n");
                break;
            }
            prevNode = node;
            node = node->next;
            i++;
        }
    else
        printf("Utilizador não existente.\n");
}

bool CheckExistSameName(List list, char *name)
{
    Node node = list->head;
    int check = 0;
    while (node != NULL)
    {
        if (CheckEqualString(node->element, name))
            check++;

        if (check == 2)
            return true;

        node = node->next;
    }
    return false;
}

void ListJogador(List list)
{
    Node node = list->head;
    if (node == NULL)
        printf("Não existem utilizadores registados.\n");
    else
        while (node != NULL)
        {
            printf("%p", node->element);
            node = node->next;
        }
}

void *list_remove_first(List list)
{

    Node node = list->head;
    list->head = node->next;
    void *element = node->element;
    free(node);
    return element;
}

/*void RegistSimSpace(ListP list, char * user){
    if (CheckEmptyPart(list))
        list = list_createPart();

    if (!CheckExistSameName(list, user))
    {
        NodeP node = malloc(sizeof(struct NodeP_));
        node->NomeUser = user;
        node->next = NULL;

        if (CheckEmpty(list))
        {
            list->head = node;
        }
        else
            list->tail->next = node;

        list->tail = node;
        list->size++;

        printf("Espaço de simulação registado com identificador IdentificadorEspaço.\n");
    }
    else
        printf("Utilizador inexistente.\n");
}

void RemoveSimSpace(ListP list, char * nome, char* Identificador){
    //... O que é o Identificador??
}*/

