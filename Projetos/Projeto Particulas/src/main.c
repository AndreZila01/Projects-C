#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "auxMain.c"

typedef struct List_ *List;
typedef struct Node_ *Node;

void switchcase(List lst, char* line) {

}
int main()
{
    List lst = list_create();
    while(true){
        char *line = NULL;
        size_t len = 0;
        getline(&line, &len, stdin);
        line[strlen(line) - 1] = '\0';
        if (strlen(line) == 0)
            break;
        switchcase(lst, line);
        free(line);
    }
    return 0;
}
