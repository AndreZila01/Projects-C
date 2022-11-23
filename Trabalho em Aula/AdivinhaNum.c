#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>  

int answer = 0;
int score = 0;
int attempts = 0;

void reset() {
    answer = 0;
    score = 0;
    attempts = 0;
}

int main() {
    while (true) {
        char *line = NULL;
        size_t len = 0;
        getline(&line, &len, stdin);
        line[strlen(line)-1] = '\0';
        char* command = strtok(line, " ");
        if(strcmp(command, "IJ") == 0) {
            // Verificar se existe um jogo em curso
            if(answer > 0) {
                printf("Já existe um jogo em curso\n");
            }
            else  {
                // Se não existir, criar um novo jogo
                answer = rand() % 100 +0; 
            }
        }
        else if(strcmp(command, "R") == 0) {
            if(answer == 0) {
                // Verificar se existe um jogo em curso
                printf("Não existe um jogo em curso\n");
            }
            else {
                // Incrementar número de tentativas
                attempts++;
                // Ler o número
                char* number = strtok(NULL, " ");
                // Converter para inteiro
                int num = atoi(number);
                // Calcular pontuação
                if(attempts == 1) {
                    score = 10;
                }
                else if(attempts == 2) {
                    score = 5;
                }
                else {
                    score = 2;
                }
                // Comparar com o valor
                if(num == answer) {
                    printf("Acertou! Pontuação: %d\n", score);
                    reset();
                }
                else if(num < answer) {
                    printf("Maior\n");
                    if(attempts == 3) {
                        printf("Perdeu! Pontuação: 0\n");
                        reset();
                    }
                }
                else {
                    printf("Menor\n");
                    if(attempts == 3) {
                        printf("Perdeu! Pontuação: 0\n");
                        reset();
                    }
                }
            }
        }
    }
    return 0;
}