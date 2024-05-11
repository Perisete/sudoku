#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int **allocate_board(int rows, int cols)
{
    int **board = (int **) malloc(rows * sizeof(int *));
    int i = 0, j = 0;
    
    for(i=0;i<rows;i++){
        board[i] = (int *) malloc(rows * sizeof(int));
    }
    return board;
}

int **zeroes_board(int **board, int rows, int cols)
{
    int i = 0, j = 0;
    for(i=0;i<rows;i++)
    {
        for(j=0;j<cols;j++)
        {
            board[i][j] = 0;
        }
    }
    return board;
}

int check_if_allowed_square(int **board, int rows, int cols, int row_start, int row_end, int col_start, int col_end, int num)
{
    int row, col;
    printf("row start: %d\n", row_start);
    printf("row end: %d\n", row_end);
    printf("col start: %d\n", col_start);
    printf("col end: %d\n", col_end);
    for(row=row_start;row<row_end;row++)
    {
        for(col=col_start;col<col_end;col++)
        {
            if(board[row][col] == num)
            {
                return 0;
            }
        }
    }
    return 1;
}

int **get_values(int **board, int rows, int cols)
{
    int row = 0, col = 0, num = 0, allowed = 1, col_mult = 0, row_mult = 0;
    srand(time(NULL));
    for(row=0;row<rows;row++)
    {
        col_mult = 0;
        for(col=0;col<cols;col++)
        {
            if(col % 3 == 0 && col > 0)
            { 
                col_mult++;
            }
            do{
                num = (rand() % 9) + 1;
                allowed = check_if_allowed_square(board, rows/3, cols/3, row - row_mult, row - (row_mult*3), col - (col_mult*3), row - (col_mult*3), num);
            }while(allowed != 1);
            board[row][col] = num;
        }
        if(row % 3 == 0 && row > 0)
        {
            row_mult++;
        }
    }
    return board;
}

void draw_board(int **board, int rows, int cols){
    int i = 0, j = 0;
    for(i;i<rows;i++)
    {
        for(j=0;j<cols;j++){
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int rows = 9,cols = 9;
    int **board = allocate_board(rows, cols);
    board = zeroes_board(board, rows, cols);
    board = get_values(board, rows, cols);
    draw_board(board, rows, cols);
    free(board); // TODO do it for matrix
    return 0;
}
