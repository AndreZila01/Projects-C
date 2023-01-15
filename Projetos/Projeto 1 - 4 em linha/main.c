#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char *Nome;  // Nome de Jogadores
    int Vitoria; // Vitorias do Jogador
    int Jogadas; // Numero de Jogadas do Jogador
} jogador, *LstJogador;

typedef struct
{
    LstJogador *Jogadores;     // Struct ligado ao LstJogador
    int **Tabuleiro;           // Matriz do tabuleiro de inteiros
    int DimensoesTabuleiro[2]; // linhas x colunas
    int *PecEspecial[2];       // As peças especiais de cada jogador
    int NumPecEspecial[2];     // Número de peças especiais para cada jogador (igual inicialmente)
    int Sequencia;             // Tamanho de sequencia
    char *Nome[2];             // Nome dos dois jogadores
    int LenghPlayers;          // Quantos Jogadores estão no *Jogadores
    bool EstadoJogo;           // false - Por Inciar || true - A decorrer
} game, *LstGame;

void reset_game(LstGame game)
{
    game->Tabuleiro = NULL;
    game->Nome[0] = NULL;
    game->Nome[1] = NULL;
    game->EstadoJogo = false;
    game->DimensoesTabuleiro[0] = -1;
    game->DimensoesTabuleiro[1] = -1;
    game->Sequencia = 0;
    game->PecEspecial[0] = NULL;
    game->PecEspecial[1] = NULL;
    game->NumPecEspecial[0] = -1;
    game->NumPecEspecial[1] = -1;
    free(game->PecEspecial[1]);
    free(game->PecEspecial[0]);
}

