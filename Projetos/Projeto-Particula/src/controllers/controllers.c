#include "controllers.h"
#include "../models/models.h"

#include <stdlib.h>
#include <string.h>

App new_app() {
    App app = malloc(sizeof(tApp));
    app->users = hash_table_create(0, app_has_user, equal_ints, NULL, (void (*)(void*))free_user);
    return app;
}


void free_app(App app) {
    hash_table_destroy(app->users);
    free(app);
}

bool app_has_user(App app, char* name) {
    return hash_table_get(app->users, name) != NULL;
}

void app_register_user(App app, char* name) {
    User user = new_user(name);
    hash_table_insert(app->users, name, user);
}

void app_register_space(App app, char* user_name) {
    register_space(hash_table_get(app->users, user_name), user_name);
}

bool app_has_user(App app, char *name){

}


User app_new_simulation(){

}

void app_free_simulation(User usern){

}

bool app_has_simulation(User usern, char *name){

}

void app_register_simulation(User usern, char *name){

}

int app_SizeOfHash(App usern){

}

SpaceSimulation app_new_space(){

}

void app_free_space(SpaceSimulation app){

}

bool app_has_space(SpaceSimulation app, char* name){

}


Particle app_new_Part(){

}

void app_free_Part(Particle part){

}

bool app_has_Part(Particle part, int * idParticula, char *NomeUser, int massa, int carga, float x, float y, float z, float Vx, float Vy, float Vz){

}

void app_register_Part(Particle part, char *name){

}


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

// #pragma endregion