#ifndef Api
#define Api

#include "Structs.h"
#include <string.h>

typedef struct List_ *List;
typedef struct Node_ *Node;



bool CheckEmpty(List list)
{
    return list->size == 0;
}

bool CheckEqualString(void *Nome1, char *Nome2)
{
    return strcmp((char *)Nome1, Nome2) == 0;
}

#endif