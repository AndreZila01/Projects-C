#include "controllers.h"
#include "../models/models.h"
#include "../utils/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

App app_new()
{
    App app = malloc(sizeof(tApp));
    app->users = hash_table_create(0, NULL, NULL, NULL, (void (*)(void *))free_user);
    return app;
}

// void list_user(App app)
// {
// List user_list = hash_table_values(app->users);
// int size = list_size(user_list);
// User *user_array = malloc(sizeof(User) * size);
// for (int i = 0; i < size; i++)
// {
//     user_array[i] = (User)list_get(user_list, i);
// }
// qsort(user_array, size, sizeof(User), compare_users);

// list_free(user_list);

// return user_array;
//  List user_list = hash_table_values(app->users);
//  int size = list_size(user_list);

// void *value = hash_table_values(usern);
// int lenght = hash_table_size(usern), val = 0;

// não consigo ter o node desta solução??
// while (lenght != val)
// {
//     printf("Espaço de simulação registado com identificador %s.\n", value); // Corrigir-me coletar o valor do identificador
//     val++;
// }
// }

int compareUsersByName(void *Namea, void *Nameb)
{
    // char* user1 = (char*)Namea;
    // char* user2 = (char*)Nameb;
    // return strcmp(user1, user2);
    User *user1 = (User *)Namea;
    User *user2 = (User *)Nameb;
    return strcmp((*user1)->name, (*user2)->name);
}

int compare_users(const void *a, const void *b)
{
    const User user1 = *(const User *)a;
    const User user2 = *(const User *)b;
    return strcmp(user1->name, user2->name);
}

void app_free_app(App app)
{
    hash_table_destroy(app->users);
    free(app);
}

void app_free(App app)
{
    // Meter remover espaço
    hash_table_destroy(app->users);
    free(app);
}

void app_free_space(App app)
{
    // Meter remover espaço
    hash_table_destroy(app->users);
    free(app);
}

void app_remove_user(App app, char *name)
{
    // User user = hash_table_remove(app->users, name);
    // free_user(user);
    free_user(hash_table_get(app->users, name));
}

bool app_has_user(App app, char *name)
{
    return hash_table_get(app->users, name) != NULL;
}

void app_register_user(App app, char *name)
{
    User user = new_user(name);
    hash_table_insert(app->users, user->name, user);
}

void *app_register_simulation(App app, char *user_name)
{
    return register_simulation(hash_table_get(app->users, user_name));
}

void *app_ValueOfUser(App app, char *name)
{
    return hash_table_get(app->users, name);
}

// void* app_ValueOfUsers(App app)
//{
// return hash_table_get();
//}

// User app_new_simulation(App app, char* name){

// }

void app_free_simulation(App app, char *name)
{
    free_Space(hash_table_get(app->users, name));
}

bool app_has_simulation(App app, char *name, char* iden)
{
    return has_simulation(app_ValueOfUser(app, name), iden);
}

int app_SizeOfHash(App usern)
{
    return hash_table_size(usern->users);
}

int app_spacesCount(void *user)
{
    return SpaceSimulationCount(user);
}

// SpaceSimulation app_new_space(){

// }

// void app_free_space(SpaceSimulation app){

// }

// bool app_has_space(SpaceSimulation app, char* name){

// }

// Particle app_new_Part(){

// }

// void app_free_Part(Particle part){

// }

// bool app_has_Part(Particle part, int * idParticula, char *NomeUser, int massa, int carga, float x, float y, float z, float Vx, float Vy, float Vz){

// }

// void app_register_Part(Particle part, char *name){

// }

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

void app_Registar_Part(App app, char *name, char *identifi, float massa, float carga, float pix, float piy, float piz, float vx, float vy, float vz)
{
    if (!app_has_user(app, name))
        printf("Utilizador inexistente.\n");
    else
    {
        if (!app_has_simulation(app, name, identifi))
            printf("Espaço de simulação inexistente.\n");
        else
        {
            if (massa >= 0)
            {
                User user = hash_table_get(app->users, name);
                SpaceSimulation sim = (return_simulation(user, identifi));
                Particle part = malloc(sizeof(Particle_));
                part->carga = carga;
                part->idParticula = hash_table_size(sim->particle);
                // user->space->particula->quantidadeparticula
                part->massa = massa;
                part->NomeUser = name;
                part->Vx = vx;
                part->Vy = vy;
                part->Vz = vz;
                part->x = pix;
                part->y = piy;
                part->z = piz;

                hash_table_insert(sim->particle, name, part);
                printf("Partícula registada com identificador %d.\n", part->idParticula);
            }
            else
                printf("Massa inválida.\n");
        }
    }
}

void app_Modify_Part(App app, char *name, char *IdenSpace, char *IdenPart, float massa, float carga, float pix, float piy, float piz, float vx, float vy, float vz)
{
    if (app_has_user(app, name))
        Modify_Part(hash_table_get(app->users, name), name, IdenSpace, IdenPart, massa, carga, pix, piy, piz, vx, vy, vz);
    else
        printf("Utilizador inexistente.\n");
}

int app_user_simulatorCount(void *user)
{
    return SpaceSimulationCount(user);
}

void *app_ConvertUserToArray(App app, int userCount)
{
    return ConvertArray(hash_table_values(app->users), userCount); // TODO: de certo modo fazer free do valor hash_tables_values
}

void app_Simulate(App app, char *name, char *IdentificadorEspaço, char *IdentificadorParticula, int tempo, int passo, char *file)
{
    if (app_has_user(app, name))
        printformulas(hash_table_get(app->users, name), IdentificadorEspaço, IdentificadorParticula, tempo, passo, file);
    else
        printf("Utilizador inexistente.\n");
}

int app_CounterUser(App app)
{
    return hash_table_size(app->users);
}

bool app_Simulation_OnOff(App app, char *name)
{
    return (!Simulation_OnOff(hash_table_get(app->users, name)));
}