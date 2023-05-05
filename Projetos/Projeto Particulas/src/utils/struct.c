#include "hash_table.h"

typedef struct
{
    char * userName;
    HashTable SimulationSpace
} User_, *user;

typedef struct{
    int* id;
    HashTable Particle;
} Simulation_, *Simulation;

typedef struct{
    int* idParticula; // particula do user, neste caso o size
    char * NomeUser;
    int massa;
    int carga;
    float x;//posição em x
    float y;//posição em y
    float z;//posição em z
    float Vx;//velocidade em x
    float Vy;//velocidade em y
    float Vz;//velocidade em z
} Particle_, *Particle;