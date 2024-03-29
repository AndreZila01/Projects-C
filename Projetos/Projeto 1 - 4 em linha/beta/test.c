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
    char *TamanhoPeca;
    int Comprimento;
    int Sequencia;
    int Altura; // Tamanho de sequencia
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

        realloc(gam->Jogadores, sizeof(LstJogador) * gam->LenghPlayers - 1);
        return "Jogador removido com sucesso.";
    }
    else
        return "Jogador não existente.\n";

    //  -> Se Remover com sucesso imprime, "Jogador removido com sucesso.";
    //-> Se o jogador não existir imprimir, "Jogador não existente";
    //-> Se jogador está a participar num jogo em curso imprime, "Jogador participa no jogo em curso.";
}

bool LJ(LstGame gam)
{
    if (gam->LenghPlayers == 0)
        return false;
    for (int count = 0; count < gam->LenghPlayers - 1; count++)
        if (gam->Jogadores[count]->Nome != 0x0)
            printf("%s %d %d\n", gam->Jogadores[count]->Nome, gam->Jogadores[count]->Jogadas, gam->Jogadores[count]->Vitoria);
    return true;

    //ORDENAR ALFABETICAMENTE
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
    game->Altura = -1;
    game->Comprimento = -1;
    game->Sequencia = 0;
    game->TamanhoPeca = NULL;
}

bool CheckWin(int numjogador, int coluna, int linha, char *sentido, LstGame gam)
{

    int linhaigual = 0;
    for (int value = linha -4; value <= linha + 4; value++)
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

char *CP(int numbjogador, int coluna, char *sentido, int tamanhopeca, LstGame gam)
{
    //char *v = strtok(("%s", gam->dimensao), ",");
    int col = (strcmp(sentido, "D") == 0) ? coluna : (coluna - (atoi(strtok(NULL, ","))));

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
    if (filename != NULL)
    {
        FILE *fp = fopen(filename, "r");

        char line[40];
        fgets(line, 40, fp);
        gam->Comprimento = atoi(strtok(line, ","));
        gam->Altura = atoi(strtok(NULL, ","));

       

        gam->Tabuleiro = malloc(sizeof(int *) * gam->Comprimento);

        for (int i = 0; i < gam->Comprimento; i++)
            gam->Tabuleiro[i] = malloc(sizeof(int) * gam->Altura);

        int board_line_size = gam->Comprimento * 3 + 1;
        char *board_line = malloc(sizeof(char) * (board_line_size + 1));
        int lin = 0, col = 0;
        while (fgets(board_line, board_line_size, fp))
        {
            char *command = strtok(board_line, ",");
            lin = 0;
            gam->Tabuleiro[col][lin] = atoi(command);
            for (int lin = 1; lin < gam->Comprimento - 1; lin++)
                gam->Tabuleiro[col][lin] = atoi(strtok(NULL, ","));

            col++;
        }

        free(board_line);
    }
    else
    {

        gam->Tabuleiro = malloc(sizeof(int *) * gam->Comprimento);

        for (int i = 0; i < gam->Comprimento; i++)
            gam->Tabuleiro[i] = malloc(sizeof(int) * gam->Altura);

        int board_line_size = gam->Comprimento * 3 + 1;
        char *board_line = malloc(sizeof(char) * (board_line_size + 1));
        int lin = 0, col = 0;
        for (int col = 0; col < gam->Altura; col++)
            for (int lin = 0; lin < gam->Comprimento; lin++)
                gam->Tabuleiro[col][lin] = -1;

        free(board_line);
    }
}

void IJ(LstGame gam, char *Nome1, char *Nome2)
{
    if (gam->EstadoJogo == false)
    {

        gam->Jogador0 = Nome1;
        gam->Jogador1 = Nome2;

        char *lineIJ = NULL;
        size_t lenIJ = 0;
        getline(&lineIJ, &lenIJ, stdin);

        gam->Comprimento = strtok(lineIJ, " ");
        gam->Altura = strtok(NULL, " ");
        gam->Sequencia = strtok(NULL, " ");
        if (gam->Comprimento > 0 && gam->Altura <= gam->Comprimento && gam->Altura >= (gam->Comprimento / 2))
        {
            if (gam->Sequencia > 0 && gam->Sequencia < gam->Comprimento)
            {
                char *line = NULL;
                size_t len = 0;
                getline(&line, &len, stdin);

                char *token;

                token = strtok(line, " ");

                int *values = NULL;
                int value = 0;
                while (token != NULL)
                {
                    if (atoi(token) > 0 && gam->Sequencia > token)
                    {
                        if (values == NULL)
                            values = (int *)malloc(sizeof(int) * 1);
                        else
                            values = realloc(values, sizeof(values) * value);

                        values[value] = atoi(token);
                        value++;
                    }
                    else
                        printf("Dimensões de peças especiais inválidas.");
                            token = strtok(NULL, " ");
                }
                printf("Jogo iniciado entre %s e %s", gam->Jogador0, gam->Jogador1);
            }
            else
            {
                reset_game(gam);
                printf("Tamanho de sequência inválido.");
            }
        }
        else
        {
            reset_game(gam);
            printf(" Dimensões de grelha inválidas.");
        }
    }
    else
        printf("Existe um jogo em curso.");
    // comprimento >0
    // altura tem de ter no minimo metade de 2 no maximo valor de comprimento
    // numero de peças em linha tem de ser >0 e <=w
    // PeçasEspeciais tem de ser inferior a numero de peças em linha.
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
        char *Nome1 = strtok(NULL, " ");
        char *Nome2 = strtok(NULL, " ");
        if (FindIndex(Nome1, gam) != -1 && FindIndex(Nome2, gam) != -1)
            IJ(gam, Nome1, Nome2);
        else
            printf("Jogador não registado");
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

        CP(numb, coluna, sentido, tamanho, gam);
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
    LstJogador player = (LstJogador)malloc(sizeof(jogador));
    player->Nome = NULL;
    player->Vitoria = -1;
    player->Jogadas = -1;
    LstGame gam = (LstGame)malloc(sizeof(game));
    gam->Jogadores = NULL;
    gam->LenghPlayers = 0;

    reset_game(gam);
    while (true)
    {
        char *line = NULL;             // variavel string apontador
        size_t len = 0;                // É um "long", que conta bytes
        getline(&line, &len, stdin);   // geline() -> função para recolher texto stdin -> é um ponteiro do tipo FILE *
        line[strlen(line) - 1] = '\0'; // remover o \n
        switchcase(line, gam, player);
    }
    return 0;
}