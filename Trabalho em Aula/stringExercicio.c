#include <stdio.h>
#include <string.h>

int main(){

    char s[] = "IADE - Faculdade de Design Tecnologia e Comunicação";
    int count =0, words=0;
    for(int i=0; i<strlen(s); i++){
        if(s[i]!= ' ' && s[i]!='-')
            count++;
        else{
            if(count>0){
                words++;
                count++;
            }
        }
    }
    printf("A string tem %d palavras!\n", words+1);
    return 0;
}