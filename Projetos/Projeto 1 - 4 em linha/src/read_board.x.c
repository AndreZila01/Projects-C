#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **read_board(char *filename, int *w, int *h)
{
    FILE *fp = fopen(filename, "r");//abrir o ficheiro e "ler"

    char line[40];//array de char, com vetor de 39
    fgets(line, 40, fp); // lê o texto e envia os 40 caracteres do ficheiro da variavel fp para a line
    char *command = strtok(line, ","); //faz split(",") do texto da line
    *w = atoi(command);//convert para inteiro
    command = strtok(NULL, ",");//fazes split(",") again 
    *h = atoi(command);//e conveste o valor para inteiro

    int width = *w;//envias o valor de *w para width
    int height = *h;//envias o valor de *h para o height
    int **board = malloc(sizeof(int *) * width);//crias um array dinamico de apontadores 8 bytes * comprimento
    
    for (int i = 0; i < width; i++)//**não devia ser height**
    {
        board[i] = malloc(sizeof(int) * height);//multiplica o inteiro (4bytes) * tamanho, o que irá dar o espaço necessário para guardar todos os 0, 1, -1
        //**não devia ser int * **
    }
    
    int board_line_size = width * 3 + 1;//comprimento x 3 (porque o maximo de caracteres por linha da coluna são 3 (-1,)) + 1 (por causa do \n)
    char *board_line = malloc(sizeof(char) * ( board_line_size + 1));//?
    int row = 0, col = 0; // inteiro para ser a posição exato da linha e coluna
    while (fgets(board_line, board_line_size , fp))// vê o ficheiro na variavel fp, com o tamanho da boardline e lê contantemente o ficheiro linha por linha
    {
        command = strtok(board_line, ",");//split da coluna e pega primeiro valor antes de ,
        col = 0;
        board[row][col] = atoi(command);//conveste para inteiro e envia o valor para a board
        col++;
        for (int i = 0; i < width - 1; i++)//lê todos os outros 9 valores (neste caso)
        {
            command = strtok(NULL, ",");//faz split do resto da linha restante
            board[row][col] = atoi(command);//convert para inteiro e envia para a posição da matriz exata
            col++;//esta coluna poderá ser subsituida pela col?
        }
        row++;//muda de linha quando acabar com o ciclo coluna
    }

    free(board_line);//apaga os dados que estão na ram?

    fclose(fp);//fecha a ligação do ficheiro
    return board;
}

int main()
{
    int w;
    int h;
    int **board = read_board("board.txt", &w, &h);

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            printf("%3d", board[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < w; i++)
    {
        free(board[i]);
    }
    free(board);

    return 0;
}