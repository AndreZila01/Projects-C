#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char *Nome;
    int Vitoria;
    int Jogadas;
} jogador, *LstJogador;

typedef struct
{
    LstJogador *Jogadores;
    int **Tabuleiro;
    char *dimensao;
    char *Jogador0;
    char *Jogador1;
    int LenghPlayers;
    bool EstadoJogo; // false - Por Inciar || true - A decorrer
} game, *LstGame;

// int* myArray = calloc(16, sizeof(int)); VER O QUE FAZ

bool RJ(char *Name, LstGame gam)
{
    for (int count = 0; count < gam->LenghPlayers; count++)
    {
        if (strcmp(gam->Jogadores[count]->Nome, Name) == 0)
            return false;
    }

    LstJogador player = (LstJogador)malloc(sizeof(jogador));
    strcpy(player->Nome, Name);
    player->Vitoria = 0;
    player->Jogadas = 0;

    gam->LenghPlayers++;
    gam->Jogadores = realloc(gam->Jogadores, sizeof(LstJogador) * gam->LenghPlayers);
    gam->Jogadores[gam->LenghPlayers - 1] = player;
    return true;
}

int FindIndex(char *Nome, LstGame gam)
{
    for (int count = 0; count < gam->LenghPlayers; count++)
        if (strcmp(gam->Jogadores[count]->Nome, Nome) == 0)
            return count;

    return -1;
}

char *EJ(char *Nome, LstGame gam)
{
    int index = FindIndex(Nome, gam);
    if (index != -1)
    {
        for (int count = index; count < gam->LenghPlayers; count++)
           gam->Jogadores[count] = gam->Jogadores[gam->LenghPlayers + 1];

        return "Jogador removido com sucesso.";
    }
    else
        return "Jogador não existente.\n";

    //  -> Se Remover com sucesso imprime, "Jogador removido com sucesso.";
    //-> Se o jogador não existir imprimir, "Jogador não existente";
    //-> Se jogador está a participar num jogo em curso imprime, "Jogador participa no jogo em curso.";
    return "Jogador removido com sucesso.\n";
}

bool LJ(LstGame gam)
{
    if (gam->Jogadores[0]->Nome == 0x0)
        return false;
    for (int count = 0; count < gam->LenghPlayers - 1; count++)
        if (gam->Jogadores[count]->Nome != 0x0)
            printf("%s %d %d\n", gam->Jogadores[count]->Nome, gam->Jogadores[count]->Jogadas, gam->Jogadores[count]->Vitoria);
    return true;
}

void D(char *Utilizador, int idUtiliz)
{
}

void reset_game(LstGame game)
{
    game->Tabuleiro = NULL;
    game->Jogador0 = NULL;
    game->Jogador1 = NULL;
    game->EstadoJogo = false;
}

bool CheckWin(int numjogador, int coluna, int linha, char *sentido, LstGame gam)
{

    int linhaigual = 0;
    for (int value = linha - 4; value <= linha + 4; value++)
    {
        if (linha > 19)
            break;
        if (linha > -1)
        {
            if (gam->Tabuleiro[coluna][value] == numjogador)
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
            if (gam->Tabuleiro[value][linha] == numjogador)
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
            if (gam->Tabuleiro[coluna + value][linha + value] == numjogador)
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
        if (gam->Tabuleiro[coluna - value][linha - value] == numjogador)
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

char *ColocarPeca(int numbjogador, int coluna, char *sentido, int tamanhopeca, LstGame gam)
{
    char *v = strtok(("%s", gam->dimensao), ",");
    int col = (strcmp(sentido, "D") == 0) ? coluna : (coluna - (atoi(strtok(NULL, ","))));
    /*if (strcmp(sentido, "D") == 0)
        col = 20 - coluna;
    else
        col = coluna;*/
    int linha = -1;
    for (int count = 19; count < 20; count--)
        if (gam->Tabuleiro[col][count] == -1 || gam->Tabuleiro[col][count] == 0)
        {
            gam->Tabuleiro[col][count] = numbjogador;
            linha = count;
            break;
        }

    bool s = CheckWin(numbjogador, col, linha, sentido, gam);
}

int **sendboard(char *filename, LstGame gam)
{
    FILE *fp = fopen(filename, "r");

    char line[40];
    fgets(line, 40, fp);
    int *w = atoi(strtok(line, ","));
    int *h = atoi(strtok(NULL, ","));

    gam->dimensao = "%cx%c", *w, *h;

    int **board = malloc(sizeof(int *) * *w);

    for (int i = 0; i < *w; i++)
        board[i] = malloc(sizeof(int) * *h);

    int board_line_size = *w * 3 + 1;
    char *board_line = malloc(sizeof(char) * (board_line_size + 1));
    int row = 0, col = 0;
    while (fgets(board_line, board_line_size, fp))
    {
        char *command = strtok(board_line, ",");
        col = 0;
        board[row][col] = atoi(command);
        for (int col = 1; col < *w - 1; col++)
            board[row][col] = atoi(strtok(NULL, ","));

        row++;
    }

    free(board_line);
    return board;
}

void IJ()
{
}

void switchcase(char *linha, LstGame gam, LstJogador jog)
{

    char *comando = strtok(linha, " "); //.Split(new string [] {""}, none);
    if (strcmp(comando, "RJ") == 0)     // strcmp irá comparar o primeiro espaçamento com IJ, se for verdade retorna 0
    {
        if (RJ(strtok(NULL, " "), gam) == true)
            printf("Jogador registado com sucesso.\n");
        else
            printf("Jogador existente.\n");
    }
    else if (strcmp(comando, "EJ") == 0)
    {
        char *mensagem = EJ(strtok(NULL, " "), gam);
        // https://codeforwin.org/2015/07/c-program-to-delete-element-from-array.html
        printf("%s", mensagem);
    }
    else if (strcmp(comando, "LJ") == 0)
        LJ(gam);
    else if (strcmp(comando, "D") == 0)
    {
        char *utilizadorD = strtok(NULL, " ");
        int idUtilizador = (FindIndex(utilizadorD, gam));
        if (gam->EstadoJogo == false)
            printf("Não existe jogo em curso.");
        else if ((gam->Jogador1 == utilizadorD) || (gam->Jogador0 == utilizadorD) && idUtilizador != -1)
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

        if (strcmp(jogador, gam->Jogador0) == 0)
            numb = 0;
        else
            numb = 1;

        ColocarPeca(numb, coluna, sentido, tamanho, gam);
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
    LstJogador player = malloc(sizeof(jogador));
    player->Nome = NULL;
    player->Vitoria = -1;
    player->Jogadas = -1;
    LstGame game = malloc(sizeof(game));
    game->Jogadores = NULL;
    game->LenghPlayers = 0;

    reset_game(game);
    while (true)
    {
        char *line = NULL;             // variavel string apontador
        size_t len = 0;                // É um "long", que conta bytes
        getline(&line, &len, stdin);   // geline() -> função para recolher texto stdin -> é um ponteiro do tipo FILE *
        line[strlen(line) - 1] = '\0'; // remover o \n
        switchcase(line, &game, &player);
    }
    return 0;
}