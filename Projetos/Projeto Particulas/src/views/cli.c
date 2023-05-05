#include "cli.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../controllers/task_list.h"
#include "../models/tasks.h"
#include "../utils/hash_table.h"

void switchcase(TaskList lstUser, char *line, int id)
{
    char *comando = strtok(line, " ");
    if (strcmp(comando, "RJ") == 0)
        hash_table_insert(lstUser, (int *)++id, strtok(NULL, " "));
    if (strcmp(comando, "EJ") == 0)
        hash_table_remove(lstUser, strtok(NULL, " "));
    if (strcmp(comando, "LJ") == 0)
        ListUser(lstUser);
    if (strcmp(comando, "RE") == 0)
        RegistSimSpace(lstUser, strtok(NULL, " "));
    if (strcmp(comando, "EE") == 0)
        RemoveSimSpace(lstUser, strtok(NULL, " "));
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
int hash_ints(void *key, int size)
{
    int *k = (int *)key;
    return *k % size;
}

bool equal_ints(void *key1, void *key2)
{
    int *k1 = (int *)key1;
    int *k2 = (int *)key2;
    return *k1 == *k2;
}

void free_key(void *key)
{
    free(key);
}

void free_value(void *value)
{
    free(value);
}

void run_cli()
{
    char *line = NULL;
    size_t len = 0;
    int id = 1;
    HashTable lstUser = hash_table_create(0, hash_ints, equal_ints, free_key, free_value);
    while (true)
    {
        getline(&line, &len, stdin);
        char *command = strtok(line, " \n");
        if (line != NULL)
            free(line);

        switchcase(lstUser, line, id);
        free(line);
        // if (strcmp(command, "Q") == 0) {
        //     break;
        // } else if (strcmp(command, "RT") == 0) {
        //     char* description = strtok(NULL, "\n");
        //     char* id = task_list_add_task(task_list, description);
        //     printf("Tarefa criada com identificador %s.\n", id);
        // } else if (strcmp(command, "LT") == 0) {
        //     list_iterator_start(task_list->tasks);
        //     while(list_iterator_has_next(task_list->tasks)) {
        //         Task task = list_iterator_get_next(task_list->tasks);
        //         printf("%s %s %s\n", task_get_id(task), task_get_description(task), task_get_status(task));
        //     }
        // } else if (strcmp(command, "MT") == 0) {
        //     char* id = strtok(NULL, "\n");
        //     task_list_complete_task(task_list, id);
        //     printf("Tarefa %s marcada como completa.\n", id);
        // } else {
        //     printf("Instrução inválida.\n");
    }
    free(line);
    line = NULL;
    task_list_destroy(lstUser);
}
