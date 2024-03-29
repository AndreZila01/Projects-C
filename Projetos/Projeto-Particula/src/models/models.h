#ifndef MODELS_H
#define MODELS_H

#include "../utils/hash_table.h"
#include "../utils/list.h"

typedef struct
{
    char *name;
    int next_space_id;
    bool simulation_on; // simuação realizada.
    HashTable Spacesimulation;
} User_, *User;

typedef struct
{
    char* id;
    //int next_space_id;
    HashTable particle;
    int SpaceSimulationCount; //Espaços de simulação do user
    int SimulationCount; //Simulações executadas
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

char* register_simulation(User user);

SpaceSimulation new_space(char* id);

int size_Simulation(User sim);

void free_Particle(SpaceSimulation space);

void free_Space(User user);

bool has_simulation(User user, char *name);

bool has_Particle(SpaceSimulation sim, char *name);

void* return_simulation(User user, char* name);

bool Simulation_OnOff(User sim);

void* ConvertArray(List lst, int userCount);

int SpaceSimulationCount(void* values);

void Modify_Part(User user, char* name, char* IdenSpace, char* IdenPart, float massa, float carga, float pix, float piy, float piz, float vx, float vy, float vz);

void printformulas(User user, char* IdentificadorEspaço, char* IdentificadorParticula, int tempo, int passo, char* file);

int CountUser(User user);
#endif