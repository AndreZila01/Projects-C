#ifndef MODELS_H
#define MODELS_H

#include "../utils/hash_table.h"

typedef struct {
    char* name;
    HashTable simulation_spaces;
    // TODO: Mais coisas...
} tUser, *User;

User new_user(char* name);

void free_user(User user);

#endif