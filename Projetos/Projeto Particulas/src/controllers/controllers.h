#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include "../utils/hash_table.h"

typedef struct
{
    HashTable users;
} tApp, *App;

App new_app();

void free_app(App app);

bool has_app(App app, char *name);

void register_app(App app, char *name);

typedef struct
{
    char *name;
    HashTable simulation;
} User_, *User;

User new_user();

void free_user(User usern);

bool has_user(User usern, char *name);

void register_user(User usern, char *name);

typedef struct
{
    int *id;
    HashTable particle;
} SpaceSimulation_, *SpaceSimulation;

SpaceSimulation new_space();

void free_space(SpaceSimulation app);

bool has_space(SpaceSimulation app, int* id);

void register_space(SpaceSimulation app, int* id);

typedef struct
{
    int *idParticula; // particula do user, neste caso o size
    char *NomeUser;
    int massa;
    int carga;
    float x;  // posição em x
    float y;  // posição em y
    float z;  // posição em z
    float Vx; // velocidade em x
    float Vy; // velocidade em y
    float Vz; // velocidade em z
} Particle_, *Particle;

Particle new_Part();

void free_Part(Particle part);

bool has_Part(Particle part, int * idParticula, char *NomeUser, int massa, int carga, float x, float y, float z, float Vx, float Vy, float Vz);

void register_Part(Particle part, char *name);

#endif