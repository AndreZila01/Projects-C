#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include "../utils/hash_table.h"
#include "../models/models.h"

typedef struct
{
    HashTable users;
} tApp, *App;

App app_new_user();

void app_free_user(App app);

bool app_has_user(App app, char *name);

void app_register_user(App app, char *name);

User app_new_simulation();

void app_free_simulation(User usern);

bool app_has_simulation(User usern, char *name);

void app_register_simulation(User usern, char *name);

int app_SizeOfHash(App usern);

SpaceSimulation app_new_space();

void app_free_space(SpaceSimulation app);

bool app_has_space(SpaceSimulation app, char* name);

void app_register_space(App app, char* name);


Particle app_new_Part();

void app_free_Part(Particle part);

bool app_has_Part(Particle part, int * idParticula, char *NomeUser, int massa, int carga, float x, float y, float z, float Vx, float Vy, float Vz);

void app_register_Part(Particle part, char *name);

#endif