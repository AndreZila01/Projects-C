#include "cli.h"
#include "../controllers/controllers.h"

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

void run_cli()
{
    char *line = NULL;
    size_t len = 0;
    App app = new_app();
    while (true)
    {
        getline(&line, &len, stdin);
        line[strlen(line) - 1] = '\0';
        if (strlen(line) == 0)
        {
            break;
        }
        char *command = strtok(line, " ");
        if (strcmp(command, "RJ") == 0)
        {
            char *name = strtok(NULL, " ");
            if (has_user(app, name))
            {
                printf("Utilizador existente.\n");
            }
            else
            {
                register_user(app, name);
                printf("Utilizador registado com sucesso.\n");
            }
        }
        else if (strcmp(command, "EJ") == 0)
        {
            char *description = strtok(NULL, "\n");
            if (!has_user(app, description))
                printf("Utilizador não existente.\n");
            else
            {
                free_user(hash_table_get(app, description));
                printf("Utilizador removido com sucesso.\n");
            }
        }
        else if (strcmp(command, "LJ") == 0)
        {
            if (SizeOfHash(app) != -1)
                hash_list(app);
        }
        else if (strcmp(command, "RE") == 0)
        {
            char *name = strtok(NULL, " ");
            if (has_user(app, name))
                printf("Utilizador existente.\n");

            else
            {
                register_simulation(app, name);
                printf("Espaço de simulação registado com identificador IdentificadorEspaço.\n");
            }
        }
        else if (strcmp(command, "EE") == 0)
        {
            char *description = strtok(NULL, "\n");
            if (!has_simulation(app->users, description))
                printf("Utilizador não existente.\n");
            else
            {
                if (has_simulation(app->users, description))
                {
                    free_simulation(hash_table_get(app->users->, description));
                    printf("Espaço de simulação removido com sucesso.\n");
                }
                else
                    printf("Espaço de simulação inexistente.");
            }
        }
        else if (strcmp(command, "RP") == 0)
        {
        }
        else if (strcmp(command, "AP") == 0)
        {
        }
        else if (strcmp(command, "S") == 0)
        {
        }
        else
        {
            printf("Instrução inválida.\n");
        }
        free(line);
        line = NULL;
    }
    if (line != NULL)
    {
        free(line);
    }
    free_app(app);
}