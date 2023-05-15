#include "controllers.h"
#include "../models/models.h"

#include <stdlib.h>
#include <string.h>

#pragma region User

App new_user()
{
    App app = malloc(sizeof(tApp));
    app->users = hash_table_create(0, NULL, NULL, NULL, (void (*)(void *))free_user);
    return app;
}

void free_user(App app)
{
    hash_table_destroy(app->users);
    free(app);
}

bool has_user(App app, char *name)
{
    return hash_table_get(app->users, name) != NULL;
}

void register_user(App app, char *name)
{
    User user = new_app(name);
    hash_table_insert(app->users, name, user);
}

int SizeOfHash(App usern)
{
    return hash_table_size(usern->users);
}

void list_user(App usern)
{
    void *value = hash_table_values(usern);
    int lenght = hash_table_size(usern), val=0;

    // não consigo ter o node desta solução??
    while (lenght != val)
    {
        printf("Espaço de simulação registado com identificador %s.\n", hash_table_get(usern, val));
        val++;
    }
}

#pragma endregion

#pragma region simulation_spaces

User new_simulation(char *username)
{
    User app = malloc(sizeof(tApp));
    app->name = NULL;
    app->simulation_spaces = hash_table_create(0, NULL, NULL, NULL, (void (*)(void *))free_user);
    return app;
}

void free_simulation(User usern)
{
    hash_table_destroy(usern->simulation_spaces);
    free(usern);
}

bool has_simulation(User usern, char *name)
{
    return hash_table_get(usern->simulation_spaces, name) != NULL;
}

void register_simulation(User usern, char *name)
{
    User user = new_app(name);
    hash_table_insert(usern->simulation_spaces, name, user);
}


#pragma endregion

#pragma region particle

SpaceSimulation new_space()
{
    App app = malloc(sizeof(Particle_));
    app->users = hash_table_create(0, NULL, NULL, NULL, (void (*)(void *))free_user);
    return app;
}

void free_space(SpaceSimulation app)
{
    hash_table_destroy(app->particle);
    free(app);
}

bool has_space(SpaceSimulation app, char *name)
{
    return hash_table_get(app->particle, name) != NULL;
}

void register_space(SpaceSimulation app, char *name)
{
    User user = new_app(name);
    hash_table_insert(app->particle, name, user);
}

#pragma endregion

// #pragma region Particle

// Particle new_Part()
// {
//     App app = malloc(sizeof(tApp));
//     app->users = hash_table_create(0, NULL, NULL, NULL, (void (*)(void *))free_user);
//     return app;
// }

// void free_Part(Particle part)
// {
//     hash_table_destroy(app->users);
//     free(app);
// }

// bool has_Part(Particle part, int *idParticula, char *NomeUser, int massa, int carga, float x, float y, float z, float Vx, float Vy, float Vz)
// {
//     return hash_table_get(app->users, name) != NULL;
// }

// void register_Part(Particle part, char *name)
// {
//     User user = new_app(name);
//     hash_table_insert(app->users, name, user);
// }

// #pragma endregion