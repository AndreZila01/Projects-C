#define _XOPEN_SOURCE 500
#include "models.h"
#include "../utils/hash_table.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void free_key(void* key) {
    free(key);
}

void free_value(void* value) {
    free(value);
}

bool equal_ints(void* key1, void* key2) {
    int* k1 = (int*)key1;
    int* k2 = (int*)key2;
    return *k1 == *k2;
}

int hash_space_id(void* key, int size){
    int* k = (int*)key;
    return *k % size;
}

void space_free(void* space) {
    SpaceSimulation s = (SpaceSimulation)space;
    hash_table_destroy(s->particle);
    free(s->id);
    free(s);
}


User new_user(char* name) {
    User user = malloc(sizeof(User_));
    user->name = name;
    user->simulation = hash_table_create(0, hash_space_id, equal_ints, NULL, space_free);
    return user;
}

void free_user(User user) {
    free(user->name);
    free(user);
    // TODO: Falta atualizar para os novos campos de User.
}

void register_simulation(User user) {
    //User user = hash_table_get(users, user_name);
    // 0. Criar o identificador de espaço
    char space_id[80];
    //int space_id;
    sprintf(space_id, "%d", user->next_space_id);
    SpaceSimulation space = new_space(user->next_space_id);
    user->next_space_id++;

    hash_table_insert(user->simulation, space->id, space);
    //return space->id;
}

SpaceSimulation new_space(int id)
{
    SpaceSimulation space = malloc(sizeof(SpaceSimulation_));
    space->id = malloc(sizeof(int));
    *(space->id) = id;
    return space;
}

void free_Particle(SpaceSimulation space)
{
    free(space->particle);
    free(space);
}

void free_Space(User user)
{
    free(user->simulation);
    free(user);
}

bool has_simulation(User user, char *name)
{
    return hash_table_get(user->simulation, name) != NULL;
}

bool has_Particle(SpaceSimulation sim, char *name)
{
    return hash_table_get(sim->particle, name) != NULL;
}

int size_Particle(SpaceSimulation sim){
    return hash_table_size(sim->particle);
}

void* return_simulation(User user, char* name)
{
    return hash_table_get(user->simulation, name);
}