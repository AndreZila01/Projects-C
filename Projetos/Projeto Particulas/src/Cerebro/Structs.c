#ifndef Struct
#define Struct

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    int idParticula; // particula do user, neste caso o size
    char * NomeUser;
} Espaco_, *Espaco_;

typedef struct
{
    int idParticula; // particula do user, neste caso o size
    char * NomeUser;
    int massa;
    int carga;
    float x;//posição em x
    float y;//posição em y
    float z;//posição em z
    float Vx;//velocidade em x
    float Vy;//velocidade em y
    float Vz;//velocidade em z
} Particula_, *Particula;

#endif