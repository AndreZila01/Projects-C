#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

struct Jogador
{
    char *Nome;
    int Vitoria;
    int Jogadas;
} jogador[50];
struct JogoAtivo
{
    int Tabuleiro[50][50];
    char *Jogador0;
    char *Jogador1;
    bool Jogando; // false - Por Inciar || true - A decorrer
} Ativo[1];

struct Jogador jogador[50];

// int* myArray = calloc(16, sizeof(int)); VER O QUE FAZ

bool RJ(char *Name)
{
    for (int count = 0; count < (sizeof jogador / sizeof jogador[0]); count++)
        if (jogador[count].Nome != 0x0)
        {
            if (strcmp(jogador[count].Nome, Name) == 0)
                return false;
        }
        else
        {
            jogador[count].Vitoria = 0;
            jogador[count].Jogadas = 0;
            jogador[count].Nome = Name;
            return true;
        }
}

bool LJ()
{
    if (jogador[0].Nome == 0x0)
        return false;
    for (int count = 0; count < (sizeof jogador / sizeof jogador[0]); count++)
        if (jogador[count].Nome != 0x0)
            printf("%s %d %d", jogador[count].Nome, jogador[count].Jogadas, jogador[count].Vitoria);
    return true;
}

int FindIndex(char *Nome)
{
    for (int count = 0; count < (sizeof jogador / sizeof jogador[0]); count++)
        if (jogador[count].Nome != 0x0)
            if (strcmp(jogador[count].Nome, Nome) == 0)
                return count;

    return -1;
}

char *EJ(char *Nome)
{
    int index = FindIndex(Nome);
    if (index != -1)
    {
        for (int count = index; count <= (sizeof jogador / sizeof jogador[0]); count++)
        {
            jogador[count] = jogador[count + 1];
        }
    }
    else
        return "Jogador não existente.\n";

    //  -> Se Remover com sucesso imprime, "Jogador removido com sucesso.";
    //-> Se o jogador não existir imprimir, "Jogador não existente";
    //-> Se jogador está a participar num jogo em curso imprime, "Jogador participa no jogo em curso.";
    return "Jogador removido com sucesso.\n";
}
void D(char *Utilizador, int idUtiliz)
{
}

bool CheckWin(int numjogador, int coluna, int linha, char *sentido)
{

    int linhaigual = 0;
    for (int value = linha - 4; value <= linha + 4; value++)
    {
        if (linha > 19)
            break;
        if (linha > -1)
        {
            if (Ativo[0].Tabuleiro[coluna][value] == numjogador)
                linhaigual++;
            else
                linhaigual = 0;

            if (linhaigual == 4)
            {
                printf("Acabou o jogo\n");
                break;
            }
        }
    }

    for (int value = coluna - 4; value <= coluna + 4; value++)
    {
        if (coluna > 19)
            break;

        if (coluna > -1)
        {
            if (Ativo[0].Tabuleiro[value][linha] == numjogador)
                linhaigual++;
            else
                linhaigual = 0;

            if (linhaigual == 4)
            {
                printf("Acabou o jogo\n");
                break;
            }
        }
    }

    for (int value = -4; value <= 4; value++)
    {
        if (coluna + value > 19 & linha + value > 19)
            break;
        if (coluna + value > -1 && linha + value > -1)
        {
            if (Ativo[0].Tabuleiro[coluna + value][linha + value] == numjogador)
                linhaigual++;
            else
                linhaigual = 0;

            if (linhaigual == 4)
            {
                printf("Acabou o jogo\n");
                break;
            }
        }
    }
    for (int value = 0; value <= 6; value++)
    {
        if (Ativo[0].Tabuleiro[coluna - value][linha - value] == numjogador)
            linhaigual++;
        else
            linhaigual = 0;

        if (linhaigual == 3)
        {
            printf("Acabou o jogo\n");
            break;
        }
    }
}

