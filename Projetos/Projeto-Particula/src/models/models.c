#define _XOPEN_SOURCE 500
#include "models.h"
#include "../utils/hash_table.h"
#include "fisica.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void free_key(void *key)
{
    free(key);
}

void free_value(void *value)
{
    free(value);
}

bool equal_ints(void *key1, void *key2)
{
    int *k1 = (int *)key1;
    int *k2 = (int *)key2;
    return *k1 == *k2;
}

int hash_space_id(void *key, int size)
{
    int *k = (int *)key;
    return *k % size;
}

void space_free(void *space)
{
    SpaceSimulation s = (SpaceSimulation)space;
    hash_table_destroy(s->particle);
    free(s->id);
    free(s);
}

User new_user(char *name)
{
    User user = malloc(sizeof(User_));
    user->name = strdup(name);
    user->simulation_on = false;
    user->next_space_id = 1;
    user->Spacesimulation = hash_table_create(0, hash_space_id, equal_ints, NULL, space_free);
    return user;
}

void free_user(User user)
{
    hash_table_destroy(user->Spacesimulation);
    free(user->name);
    free(user);
}

void free_Simulacao(SpaceSimulation space)
{
    free(space->id);
    hash_table_destroy(space->particle);
    free(space);
    // TODO: Falta atualizar para os novos campos de User.
}

char *register_simulation(User user)
{
    // // User user = hash_table_get(users, user_name);
    // //  0. Criar o identificador de espaço
    // char space_id[80];
    // // int space_id;
    // sprintf(space_id, "%d", user->next_space_id);
    // SpaceSimulation space = new_space(user->next_space_id);
    // user->next_space_id++;

    // hash_table_insert(user->Spacesimulation, space->id, space);
    // // return space->id;

    // User user = hash_table_get(app->users, user_name);

    char space_id[80];
    sprintf(space_id, "%d", user->next_space_id);
    user->next_space_id++;

    SpaceSimulation space = new_space(space_id);

    hash_table_insert(user->Spacesimulation, space->id, space);
    return space->id;
}

SpaceSimulation new_space(char *id)
{
    SpaceSimulation space = malloc(sizeof(SpaceSimulation_));
    space->id = strdup(id);
    return space;
}

void free_Particle(SpaceSimulation space)
{
    free(space->particle);
    free(space);
}

void free_Space(User user)
{
    free(user->Spacesimulation);
    free(user->name);
    free(user);
}

bool has_simulation(User user, char *name)
{
    return hash_table_get(user->Spacesimulation, name) != NULL;
}

bool has_Particle(SpaceSimulation sim, char *name)
{
    return hash_table_get(sim->particle, name) != NULL;
}

int SpaceSimulationCount(void *values)
{
    User user = (User)values;
    int value = hash_table_size(user->Spacesimulation);
    return value;
    // return (SpaceSimulation(hash_table_size(user->Spacesimulation)))->SpaceSimulationCount;
}

bool Simulation_OnOff(User user)
{
    return user->simulation_on;
}

int size_Particle(SpaceSimulation sim)
{
    return hash_table_size(sim->particle);
}

void *return_simulation(User user, char *name)
{
    return hash_table_get(user->Spacesimulation, name);
}

void *ConvertArray(List lst, int userCount)
{
    // User *user = (User)malloc(sizeof(User) * userCount);

    // int i = 0;
    // list_iterator_start(lst);
    // while (list_iterator_has_next(lst))
    //     user[i++] = list_iterator_get_next(lst);

    // Convert the list to an array
    void *array = malloc(sizeof(User) * userCount);
    list_to_array(lst, array);

    return array;
}

void Modify_Part(User user, char *name, char *IdenSpace, char *IdenPart, float massa, float carga, float pix, float piy, float piz, float vx, float vy, float vz)
{
    SpaceSimulation simulacao = hash_table_get(user->Spacesimulation, IdenSpace);

    if (simulacao == NULL)
        printf("Espaço de simulação inexistente.\n"); // meter isto numa funcao que faca check e retorne se existir
    else
    {
        Particle part = hash_table_get(simulacao->particle, IdenPart);
        if (simulacao == NULL)
            printf("Partícula inexistente.\n");
        else
        {
            if (pix == 0 && piy == 0 && piz == 0)
            {
                hash_table_remove(simulacao->particle, part->NomeUser);
                printf("Partícula removida com sucesso.\n");
            }
            else
            {
                if (massa > 0)
                {
                    part->massa = massa;
                    part->NomeUser = name;
                    part->carga = carga;
                    part->x = pix;
                    part->y = piy;
                    part->z = piz;
                    part->Vx = vx;
                    part->Vy = vy;
                    part->Vz = vz;

                    printf("Partícula alterada com sucesso.\n");
                }
                else
                    printf("Massa inválida.\n");
            }
        }
    }
}

