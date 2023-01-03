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
    int DimensoesTabuleiro[2]; // linhas x colunas
    char *PecEspecial[2];
    int Sequencia; // Tamanho de sequencia
    char *Nome[2];
    int LenghPlayers;
    bool EstadoJogo; // false - Por Inciar || true - A decorrer
} game, *LstGame;

// FALTA TURNO NO JOGO

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

    Sort(gam);
    return true;
}

int FindIndex(char *Nome, LstGame gam)
{
    for (int count = 0; count < gam->LenghPlayers; count++)
        if (strcmp(gam->Jogadores[count]->Nome, Nome) == 0)
            return count;

    return -1;
}

void Sort(LstGame gam)
{
    char *temp[101];
    for (int i = 0; i < gam->LenghPlayers; i++)
    {
        for (int j = i + 1; j < gam->LenghPlayers; j++)
        {
            if (strcmp(gam->Jogadores[i]->Nome, gam->Jogadores[j]->Nome) > 0)
            {
                strcpy(temp, gam->Jogadores[i]->Nome);
                strcpy(gam->Jogadores[i]->Nome, gam->Jogadores[j]->Nome);
                strcpy(gam->Jogadores[j]->Nome, temp);
            }
        }
    }
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
}

void D(char *Utilizador, LstGame gam)
{
    int idUtilizador = (FindIndex(Utilizador, gam));
    if (gam->EstadoJogo == false)
        printf("Não existe jogo em curso.");
    else if ((gam->Nome[1] == Utilizador) || (gam->Nome[0] == Utilizador) && idUtilizador != -1)
    {
        if (strcmp(Utilizador, gam->Nome[0]) == 0 && strcmp(Utilizador, gam->Nome[1]) == 0)
        {
            // O outro jogador regista uma vitória e ambos registam mais um jogo jogado
            if (strcmp(Utilizador, gam->Nome[0]) == 0)
                gam->Jogadores[FindIndex(gam->Nome[0], gam)]->Vitoria++;
            else
                gam->Jogadores[FindIndex(gam->Nome[1], gam)]->Vitoria++;

            gam->Jogadores[FindIndex(gam->Nome[1], gam)]->Jogadas++;
            gam->Jogadores[FindIndex(gam->Nome[0], gam)]->Jogadas++;
            printf("Desistência com sucesso. Jogo terminado.\n");
            reset_game(gam);
        }
    }
}

void reset_game(LstGame game)
{
    game->Tabuleiro = NULL;
    game->Nome[0] = NULL;
    game->Nome[1] = NULL;
    game->EstadoJogo = false;
    game->DimensoesTabuleiro[0] = -1;
    game->DimensoesTabuleiro[1] = -1;
    game->Sequencia = 0;
    game->PecEspecial[0] = "0";
    game->PecEspecial[1] = "0";
    game->TamanhoPeca = NULL;
}

bool CheckWin(int numjogador, int coluna, int linha, char *sentido, LstGame gam)
{

    int linhaigual = 0;
    for (int value = linha - gam->Sequencia; value <= linha + gam->Sequencia; value++)
    {
        if (value < 0)
            value = 0;
        if (value > gam->Sequencia)
            break;
        if (value >= 0)
        {
            if (gam->Tabuleiro[coluna][value] == numjogador)
                linhaigual++;
            else
                linhaigual = 0;

            if (linhaigual == gam->Sequencia)
            {
                printf("Acabou o jogo\n");
                break;
            }
        }
    }

    for (int value = coluna - gam->Sequencia; value <= coluna + gam->Sequencia; value++)
    {
        if (coluna > gam->DimensoesTabuleiro[1])
            break;
        if (value < 0)
            value = 0;
        if (coluna > -1)
        {
            if (gam->Tabuleiro[value][linha] == numjogador)
                linhaigual++;
            else
                linhaigual = 0;

            if (linhaigual == gam->Sequencia)
            {
                printf("Acabou o jogo\n");
                break;
            }
        }
    }

    for (int value = -gam->Sequencia; value <= gam->Sequencia; value++)
    {
        if (coluna + value > gam->DimensoesTabuleiro[1] & linha + value > gam->DimensoesTabuleiro[0])
            break;
        if (value < 0)
            value = 0;
        if (coluna + value > -1 && linha + value > -1)
        {
            if (gam->Tabuleiro[coluna + value][linha + value] == numjogador)
                linhaigual++;
            else
                linhaigual = 0;

            if (linhaigual == gam->Sequencia)
            {
                printf("Acabou o jogo\n");
                break;
            }
        }
    }
    for (int value = 0; value <= gam->Sequencia; value++)
    {
        if (value < 0)
            value = 0;
        if (gam->Tabuleiro[coluna - value][linha - value] == numjogador)
            linhaigual++;
        else
            linhaigual = 0;

        if (linhaigual == gam->Sequencia)
        {
            printf("Acabou o jogo\n");
            break;
        }
    }
}