void Sort(LstGame gam)
{
    LstJogador temp;
    for (int i = 0; i < gam->LenghPlayers; i++)
    {
        for (int j = 0; j < gam->LenghPlayers - 1; j++)
        {
            if (strcmp(gam->Jogadores[j]->Nome, gam->Jogadores[j + 1]->Nome) > 0)
            {
                temp = gam->Jogadores[j];
                gam->Jogadores[j] = gam->Jogadores[j + 1];
                gam->Jogadores[j + 1] = temp;
            }
        }
    }
}
bool RJ(char *Name, LstGame gam)
{
    for (int count = 0; count < gam->LenghPlayers; count++)
    {
        if (strcmp(gam->Jogadores[count]->Nome, Name) == 0)
            return false;
    }

    LstJogador player = (LstJogador)malloc(sizeof(jogador));
    player->Nome = malloc(sizeof(char) * (strlen(Name) + 1));
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

char *EJ(char *Nome, LstGame gam)
{
    int index = FindIndex(Nome, gam);
    if (index != -1)
    {
        if (gam->EstadoJogo)
            if (strcmp(gam->Nome[0], Nome) == 0 || strcmp(gam->Nome[1], Nome) == 0)
                return "Jogador participa no jogo em curso.";

        LstJogador jog = gam->Jogadores[index];
        for (int count = index; count < gam->LenghPlayers; count++)
            gam->Jogadores[count] = gam->Jogadores[count + 1];
        // gam->Jogadores = realloc(gam->Jogadores, sizeof(LstJogador) * gam->LenghPlayers - 1);
        gam->Jogadores[gam->LenghPlayers - 1] = NULL;
        gam->LenghPlayers--;
        free(jog);
        return "Jogador removido com sucesso.\n";
    }
    else
        return "Jogador não existente.\n";
}

bool LJ(LstGame gam)
{
    if (gam->LenghPlayers == 0)
        return false;
    for (int count = 0; count < gam->LenghPlayers; count++)
        if (gam->Jogadores[count]->Nome != 0x0)
            printf("%s %d %d\n", gam->Jogadores[count]->Nome, gam->Jogadores[count]->Jogadas, gam->Jogadores[count]->Vitoria);
    return true;
}

void GiveWin(int numjogador, LstGame gam)
{
    if (numjogador != -1)
        gam->Jogadores[(FindIndex(gam->Nome[numjogador], gam))]->Vitoria++;
    gam->Jogadores[(FindIndex(gam->Nome[0], gam))]->Jogadas++;
    gam->Jogadores[(FindIndex(gam->Nome[1], gam))]->Jogadas++;
    reset_game(gam);
}

void D(char *Utilizador1, char *Utilizador2, LstGame gam)
{
    if (!gam->EstadoJogo == false)
    {
        int idUtilizador = (FindIndex(Utilizador1, gam));

        if ((strcmp(Utilizador1, gam->Nome[0]) == 0 || strcmp(Utilizador1, gam->Nome[1]) == 0) && idUtilizador != -1)
        {
            // O outro jogador regista uma vitória e ambos registam mais um jogo jogado
            // Os dois utilizadores podem perder
            int numjogador = strcmp(gam->Nome[0], Utilizador1) == 0 ? 0 : 1;
            if (Utilizador2 != NULL)
                numjogador = -1;
                GiveWin(numjogador, gam);

            printf("Desistência com sucesso. Jogo terminado.\n");
            reset_game(gam);
        }
        else
            printf("Jogador não participa no jogo em curso.\n");
    }
    else
        printf("Não existe jogo em curso.\n");
}

bool CheckWin(int numjogador, int coluna, int linha, LstGame gam)
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
            if (linha + value >= gam->DimensoesTabuleiro[0] || coluna + value >= gam->DimensoesTabuleiro[1])
            {
                linhaigual = 0;
                break;
            }
            else if (gam->Tabuleiro[value][coluna] == numjogador)
                linhaigual++;
            else
                linhaigual = 0;

            if (linhaigual == gam->Sequencia)
                return true;
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
            if (linha + value >= gam->DimensoesTabuleiro[0] || coluna + value >= gam->DimensoesTabuleiro[1])
            {
                linhaigual = 0;
                break;
            }
            else if (gam->Tabuleiro[linha][value] == numjogador)
                linhaigual++;
            else
                linhaigual = 0;

            if (linhaigual == gam->Sequencia)
                return true;
        }
    }

    for (int value = -gam->Sequencia; value <= gam->Sequencia; value++)
    {
        if (coluna + value > gam->DimensoesTabuleiro[1] & linha + value > gam->DimensoesTabuleiro[0])
            break;
        if (value < 0)
            value = 0;
        if (linha + value >= gam->DimensoesTabuleiro[0] || coluna + value >= gam->DimensoesTabuleiro[1])
        {
            linhaigual = 0;
            break;
        }
        else if (coluna + value > -1 && linha + value > -1)
        {
            if (gam->Tabuleiro[linha + value][coluna + value] == numjogador)
                linhaigual++;
            else
                linhaigual = 0;

            if (linhaigual == gam->Sequencia)
                return true;
        }
    }
    for (int value = 0; value <= gam->Sequencia; value++)
    {
        if (value < 0)
            value = 0;
        if (linha + value >= gam->DimensoesTabuleiro[0] || coluna + value >= gam->DimensoesTabuleiro[1])
        {
            linhaigual = 0;
            break;
        }
        else if (gam->Tabuleiro[linha - value][coluna - value] == numjogador)
            linhaigual++;
        else
            linhaigual = 0;

        if (linhaigual == gam->Sequencia)
            return true;
    }
    return false;
}

bool CheckPecaEspecial(LstGame gam, int tamanho, int numb)
{
    for (int i = 0; i < gam->NumPecEspecial[numb]; i++)
    {
        if (gam->PecEspecial[numb][i] == tamanho)
        {
            memmove(&(gam->PecEspecial[numb][i]), &(gam->PecEspecial[numb][i + 1]), (gam->NumPecEspecial[numb] - i - 1) * sizeof(int));
            gam->NumPecEspecial[numb]--;

            return true;
        }
    }
    return false;
}

