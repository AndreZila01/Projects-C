#ifndef Struct
#define Struct

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node_ *Node;
typedef struct NodeP_ *NodeP;

struct Node_
{
    Node next;
    void *element;
};

struct List_
{
    Node head;
    Node tail;
    int size;
};

struct Particula
{
    //int idParticula; // particula do user, neste caso o size
    char * NomeUser;
    int massa;
    int carga;
    float x;//posição em x
    float y;//posição em y
    float z;//posição em z
    float Vx;//velocidade em x
    float Vy;//velocidade em y
    float Vz;//velocidade em z
};

#endif