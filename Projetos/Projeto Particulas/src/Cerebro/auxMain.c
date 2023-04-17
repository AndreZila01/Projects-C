#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "api.h"
#include "FuncoesUnite.c"
#include "Structs.c"

void RegistUser(char *user, List list)
{
    if (list_is_empty(list))
        list = list_create();

    if (list_find(list, list_equal, user) != -1)
    {
        list_insert_last(list, user);
        printf("Utilizador registado com sucesso.\n");
    }
    else
        printf("Utilizador existente.\n");
}

void RemoveUser(List list, char *user)
{
    if (list_find(list, list_equal, user) == -1)
        return printf("Utilizador não existente.\n");

    list_remove(list, list_find(list, list_equal, user));
    printf("Utilizador removido com sucesso.\n");
}

void ListUser(List list)
{
    Node node = list->head;
    while (node != NULL)
    {
        printf("%s", node->element);
        node = node->next;
    }
}

void RegistSimSpace(List listuser, List lstPart, char *vs)
{
    if (list_find(listuser, list_equal, vs) != -1)
    {
        Particula part = malloc(sizeof(Particula_));
        part->idParticula = lstPart->size++;
        part->NomeUser = vs;
        list_insert_last(lstPart, part);
        printf("Espaço de simulação registado com identificador IdentificadorEspaço.\n");
    }
    else
        printf("Utilizador inexistente.\n");
}

void RemoveSimSpace(List lstUser, List lstPart, char *vs)
{
    
    if (list_find(lstUser, list_equal, vs) == -1)
        return printf("Utilizador inexistente.");

    char *va = strtok(NULL, " ");
    if (list_find(lstPart, list_equal, va) == -1)
        return printf("Espaço de simulação inexistente.");

    list_remove(lstPart, list_find(lstPart, list_equal, va));
    printf("Espaço de simulação removido com sucesso.");
}

void RegistPart(List lstuser, List lstPart, char *vs){
    
}