void CP(int numbjogador, int coluna, char *sentido, int tamanhopeca, LstGame gam)
{
    if (gam->EstadoJogo == false)
        printf("Não existe jogo em curso.\n");

    int poscol = (sentido != NULL && strcmp(sentido[0], "E") == 0) ? coluna - tamanhopeca : coluna;
    poscol--;

    if (poscol < 0 && poscol > gam->DimensoesTabuleiro[0])
        printf("Posição irregular.");
    else if (CheckPecaEspecial(gam, tamanhopeca, numbjogador) || tamanhopeca == 1)
    {
        int col = 0, linha = 0;
        for (linha = 0; linha < tamanhopeca; linha++)
            for (col = gam->DimensoesTabuleiro[1] - 1; col >= 0; col--) // Alterar estes valores
                if (gam->Tabuleiro[linha][col + poscol] == -1)
                {
                    gam->Tabuleiro[linha][col + poscol] = numbjogador;
                    // linha = linha;
                    break;
                }

        bool s = CheckWin(numbjogador, col, linha, gam);
        if (s)
        {
            printf("Sequência conseguida. Jogo terminado.\n");
            GiveWin(numbjogador, gam);
        }
        else
            printf("Peça colocada.\n");
    }
    else
        printf("Tamanho de peça não disponível.\n");
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
        gam->Nome[0] = malloc(sizeof(char) * (strlen(Nome1) + 1));
        strcpy(gam->Nome[0], Nome1);
        gam->Nome[1] = malloc(sizeof(char) * (strlen(Nome2) + 1));
        strcpy(gam->Nome[1], Nome2);

        char *lineIJ = NULL;
        size_t lenIJ = 0;
        getline(&lineIJ, &lenIJ, stdin);
        lineIJ[strlen(lineIJ) - 1] = '\0';

        gam->DimensoesTabuleiro[0] = atoi(strtok(lineIJ, " "));
        gam->DimensoesTabuleiro[1] = atoi(strtok(NULL, " "));
        gam->Sequencia = atoi(strtok(NULL, " "));

        char *line = NULL;
        size_t len = 0;
        getline(&line, &len, stdin);
        line[strlen(line) - 1] = '\0';

        char *token;
        token = strtok(line, " ");

        int *values = NULL;
        int num_values = 0;
        while (token != NULL)
        {
            if (atoi(token) > 1 && gam->Sequencia > atoi(token))
            {
                num_values++;
                values = realloc(values, sizeof(int) * num_values);

                values[num_values - 1] = atoi(token);
            }
            else
            {
                num_values = -10000;
                printf("Dimensões de peças especiais inválidas.\n");
            }
            token = strtok(NULL, " ");
        }
        if (num_values > 0)
        {
            gam->PecEspecial[1] = malloc(sizeof(int) * num_values);
            memcpy(gam->PecEspecial[1], values, sizeof(int) * num_values);
            gam->NumPecEspecial[1] = num_values;
            gam->PecEspecial[0] = malloc(sizeof(int) * num_values);
            memcpy(gam->PecEspecial[0], values, sizeof(int) * num_values);
            gam->NumPecEspecial[0] = num_values;

            printf("Jogo iniciado entre %s e %s\n", gam->Nome[0], gam->Nome[1]);
            gam->EstadoJogo = true;

            gam->Tabuleiro = malloc(sizeof(int *) * gam->DimensoesTabuleiro[0]);

            for (int i = 0; i < gam->DimensoesTabuleiro[0]; i++)
                gam->Tabuleiro[i] = malloc(sizeof(int) * gam->DimensoesTabuleiro[1]);

            int board_line_size = gam->DimensoesTabuleiro[0] * 3 + 1;
            char *board_line = malloc(sizeof(char) * (board_line_size + 1));

            for (int col = 0; col < gam->DimensoesTabuleiro[1]; col++)
                for (int lin = 0; lin < gam->DimensoesTabuleiro[0]; lin++)
                    gam->Tabuleiro[lin][col] = -1;
        }

        if (!(gam->Sequencia > 0 && gam->Sequencia < gam->DimensoesTabuleiro[0]))
        {
            reset_game(gam);
            printf("Tamanho de sequência inválido.\n");
        }
        else if (!(gam->DimensoesTabuleiro[0] > 0 && gam->DimensoesTabuleiro[1] <= gam->DimensoesTabuleiro[0] && gam->DimensoesTabuleiro[1] >= (gam->DimensoesTabuleiro[0] / 2)))
        {
            reset_game(gam);
            printf("Dimensões de grelha inválidas.\n");
        }
        free(line);
        free(lineIJ);
    }
    else
        printf("Existe um jogo em curso.\n");
}

void VR(LstGame gam)
{
    if (!gam->EstadoJogo)
        printf("Não existe jogo em curso.\n");

    for (int i = 0; i < gam->DimensoesTabuleiro[1]; i++)
    {
        for (int j = 0; j < gam->DimensoesTabuleiro[0]; j++)
        {
            printf("%d %d ", i + 1, j + 1);
            if (gam->Tabuleiro[i][j] == -1)
                printf("Vazio\n");
            else
                printf("%s", gam->Jogadores[gam->Tabuleiro[i][j]]->Nome);
        }
    }
}