char *CP(int numbjogador, int coluna, char *sentido, int tamanhopeca, LstGame gam)
{
    // char *v = strtok(("%s", gam->dimensao), ",");
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
        gam->DimensoesTabuleiro[0] = atoi(strtok(line, ","));
        gam->DimensoesTabuleiro[1] = atoi(strtok(NULL, ","));

        gam->Tabuleiro = malloc(sizeof(int *) * gam->DimensoesTabuleiro[0]);

        for (int i = 0; i < gam->DimensoesTabuleiro[0]; i++)
            gam->Tabuleiro[i] = malloc(sizeof(int) * gam->DimensoesTabuleiro[1]);

        int board_line_size = gam->DimensoesTabuleiro[0] * 3 + 1;
        char *board_line = malloc(sizeof(char) * (board_line_size + 1));
        int lin = 0, col = 0;
        while (fgets(board_line, board_line_size, fp))
        {
            char *command = strtok(board_line, ",");
            lin = 0;
            gam->Tabuleiro[col][lin] = atoi(command);
            for (int lin = 1; lin < gam->DimensoesTabuleiro[0] - 1; lin++)
                gam->Tabuleiro[col][lin] = atoi(strtok(NULL, ","));

            col++;
        }

        free(board_line);
    }
    else
    {

        gam->Tabuleiro = malloc(sizeof(int *) * gam->DimensoesTabuleiro[0]);

        for (int i = 0; i < gam->DimensoesTabuleiro[0]; i++)
            gam->Tabuleiro[i] = malloc(sizeof(int) * gam->DimensoesTabuleiro[1]);

        int board_line_size = gam->DimensoesTabuleiro[0] * 3 + 1;
        char *board_line = malloc(sizeof(char) * (board_line_size + 1));
        int lin = 0, col = 0;
        for (int col = 0; col < gam->DimensoesTabuleiro[1]; col++)
            for (int lin = 0; lin < gam->DimensoesTabuleiro[0]; lin++)
                gam->Tabuleiro[col][lin] = -1;

        free(board_line);
    }
}

void IJ(LstGame gam, char *Nome1, char *Nome2)
{
    if (gam->EstadoJogo == false)
    {

        gam->Nome[0] = Nome1;
        gam->Nome[1] = Nome2;

        char *lineIJ = NULL;
        size_t lenIJ = 0;
        getline(&lineIJ, &lenIJ, stdin);

        gam->DimensoesTabuleiro[0] = atoi(strtok(lineIJ, " "));
        gam->DimensoesTabuleiro[1] = atoi(strtok(NULL, " "));
        if (gam->DimensoesTabuleiro[0] > 0 && gam->DimensoesTabuleiro[1] <= gam->DimensoesTabuleiro[0] && gam->DimensoesTabuleiro[1] >= (gam->DimensoesTabuleiro[0] / 2))
        {
            if (gam->Sequencia > 0 && gam->Sequencia < gam->DimensoesTabuleiro[0])
            {
                char *line = NULL;
                size_t len = 0;
                getline(&line, &len, stdin);

                char *token;

                token = strtok(line, " ");

                int values = NULL;
                int value = 0;
                while (token != NULL)
                {
                    if (atoi(token) > 0 && gam->Sequencia > atoi(token))
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
                if (value != 0)
                {
                    gam->Sequencia[1] = values;
                    gam->Sequencia[0] = values;
                }
                printf("Jogo iniciado entre %s e %s", gam->Nome[0], gam->Nome[1]);
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

void VR(LstGame gam)
{
    if (!gam->EstadoJogo)
        printf("Não existe jogo em curso.\n");

    // Mostrar estado atual da grelha
    for (int i = 0; i < gam->DimensoesTabuleiro[1]; i++)
    {
        for (int j = 0; j < gam->DimensoesTabuleiro[0]; j++)
        {
            printf("%d %d ", i + 1, j + 1);
            if (gam->Tabuleiro[i][j] == -1)
                printf("Vazio\n");
            else
                printf("%s\n", gam->Jogadores[gam->Tabuleiro[i][j]]->Nome);
        }
    }
}

void Gravar(LstGame gam)
{
    FILE *fp = fopen("", "w");
    fprintf(fp, "%d\n", gam->LenghPlayers);
    for (int i = 0; i < gam->LenghPlayers; i++)
    {
        fprintf(fp, "%s,", gam->Jogadores[i]->Nome);
        fprintf(fp, "%d,", gam->Jogadores[i]->Jogadas);
        fprintf(fp, "%d\n", gam->Jogadores[i]->Vitoria);
    }
    if (gam->EstadoJogo)
    {
        fprintf(fp, "%d,%d\n", gam->DimensoesTabuleiro[0], gam->DimensoesTabuleiro[1]);
        for (int c = 0; c < gam->DimensoesTabuleiro[1]; c++)
        {
            for (int l = 0; l < gam->DimensoesTabuleiro[0]; l++)
            {
                if (c - 1 < gam->DimensoesTabuleiro[0])
                    fprintf(fp, "%d,", gam->Tabuleiro[c][l]);
                else
                    fprintf(fp, "%d\n", gam->Tabuleiro[c][l]);
            }
        }
        fprintf(fp, "%d,%d\n", FindIndex(gam->Nome[0], gam), FindIndex(gam->Nome[1], gam));
        //PEÇAS ESPECIAIS FALTA
    }
    fclose(fp);
}

void Ler(LstGame game, LstJogador pla){

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
        D(utilizadorD, gam);
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

        if (strcmp(jogador, gam->Nome[0]) == 0)
            numb = 0;
        else
            numb = 1;

        CP(numb, coluna, sentido, tamanho, gam);
    }
    else if (strcmp(comando, "VR") == 0)
    {
        VR(gam);
    }
    else if (strcmp(comando, "G") == 0)
    {
        Gravar(gam, jog);
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