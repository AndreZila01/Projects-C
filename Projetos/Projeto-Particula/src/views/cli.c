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
        app_remove_user(app, name);
        printf("Utilizador removido com sucesso.\n");
    }
}

void LJ(App app)
{
    if (app_SizeOfHash(app) != -1)
        list_user(app);
}

void RE(App app, char *name)
{
    if (!app_has_user(app, name))
        printf("Utilizador existente.\n");
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
            printf("Espaço de simulação inexistente.");
    }
}

void RP(App app, char *name, char *identifi)
{
    int massa=0, carga=0, pix=0, piy=0, piz=0, vx=0, vy=0, vz=0;
    char *row_contents = NULL;
    size_t row_len = 0;

    //MASSA >=0, CARGA percente a Z
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

void AP(App app, char* name, char* IdenSpace, char* IdenPart){
    
    int massa=0, carga=0, pix=0, piy=0, piz=0, vx=0, vy=0, vz=0;
    char *row_contents = NULL;
    size_t row_len = 0;

    //MASSA >=0, CARGA percente a Z
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

void S(){

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
        else if (strcmp(command, "RP") == 0) // Remover particula
            RP(app, strtok(NULL, " "), strtok(NULL, " "));
        else if (strcmp(command, "AP") == 0) // Alterar Particula
        {
            Ap(app, strtok(NULL, " "), strtok(NULL, " "), strtok(NULL, " "));
        }
        else if (strcmp(command, "S") == 0) // Simular
        {
            S();
        }
        else
        {
            printf("Instrução inválida.\n");
        }
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