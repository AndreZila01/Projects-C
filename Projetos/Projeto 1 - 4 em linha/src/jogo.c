#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int tabuleiro[20][20];
int test(char* comando, char* line)
{
    comando = strtok(line, "[");
    line[strlen(line) - 1] = '\0';
    int lin = atoi(strtok(line, ","));
    int col = atoi(strtok(NULL, ","));
    for (int cols = 0; cols < col; cols++)
    {
    }

    return -1;
}
int main()
{
    char *tabuleiro = "[0,0](-1)\t[0,1](-1)\t[0,2](-1)\t[0,3](-1)\t[0,4](-1)\t[0,5](-1)\t[0,6](-1)\t[0,7](-1)\t[0,8](-1)\t[0,9](-1)\t[0,10](-1)\n[1,0](-1)\t[1,1](-1)\t[1,2](-1)\t[1,3](-1)\t[1,4](-1)\t[1,5](-1)\t[1,6](-1)\t[1,7](-1)\t[1,8](-1)\t[1,9](-1)\t[1,10](-1)\n[2,0](-1)\t[2,1](-1)\t[2,2](-1)\t[2,3](-1)\t[2,4](-1)\t[2,5](-1)\t[2,6](-1)\t[2,7](-1)\t[2,8](-1)\t[2,9](-1)\t[2,10](-1)\n";

    while (true)
    {
        char *line = NULL;
        size_t len = 0;
        getline(&line, &len, stdin);
        const char *text = line;
        char *comando = strtok(line, " ");//.SPLIT
        if (strcmp(comando, "CP") == 0)
        {
            int value = test(comando, line);
        }
    }
}