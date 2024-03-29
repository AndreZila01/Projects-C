#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include "../utils/hash_table.h"
#include "../models/models.h"

typedef struct
{
    HashTable users;
} tApp, *App;

App app_new();

// void list_user(App usern);

void app_free_app(App app);

bool app_has_user(App app, char *name);

void app_register_user(App app, char *name);

User app_new_simulation();

void app_free_simulation(App usern, char *name);

bool app_has_simulation(App app, char *name, char* iden);

void* app_register_simulation(App app, char *user_name);

int app_SizeOfHash(App usern);

void *app_ValueOfUser(App app, char *name);

int app_hash_ints(void *key, int size);

bool app_has_simulation(App app, char *name, char* iden);

void app_remove_user(App app, char *name);

void free_app(App app);

// int app_SizeOfHash(App usern);

// SpaceSimulation app_new_space();

// void app_free_space(SpaceSimulation app);

// bool app_has_space(SpaceSimulation app, char* name);

// void app_register_space(App app, char* name);

// Particle app_new_Part();

// void app_free_Part(Particle part);

// bool app_has_Part(Particle part, int * idParticula, char *NomeUser, int massa, int carga, float x, float y, float z, float Vx, float Vy, float Vz);

// void app_register_Part(Particle part, char *name);

void app_Registar_Part(App app, char *name, char *identifi, float massa, float carga, float pix, float piy, float piz, float vx, float vy, float vz);

void app_Modify_Part(App app, char *name, char *IdenSpace, char *IdenPart, float massa, float carga, float pix, float piy, float piz, float vx, float vy, float vz);

int compare_users(const void* a, const void* b);

void *app_ConvertUserToArray(App app, int userCount);

int app_user_simulatorCount(void* user);

int app_spacesCount(void* user);

void app_Simulate(App app, char *name, char *IdentificadorEspaço, char *IdentificadorParticula, int tempo, int passo, char *file);

int app_CounterUser(App app);

bool app_Simulation_OnOff(App app, char *name);

#endif