void Gravar(LstGame gam)
{
    FILE *fp = fopen("Backup.txt", "w");
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

        fprintf(fp, "%d,%d\n", gam->NumPecEspecial[0], gam->NumPecEspecial[1]);

        for (int count = 0; count < gam->NumPecEspecial[0]; count++)
            fprintf(fp, "%d", gam->PecEspecial[0][count]);

        fprintf(fp, "\n");

        for (int count = 0; count < gam->NumPecEspecial[1]; count++)
            fprintf(fp, "%d", gam->PecEspecial[1][count]);

        fprintf(fp, "\n");

        printf("Jogo Gravado.\n");
    }
    else
        printf("Ocorreu um erro na gravação.\n");
    fclose(fp);
}

void LerPecEsp(LstGame gam, char *tamanho, int jogador)
{

    char *token;
    token = strtok(tamanho, ",");

    int *values = NULL;
    int num_values = 0;
    while (token != NULL)
    {
        if (atoi(token) > 0 && gam->Sequencia > atoi(token))
        {
            num_values++;
            values = realloc(values, sizeof(int) * num_values);

            values[num_values - 1] = atoi(token);
        }
        else
            printf("Dimensões de peças especiais inválidas.\n");
        token = strtok(NULL, " ");
    }
    if (num_values != 0)
    {
        gam->PecEspecial[jogador] = malloc(sizeof(int) * num_values);
        memcpy(gam->PecEspecial[jogador], values, sizeof(int) * num_values);
        gam->NumPecEspecial[jogador] = num_values;
    }
}

void Ler(LstGame game)
{
    FILE *fp = fopen("Backup.txt", "r"); // abrir o ficheiro e "ler"

    if (fp != NULL)
    {
        char line[40];
        fgets(line, 40, fp);
        char *command = strtok(line, ",");
        game->DimensoesTabuleiro[0] = atoi(command);
        command = strtok(NULL, ",");
        game->DimensoesTabuleiro[1] = atoi(command);
        game->Tabuleiro = malloc(sizeof(int *) * game->DimensoesTabuleiro[0]); // crias um array dinamico de apontadores 8 bytes * comprimento

        for (int i = 0; i < game->DimensoesTabuleiro[0]; i++) //**não devia ser height**
        {
            game->Tabuleiro[i] = malloc(sizeof(int) * game->DimensoesTabuleiro[1]); // multiplica o inteiro (4bytes) * tamanho, o que irá dar o espaço necessário para guardar todos os 0, 1, -1
            //**não devia ser int * **
        }

        int board_line_size = game->DimensoesTabuleiro[0] * 3 + 1;       // comprimento x 3 (porque o maximo de caracteres por linha da coluna são 3 (-1,)) + 1 (por causa do \n)
        char *board_line = malloc(sizeof(char) * (board_line_size + 1)); //\0
        int row = 0, col = 0;                                            // inteiro para ser a posição exato da linha e coluna
        while (fgets(board_line, board_line_size, fp))                   // vê o ficheiro na variavel fp, com o tamanho da boardline e lê contantemente o ficheiro linha por linha
        {
            command = strtok(board_line, ",");
            game->Tabuleiro[row][col] = atoi(command);
            col++;
            for (col = 1; col < game->DimensoesTabuleiro[0] - 1; col++)
            {
                command = strtok(NULL, ",");
                game->Tabuleiro[row][col] = atoi(command);
            }
            row++;
        }

        char linesS[40]; // Numero dos Jogadores
        fgets(linesS, 40, fp);
        char *commandsV = strtok(linesS, ",");
        game->Nome[0] = commandsV;
        commandsV = strtok(NULL, ",");
        game->Nome[1] = commandsV;

        char tamanho[50]; // TamanhoDasPeçasEspeciais
        fgets(tamanho, 50, fp);
        char *commandsTam = strtok(linesS, ",");
        game->NumPecEspecial[0] = atoi(commandsTam);
        commandsTam = strtok(NULL, ",");
        game->NumPecEspecial[1] = atoi(commandsTam);

        char PecEsp0[3 * game->NumPecEspecial[0]]; // PeçasEspeciais
        fgets(PecEsp0, 3 * game->NumPecEspecial[0], fp);
        LerPecEsp(game, PecEsp0, 0);

        char PecEsp1[3 * game->NumPecEspecial[1]]; // PeçasEspeciais
        fgets(PecEsp1, 3 * game->NumPecEspecial[1], fp);
        LerPecEsp(game, PecEsp1, 1);

        free(board_line); // apaga os dados que estão na ram?

        fclose(fp); // fecha a ligação do ficheiro
        printf("Jogo Carregado.\n");
    }
    else
        printf("Ocorreu um erro no carregamento.\n");
}

