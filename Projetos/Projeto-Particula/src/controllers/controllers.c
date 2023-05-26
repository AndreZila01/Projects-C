#include "controllers.h"
#include "../models/models.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

App app_new()
{
    App app = malloc(sizeof(tApp));
    app->users = hash_table_create(0, app_hash_ints, equal_ints, NULL, (void (*)(void *))free_user);
    return app;
}

void list_user(App app)
{
    // List user_list = hash_table_values(app->users);
    // int size = list_size(user_list);

    // void *value = hash_table_values(usern);
    // int lenght = hash_table_size(usern), val = 0;

    // não consigo ter o node desta solução??
    // while (lenght != val)
    // {
    //     printf("Espaço de simulação registado com identificador %s.\n", value); // Corrigir-me coletar o valor do identificador
    //     val++;
    // }
}

void app_free_app(App app)
{
    hash_table_destroy(app->users);
    free(app);
}

int app_hash_ints(void *key, int size)
{
    int *k = (int *)key;
    return *k % size;
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
    hash_table_remove(app->users, name);
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

void app_register_simulation(App app, char *user_name)
{
    register_simulation(hash_table_get(app->users, user_name));
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

bool app_has_simulation(App app, char *name)
{
    return has_simulation(hash_table_get(app->users, name), name) != NULL;
}

int app_SizeOfHash(App usern)
{
    return hash_table_size(usern->users);
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
        if (!app_has_simulation(app->users, name))
            printf("Espaço de simulação inexistente.\n");
        else
        {
            if (massa >= 0)
            {
                SpaceSimulation sim = (return_simulation(app->users, name));
                Particle part = malloc(sizeof(Particle_));
                part->carga = massa;
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

                hash_table_insert(sim, name, part);
                printf("Partícula registada com identificador IdentificadorParticula.\n");
            }
            else
                printf("Massa inválida.\n");
        }
    }
}

void app_Modify_Part(app, name, IdenSpace, IdenPart, massa, carga, pix, piy, piz, vx, vy, vz){
    //FAZER AP
}