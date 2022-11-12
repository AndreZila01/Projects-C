#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct DadosPessoa
{
    char* Nome[50];
    int Jogos;
    int Vitorias;
};


int main()
{
    /*char value[] = {"dadsa"};

    char str[80] = "This is - www.tutorialspoint.com - website";
    const char s[2] = "-";
    char *token;*/

    /* get the first token */
    //token = strtok(str, s);
    //printf("%s", token);
    while (true)
    {
        char input;
        scanf("%s", &input);
        char* token = strtok(input, ' ');

        if (strcmp(token,"RJ")){
        
            for(int count = 0; count<sizeof(struct DadosPessoa)/sizeof(struct DadosPessoa[0]); count++){
                //if(strcmp(struct DadosPessoa[0].Nome, strtok(token, "")));
            }
            
            
        }
        else if (strcmp(token, "EJ"))
            printf("ds");
        else if (strcmp(token,"LJ"))
            printf("ds");
        else if (strcmp(token, "IJ"))
            printf("ds");
        else if (strcmp(token,"D"))
            printf("ds");
        else if (strcmp(token,"DJ"))
            printf("ds");
        else if (strcmp(token,"CP"))
            printf("ds");
        else if (strcmp(token,"VR"))
            printf("ds");
        else if (strcmp(token,"G"))
            printf("ds");
        else if (strcmp(token,"L"))
            printf("ds");
    }
}