int compara_PecEspecial(int *a, int *b)
{
    return *a - *b;
}

void printDJ(LstGame gam, int jogador)
{
    printf("%s\n", gam->Nome[jogador]);
    int pecaatual = 0, quantidade = 0; // pecamenor é anterior, pecaatual é a peca mais pequena da lista toda no momento e superiro ao pecamenor.
    qsort(gam->PecEspecial[jogador], gam->NumPecEspecial[jogador], sizeof(int), (int (*)(const void *, const void *))compara_PecEspecial);

    pecaatual = gam->PecEspecial[jogador][0];
    for (int val = 0; val <= gam->NumPecEspecial[jogador]; val++)
    {
        if (pecaatual == gam->PecEspecial[jogador][val])
            quantidade++;
        else
        {
            printf("%d %d\n", pecaatual, quantidade);
            quantidade = 1;
            pecaatual = gam->PecEspecial[jogador][val];
        }
    }
    printf("\n");
}

int DJ(LstGame gam)
{
    if (gam->EstadoJogo == false)
        return 0;
    printf("%d %d\n", gam->DimensoesTabuleiro[0], gam->DimensoesTabuleiro[1]);
    int jogador = 0;

    if (strcmp(gam->Nome[0], gam->Nome[1]) > 0)
        jogador = 0;
    else
        jogador = 1;
    printf("\n");
    printDJ(gam, jogador);

    if (strcmp(gam->Nome[0], gam->Nome[1]) < 0)
        jogador = 0;
    else
        jogador = 1;

    printDJ(gam, jogador);
}

void switchcase(char *linha, LstGame gam)
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
    {
        bool value = LJ(gam);
        if (value == false)
            printf("Não existem jogadores registados.\n");
    }
    else if (strcmp(comando, "D") == 0)
    {
        char *utilizadorD = strtok(NULL, " ");
        char *utilizadorT = strtok(NULL, " ");
        D(utilizadorD, utilizadorT, gam);
    }
    else if (strcmp(comando, "IJ") == 0)
    {
        char *Nome1 = strtok(NULL, " ");
        char *Nome2 = strtok(NULL, " ");
        if (FindIndex(Nome1, gam) != -1 && FindIndex(Nome2, gam) != -1)
            IJ(gam, Nome1, Nome2);
        else
            printf("Jogador não registado.\n");
    }
    else if (strcmp(comando, "CP") == 0)
    {
        char *jogador = strtok(NULL, " ");
        int tamanho = atoi(strtok(NULL, " "));
        int coluna = atoi(strtok(NULL, " "));
        char *sentido = strtok(NULL, " ");

        int numb = -1;
        if (strcmp(jogador, gam->Nome[0]) == 0)
            numb = 0;
        if (strcmp(jogador, gam->Nome[1]) == 0)
            numb = 1;

        if (numb != -1)
            CP(numb, coluna, sentido, tamanho, gam);
        else
            printf("Jogador não participa no jogo em curso.\n");
    }
    else if (strcmp(comando, "VR") == 0)
    {
        VR(gam);
    }
    else if (strcmp(comando, "G") == 0)
    {
        Gravar(gam);
    }
    else if (strcmp(comando, "L") == 0)
    {
        Ler(gam);
    }
    else if (strcmp(comando, "DJ") == 0)
    {
        int value = DJ(gam);
        if (value == 0)
            printf("Não existe jogo em curso.\n");
    }
    else
        printf("O valor inserido nao tem correspondencia.\n");
}

int main()
{
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
        if (strlen(line) == 0)
            break;
        switchcase(line, gam);
        free(line);
    }
    return 0;
    //./main < iotests/DJ.in
}