char *ColocarPeca(int numbjogador, int coluna, char *sentido, int tamanhopeca)
{
    
    int col = (strcmp(sentido, "D") == 0) ? (sizeof Ativo[0].Tabuleiro / sizeof Ativo[0].Tabuleiro[0][0])-coluna : coluna;
    int col = -1;
    if (strcmp(sentido, "D") == 0)
        col = 20 - coluna;
    else
        col = coluna;
    int linha = -1;
    for (int count = 19; count < 20; count--)
        if (Ativo[0].Tabuleiro[col][count] == -1 || Ativo[0].Tabuleiro[col][count] == 0)
        {
            Ativo[0].Tabuleiro[col][count] = numbjogador;
            linha = count;
            break;
        }

    bool s = CheckWin(numbjogador, col, linha, sentido);
}

void switchcase(char *linha)
{

    char *comando = strtok(linha, " "); //.Split(new string [] {""}, none);
    if (strcmp(comando, "RJ") == 0)     // strcmp irá comparar o primeiro espaçamento com IJ, se for verdade retorna 0
    {
        if (RJ(strtok(NULL, " ")) == true)
            printf("Jogador registado com sucesso.\n");
        else
            printf("Jogador existente.\n");
    }
    else if (strcmp(comando, "EJ") == 0)
    {
        char *mensagem = EJ(strtok(NULL, " "));
        // https://codeforwin.org/2015/07/c-program-to-delete-element-from-array.html
        printf("%s", mensagem);
    }
    else if (strcmp(comando, "LJ") == 0)
        LJ();
    else if (strcmp(comando, "D") == 0)
    {
        char *utilizadorD = strtok(NULL, " ");
        int idUtilizador = (FindIndex(utilizadorD));
        if (Ativo[0].Jogando == false)
            printf("Não existe jogo em curso.");
        else if ((Ativo[0].Jogador1 == utilizadorD) || (Ativo[0].Jogador0 == utilizadorD) && idUtilizador != -1)
        {
            D(utilizadorD, idUtilizador);
            printf("Desistência com sucesso. Jogo Terminado");
        }
        else
            printf("Não existe jogo em curso.");
    }
    else if (strcmp(comando, "IJ") == 0)
    {
        // Iniciar Jogo
    }
    else if (strcmp(comando, "CP") == 0)
    {
        char *jogador = strtok(NULL, " ");
        int tamanho = atoi(strtok(NULL, " "));
        int coluna = atoi(strtok(NULL, " "));
        char *sentido = strtok(NULL, " ");

        /*int numb = strcmp(jogador,Jogador1)==0 ? numb = 0 : numb = 1;*/
        int numb = 0;

        if (strcmp(jogador, Ativo[0].Jogador0) == 0)
            numb = 0;
        else
            numb = 1;

        ColocarPeca(numb, coluna, sentido, tamanho);
    }
    else if (strcmp(comando, "VR") == 0)
    {
        // Visualizar Result
    }
    else if (strcmp(comando, "G") == 0)
    {
        FILE *fptr;
        fptr = fopen("fprintf_test.txt", "w+");
        fprintf(fptr, "Learning C with Guru99\n");
        fclose(fptr);
    }
    else if (strcmp(comando, "L") == 0)
    {
        FILE *fp;
        char *buff;
        fp = fopen("fprintf_test.txt", "r");
        fgets(buff, 100000, (FILE *)fp);
        printf("%s\n", buff);
        fclose(fp);
    }
    else
        printf("O valor inserido nao tem correspondencia.\n");
}

int main()
{
    while (true)
    {
        char *line = NULL;             // variavel string apontador
        size_t len = 0;                //É um "long", que conta bytes
        getline(&line, &len, stdin);   // geline() -> função para recolher texto stdin -> é um ponteiro do tipo FILE *
        line[strlen(line) - 1] = '\0'; // remover o \n
        switchcase(line);
    }
    return 0;
}