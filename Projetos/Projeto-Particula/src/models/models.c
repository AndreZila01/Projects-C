#include "models.h"

#include <stdlib.h>

#define _XOPEN_SOURCE 500
#include <string.h>

#pragma region HashTable
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

#pragma endregion

#pragma region  User

User new_user(char* name) {
    User user = malloc(sizeof(User_));
    user->name = name;
    return user;
}

void free_user(User user) {
    free(user->name);
    free(user);
    // TODO: Falta atualizar para os novos campos de User.
}

int SizeOfHash(App usern)
{
    return hash_table_size(usern->users);
}
#pragma endregion

#pragma region Space

char* register_space(User users, char* user_name) {
    User user = hash_table_get(users, user_name);
    // 0. Criar o identificador de espaço
    char space_id[80];
    //sprintf(space_id, "%d", user->next_space_id);
    SpaceSimulation space = new_space(user->next_space_id);
    user->next_space_id++;
    
    SpaceSimulation space = new_space(space_id);
    
    hash_table_insert(user->simulation, space->id, space);
    return space->id;
}



#pragma endregion

#pragma region Particle

#pragma endregion




void free_user(App app)
{
    hash_table_destroy(app->users);
    free(app);
}

void* ValueOfUser(App app, char *name)
{
    return hash_table_get(app->users, name);
}



void register_user(App app, char *name)
{
    User user = new_app(name);
    hash_table_insert(app->users, name, user);
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