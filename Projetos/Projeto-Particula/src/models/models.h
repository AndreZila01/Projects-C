#ifndef MODELS_H
#define MODELS_H

#include "../utils/hash_table.h"

typedef struct
{
    char *name;
    int next_space_id;
    HashTable simulation;
} User_, *User;

typedef struct
{
    int* id;
    //int next_space_id;
    HashTable particle;
} SpaceSimulation_, *SpaceSimulation;

typedef struct
{
    int idParticula; // particula do user, neste caso o size
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

User new_user(char* name);

void free_user(User user);

bool equal_ints(void* key1, void* key2);

void register_simulation(User users);

SpaceSimulation new_space(int id);

void free_Particle(SpaceSimulation space);

void free_Space(User user);

bool has_simulation(User user, char *name);

bool has_Particle(SpaceSimulation sim, char *name);

void* return_simulation(User user, char* name);

#endif