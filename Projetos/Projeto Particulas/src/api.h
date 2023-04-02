#include "Structs.c"

#ifndef Api
#define Api

typedef struct List_ *List;

bool CheckEmpty(List list)
{
    return list->size == 0 ? true : false;
}

bool CheckExistSameName(List list, char *name)
{
    Node node = list->head;
    int check = 0;
    while (node != NULL)
    {
        if (CheckEqualString(node->element, name))
            return true;
    }
    return false;
}

bool CheckEqualString(void *Nome1, char *Nome2)
{
    return strcmp((char* )Nome1, Nome2) == 0 ? false : true;
}

#endif