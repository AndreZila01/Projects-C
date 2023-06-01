#define _POSIX_C_SOURCE 200809L
#include "cli.h"
#include "../controllers/controllers.h"

#include <stdio.h>

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

void RJ(App app, char *name)
{
    if (app_has_user(app, name))
        printf("Utilizador existente.\n");
    else
    {
        app_register_user(app, name);
        printf("Utilizador registado com sucesso.\n");
    }
}

void EJ(App app, char *name)
{
    if (!app_has_user(app, name))
        printf("Utilizador não existente.\n");
    else
    {
        // app_free_app(app);
        if (/*app_user_simulatorCount(app->users, name) > 0 &&*/ Simulation_OnOff(app->users)) // Não percebi nada!
        {
            app_remove_user(app->users, name);
            printf("Utilizador removido com sucesso.\n");
        }
        // else
        //   printf("Utilizador tem espaços de simulação sem simulações realizadas.\n");
    }
}

void LJ(App app)
{
    int userCount= app_CounterUser(app);
    User *users = app_ConvertUserToArray(app, &userCount);
    if (userCount == 0)
        printf("Não existem utilizadores registados.\n");
    else
    {
        if (userCount > 1)
            qsort(users, userCount, sizeof(User), compareUsersByName);
        int count = 0;
        while (userCount != count)
        {
            printf("%s %d %d\n", users[count]->name, app_spacesCount(users[count]), app_user_simulatorCount(users[count], users[count]->name));
            count++;
        }
        free(users);
    }
}

void RE(App app, char *name)
{
    if (!app_has_user(app, name))
        printf("Utilizador inexistente.\n");
    else
    {
        app_register_simulation(app, name);
        printf("Espaço de simulação registado com identificador IdentificadorEspaço.\n");
    }
}

void EE(App app, char *name)
{
    if (!app_has_user(app, name))
        printf("Utilizador não existente.\n");
    else
    {
        if (app_has_simulation(app, name))
        {
            app_free_simulation(app, name);
            printf("Espaço de simulação removido com sucesso.\n");
        }
        else
            printf("Espaço de simulação inexistente.\n");
    }
}

void RP(App app, char *name, char *identifi)
{
    int massa = 0, carga = 0, pix = 0, piy = 0, piz = 0, vx = 0, vy = 0, vz = 0;
    char *row_contents = NULL;
    size_t row_len = 0;

    // MASSA >=0, CARGA percente a Z
    getline(&row_contents, &row_len, stdin);
    row_contents[strlen(row_contents) - 1] = '\0';
    massa = atof(strtok(row_contents, " "));
    carga = atof(strtok(NULL, " "));

    free(row_contents);
    row_contents = NULL;

    getline(&row_contents, &row_len, stdin);
    row_contents[strlen(row_contents) - 1] = '\0';
    pix = atof(strtok(row_contents, " "));
    piy = atof(strtok(NULL, " "));
    piz = atof(strtok(NULL, " "));

    free(row_contents);
    row_contents = NULL;

    getline(&row_contents, &row_len, stdin);
    row_contents[strlen(row_contents) - 1] = '\0';
    vx = atof(strtok(row_contents, " "));
    vy = atof(strtok(NULL, " "));
    vz = atof(strtok(NULL, " "));

    free(row_contents);

    app_Registar_Part(app, name, identifi, massa, carga, pix, piy, piz, vx, vy, vz);
}

void AP(App app, char *name, char *IdenSpace, char *IdenPart)
{

    int massa = 0, carga = 0, pix = 0, piy = 0, piz = 0, vx = 0, vy = 0, vz = 0;
    char *row_contents = NULL;
    size_t row_len = 0;

    // MASSA >=0, CARGA percente a Z
    getline(&row_contents, &row_len, stdin);
    row_contents[strlen(row_contents) - 1] = '\0';
    massa = atof(strtok(row_contents, " "));
    carga = atof(strtok(NULL, " "));

    free(row_contents);
    row_contents = NULL;

    getline(&row_contents, &row_len, stdin);
    row_contents[strlen(row_contents) - 1] = '\0';
    pix = atof(strtok(row_contents, " "));
    piy = atof(strtok(NULL, " "));
    piz = atof(strtok(NULL, " "));

    free(row_contents);
    row_contents = NULL;

    getline(&row_contents, &row_len, stdin);
    row_contents[strlen(row_contents) - 1] = '\0';
    vx = atof(strtok(row_contents, " "));
    vy = atof(strtok(NULL, " "));
    vz = atof(strtok(NULL, " "));

    free(row_contents);
    
    app_Modify_Part(app, name, IdenSpace, IdenPart, massa, carga, pix, piy, piz, vx, vy, vz);
}

void S(App app, char* name, char* IdentificadorEspaço, char* IdentificadorParticula)
{
    int tempo = 0, passo = 0;
    char *row_contents = NULL;
    size_t row_len = 0;

    // MASSA >=0, CARGA percente a Z
    getline(&row_contents, &row_len, stdin);
    row_contents[strlen(row_contents) - 1] = '\0';
    tempo = atoi(strtok(row_contents, " "));
    passo = atoi(strtok(NULL, " "));

    free(row_contents);
    row_contents = NULL;

    getline(&row_contents, &row_len, stdin);
    row_contents[strlen(row_contents) - 1] = '\0';
    char* file = strtok(row_contents, " ");

    free(row_contents);
    row_contents = NULL;

    app_Simulate(app, name, IdentificadorEspaço, IdentificadorParticula, tempo, passo, file);
    // SimulationCount++;
}

void run_cli()
{
    char *line = NULL;
    size_t len = 0;
    App app = app_new();
    while (true)
    {
        getline(&line, &len, stdin);
        line[strlen(line) - 1] = '\0';
        if (strlen(line) == 0)
            break;

        char *command = strtok(line, " ");
        if (strcmp(command, "RJ") == 0) // Registar jogador
            RJ(app, strtok(NULL, " "));
        else if (strcmp(command, "EJ") == 0) // Remover Jogador
            EJ(app, strtok(NULL, " "));
        else if (strcmp(command, "LJ") == 0) // Listar Jogador
            LJ(app);
        else if (strcmp(command, "RE") == 0) // Registar Simulacao
            RE(app, strtok(NULL, " "));
        else if (strcmp(command, "EE") == 0) // Remover Simulacao
            EE(app, strtok(NULL, " "));
        else if (strcmp(command, "RP") == 0) // Registar particula
            RP(app, strtok(NULL, " "), strtok(NULL, " "));
        else if (strcmp(command, "AP") == 0) // Alterar Particula
            AP(app, strtok(NULL, " "), strtok(NULL, " "), strtok(NULL, " "));
        else if (strcmp(command, "S") == 0) // Simular
            S(app, strtok(NULL, " "), strtok(NULL, " "), strtok(NULL, " "));
        else
            printf("Instrução inválida.\n");
        
        free(line);
        line = NULL;
    }
    // if (line != NULL)
    // {
    //     free(line);
    // }
    app_free_app(app);
    free(line);
}