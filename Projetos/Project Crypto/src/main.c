#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

int main()
{
    FILE *file;
    file = fopen("btc.txt", "r+");
    if (CheckFile(file))
        ReadFile(file);

    return 0;
}