#include "controllers.h"
#include "../models/models.h"

#include <stdlib.h>
#include <string.h>

#pragma region APP

App new_app()
{
    App app = malloc(sizeof(tApp));
    app->users = hash_table_create(0, NULL, NULL, NULL, (void (*)(void *))free_user);
    return app;
}

void free_app(App app)
{
    hash_table_destroy(app->users);
    free(app);
}

bool has_app(App app, char *name)
{
    return hash_table_get(app->users, name) != NULL;
}

void register_app(App app, char *name)
{
    User user = new_app(name);
    hash_table_insert(app->users, name, user);
}

#pragma endregion

#pragma region  USER

User new_user(char* username)
{
    User app = malloc(sizeof(tApp));
    app->name = username;
    app->simulation_spaces = hash_table_create(0, NULL, NULL, NULL, (void (*)(void *))free_user);
    return app;
}

void free_user(User usern)
{
    hash_table_destroy(usern->simulation_spaces);
    free(app);
}

bool has_user(User usern, char *name)
{
    return hash_table_get(usern->users, name) != NULL;
}

void register_user(User usern, char *name)
{
    User user = new_app(name);
    hash_table_insert(usern->users, name, user);
}

#pragma endregion

#pragma region SpaceSimulation

SpaceSimulation new_space()
{
    App app = malloc(sizeof(Particle_));
    app->users = hash_table_create(0, NULL, NULL, NULL, (void (*)(void *))free_user);
    return app;
}

void free_space(SpaceSimulation app)
{
    hash_table_destroy(app->users);
    free(app);
}

bool has_space(SpaceSimulation app, int *id)
{
    return hash_table_get(app->users, name) != NULL;
}

void register_space(SpaceSimulation app, int *id)
{
    User user = new_app(name);
    hash_table_insert(app->users, name, user);
}

#pragma endregion

#pragma region Particle

Particle new_Part()
{
    App app = malloc(sizeof(tApp));
    app->users = hash_table_create(0, NULL, NULL, NULL, (void (*)(void *))free_user);
    return app;
}

void free_Part(Particle part)
{
    hash_table_destroy(app->users);
    free(app);
}

bool has_Part(Particle part, int *idParticula, char *NomeUser, int massa, int carga, float x, float y, float z, float Vx, float Vy, float Vz)
{
    return hash_table_get(app->users, name) != NULL;
}

void register_Part(Particle part, char *name)
{
    User user = new_app(name);
    hash_table_insert(app->users, name, user);
}

#pragma endregion