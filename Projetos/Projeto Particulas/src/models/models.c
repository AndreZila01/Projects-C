#include "models.h"

#include <stdlib.h>

#define _XOPEN_SOURCE 500
#include <string.h>

User new_user(char* name) {
    User user = malloc(sizeof(tUser));
    user->name = strdup(name);
    return user;
}

void free_user(User user) {
    free(user->name);
    free(user);
    // TODO: Falta atualizar para os novos campos de User.
}