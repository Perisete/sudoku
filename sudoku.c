#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int **allocate_board(int rows, int cols)
{   
    int **board = malloc(rows * sizeof(int *));
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            board[i] = malloc(cols * sizeof(int *));
        }
    }
    return board;
}

void free_board(int **board, int rows)
{   
    for(int i=0;i<rows;i++)
    {
        free(board[i]);
    }
    free(board);

}

int **fill_board(int **board, int rows, int cols)
{
    srand(time(NULL));
    int av[rows][cols], rn = 0, i = 0, j = 0, k = 0;
    bool allowed = true;
    for(i=0;i<rows;i++)
    {
        for(j=0;j<cols;j++)
        {
            board[i][j] = 0;
        }
    }
    for(i=0;i<rows;i++)
    {
        for(j=0;j<cols;j++)
        {
            rn = (rand() % 9) + 1;
            for(k=0;k<cols;k++)
            {
                if(rn == board[i][k]){
                    allowed = false;
                    break;
                }
            }
            if(allowed == true){
                board[i][j] = rn;
            }
            else
            {
                allowed = true;
            }
        }
    }

    return board;
}

void draw_board(int **board, int rows, int cols)
{
    char *indexc[27] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"}; //"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int x = 0, y = 0, i = 0, j = 0, k, b = 0, line = 1, voffset = cols/3, hoffset = rows/3;
    for(y=0;y<rows+hoffset;y++){
        k = -1;
        for(x=0;x<cols+voffset;x++){
            if(x == 0 && y == 0){
                printf("  ");
            }
            if(y%4 == 0 && y > 0 && x > 0)
            {
                printf("  ");
                while(x < cols+voffset){
                    printf("- ");
                    x++;
                }
                x = 0;
                y++;
                k--;
                printf("\n");
            }
            if(x == 0 && y > 0 && y%4 > 0){
                printf("\033[0;31m%d\033[0m ", line);
                line++;
            }
            else{
                if(y == 0){
                    if(b%3 > 0 || b == 0){
                        b++;
                        printf("\033[0;31m%s\033[0m ", indexc[j]);
                        j++;
                    }
                    else{
                        printf("  ");
                        b = 0;
                    }
                }
                else{
                    k++;
                    if(k%3 == 0 && k > 0)
                    {
                        printf("| ");
                        x++;
                    }
                    if(y > 0 && x > 0)
                    {
                        printf("%d ", board[i-1][j-1]);
                        j++;
                    }
                }
            }
        }
        printf("\n");
        i++;
        j = 0;
    }
}

int main(){
    int rows = 9, cols = 9;
    int **board = allocate_board(rows, cols);
    board = fill_board(board, rows, cols);
    draw_board(board, rows, cols);
    free_board(board, rows);
    return 0;
}