void printformulas(User user, char *IdentificadorEspaço, char *IdentificadorParticula, int tempo, int passo, char *files)
{
    FILE *file;
    if (strcmp(files, "-") == 0)
    {
        file = stdout; // Mostrar na consola
    }
    else
    {
        file = fopen(files, "w"); // Abrir arquivo para escrita
        if (file == NULL)
        {
            printf("Erro ao abrir o arquivo %s\n", files);
        }
    }

    float xi = 0, yi = 0, zi = 0, vix = 0, viy = 0, viz = 0, fgx = 0, fgy = 0, fgz = 0, fex = 0, fey = 0, fez = 0, SFx = 0, SFy = 0, SFz = 0, acx = 0, acy = 0, acz = 0;
    Particle partdinamica = hash_table_get(hash_table_get(user->Spacesimulation, IdentificadorEspaço), IdentificadorParticula);
    xi = partdinamica->x;
    yi = partdinamica->y;
    zi = partdinamica->z;
    vix = partdinamica->Vx;
    viy = partdinamica->Vy;
    viz = partdinamica->Vz;

    int value = hash_table_size(((SpaceSimulation)(hash_table_get(user->Spacesimulation, IdentificadorEspaço)))->particle);

    for (int vs = 0; vs < value; vs++)
    {
        Particle partestatic = hash_table_get(((SpaceSimulation)(hash_table_get(user->Spacesimulation, IdentificadorEspaço)))->particle, "" + vs); // mal feito
        for (int temp = 0; temp <= tempo; temp++)
        {
            if (temp != 0)
            {
                partdinamica->x = /*fabs*/ (FPosicao(xi, partdinamica->Vx, temp));
                partdinamica->Vx = /*fabs*/ (FVeloc(xi, FPosicao(xi, vix, temp), 0, tempo)); // a velocidade tb muda, sempre??
                fgx = /*fabs*/ (FForcaGraf(partdinamica->massa, partestatic->massa, distancia(partdinamica, partestatic)));
                fex = /*fabs*/ (FForceElet(partdinamica->massa, partestatic->massa, distancia(partdinamica, partestatic))); // como calcular
                SFx = /*fabs*/ (fgx + fex);
                acx = /*fabs*/ (FAcelaracao(SFx, partestatic->massa));

                // acy = FAcelaracao(yi, part1->Vy, temp, part1->y); // está sempre a mudar???
                partdinamica->y = /*fabs*/ (FPosicao(yi, partdinamica->Vy, temp));
                partdinamica->Vy = /*fabs*/ (FVeloc(yi, FPosicao(yi, viy, temp), 0, tempo)); // a velocidade tb muda, sempre??
                fgy = /*fabs*/ (FForcaGraf(partdinamica->massa, partestatic->massa, distancia(partdinamica, partestatic)));
                fey = /*fabs*/ (FForceElet(partdinamica->massa, partestatic->massa, distancia(partdinamica, partestatic))); // como calcular
                SFy = /*fabs*/ (fgy + fey);
                acy = /*fabs*/ (FAcelaracao(SFy, partdinamica->massa));

                // acz = FAcelaracao(zi, part1->Vz, temp, part1->z); // está sempre a mudar???
                partdinamica->z = /*fabs*/ (FPosicao(zi, partdinamica->Vz, temp));
                partdinamica->Vz = /*fabs*/ (FVeloc(zi, FPosicao(zi, viz, temp), 0, tempo)); // a velocidade tb muda, sempre??
                fgz = /*fabs*/ (FForcaGraf(partdinamica->massa, partestatic->massa, distancia(partdinamica, partestatic)));
                fez = /*fabs*/ (FForceElet(partdinamica->massa, partestatic->massa, distancia(partdinamica, partestatic))); // como calcular
                SFz = /*fabs*/ (fgz + fez);
                acz = /*fabs*/ (FAcelaracao(SFz, partdinamica->massa)); // está sempre a mudar???
            }
            if (tempo % passo == 0)
                printf("%d, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e", temp, partdinamica->x, partdinamica->y, partdinamica->z, partdinamica->Vx, partdinamica->Vy, partdinamica->Vz, acx, acy, acz, fgx);
            printf(", %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e, %6.3e \n", fgy, fgz, fex, fey, fez, SFx, SFy, SFz);
            free(partestatic);
        }
        ((SpaceSimulation)hash_table_get(user->Spacesimulation, IdentificadorEspaço))->SimulationCount++;

        free(partdinamica);
    }

    if (file != stdout)
    {
        fclose(file);
    }
}

// int CountUser(User user){
//     return
// }