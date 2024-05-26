#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SUDOKU_SIZE 9

struct allowed_struct{
    int size;
    int *array;
};

int **allocate_board(int rows, int cols)
{
    int **board = (int **) malloc(rows * sizeof(int *));
    int i = 0, j = 0;
    
    for(i=0;i<rows;i++){
        board[i] = (int *) malloc(rows * sizeof(int));
    }
    return board;
}

void free_board(int **board, int rows)
{
    for(int i=0;i<rows;i++)
    {
        free(board[i]);
    }
}

void print_array(int *arr, int size)
{
    int i;
    printf("[");
    for(i=0;i<size;i++)
    {
        printf("%d", arr[i]);
        if(i < size - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
}

int **zeroes_board(int **board, int rows, int cols) // Needed?
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

struct allowed_struct init_array(struct allowed_struct as)
{
    for(int i=0;i<as.size;i++)
    {
        as.array[i] = i + 1;
    }
    return as;
}

void draw_board(int **board, int rows, int cols){
    int i = 0, j = 0;
    for(i;i<rows;i++)
    {
        for(j=0;j<cols;j++)
        {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

struct allowed_struct init_struct(int s)
{
    struct allowed_struct as;
    as.size = s;
    as.array = (int *) malloc(s * sizeof(int));
    return as;
}

struct allowed_struct check_row(int **board, struct allowed_struct as, int row, int cols)
{
    // int *temp = (int *) malloc(cols * sizeof(int));
    // int *temp = as.array;
    int pos = 0;
    for(int i=0;i<=as.size;i++)
    {
        for(int col=0;col<cols;col++)
        {
            if(as.array[i] == board[row][col])
            {
                break;
            }
            if(col == cols - 1)
            {
                as.array[pos] = i;
                pos++;
            }
        }
    }
    as.size = pos;
    printf("pos: %d\n", pos);
    as.array = (int *) realloc(as.array, pos * sizeof(int));
    if(as.array == NULL)
    {
        printf("Memory reallocation failed!\n");
        free(as.array);
        // return 1;
    }
    // temp = as.array;
    return as;
}

struct allowed_struct check_col(int **board, struct allowed_struct allowed_rows, int rows, int col)
{
    // int *temp = (int *) malloc(allowed_rows.size * sizeof(int));
    int *temp = allowed_rows.array;
    int pos = 0, found = 0;
    for(int i=0;i<allowed_rows.size;i++)
    {
        for(int row=0;row<rows;row++)
        {
            if(allowed_rows.array[i] == board[row][col])
            {
                    break;
            }
            if(row == rows - 1)
            {
                temp[pos] = allowed_rows.array[i];
                pos++;
            }
        }
    }
    int *res = (int *) realloc(temp, pos * sizeof(int));
    struct allowed_struct as;
    as.size = pos;
    as.array = res;
    free(temp);
    return as;
}

struct allowed_struct check_segment(int **board, struct allowed_struct allowed_arr, int start_row, int start_col)
{
    // int *temp = (int *) malloc(allowed_arr.size * sizeof(int));
    int *temp = allowed_arr.array;
    int pos = 0, found, row, col;
    for(int i=0;i<allowed_arr.size;i++)
    {
        found = 0;
        for(row=start_row;row<start_row+3;row++)
        {
            for(col=start_col;col<start_col+3;col++)
            {
                if(allowed_arr.array[i] == board[row][col])
                {
                        found = 1;
                        break;
                }
            }
            if(found == 1)
            {
                break;
            }
        }
        if(found == 0)
        {
            temp[pos] = allowed_arr.array[i];
            pos++;
        }
    }
    int *res = (int *) realloc(temp, pos * sizeof(int));
    struct allowed_struct as;
    as.size = pos;
    as.array = res;
    free(temp);
    return as;
}

int **get_values(int **board, int rows, int cols)
{
    srand(time(NULL));
    struct allowed_struct as;
    int col, row, num, h, v, i, j, seg, pos, found = 0, hseg = 0, vseg = 0;
    as = init_struct(rows);
    // as = init_array(as);
    for(row=0;row<rows;row++)
    {
        if(row%3 == 0 && row != 0)
        {
            hseg++;
        }
        vseg = 0;
        for(col=0;col<cols;col++)
        {
           if(col%3 == 0 && col != 0)
           {
               vseg++;
           }
           if(row > 0)
           {
               pos = 0;
               for(h=hseg+1;h<rows/3;h++)
               {
                   in_other_seg = check_segment(board, as, h*3, vseg*3);
                   printf("prueba1 %d\n");
                   print_array(in_other_seg.array, in_other_seg.size);
                   printf("prueba2 %d\n");
               }
               for(v=vseg+1;v<cols/3;v++)
               {
                   in_other_seg  = check_segment(board, as, hseg*3, v*3);
               }

               for(i=1;j<=rows;j++)
               {
                   for(j=0;j<in_other_seg.size;j++)
                   {
                       if(i == in_other_seg.array[j])
                       {
                           found = 1;
                           break;
                       }
                   }
                   if(found == 1)
                   {
                       found = 0;
                   }
                   else
                   {
                       as.array[pos] = in_other_seg.array[j];
                   }
               }
           }
           as = check_row(board, as, row, cols);
           printf("check_row\n");
           print_array(as.array, as.size);
           printf("array size1; %d\n", as.size);
           as = check_col(board, as, rows, col);
           printf("check_col\n");
           print_array(as.array, as.size);
           printf("array size2; %d\n", as.size);
           as = check_segment(board, as, hseg*3, vseg*3);
           printf("check_seg\n");
           print_array(as.array, as.size);
           
           printf("check_seg\n");
           print_array(as.array, as.size);
           printf("array size3; %d\n", as.size);
           num = rand() % as.size;
           printf("random: %d\n", num);
           printf("hseg: %d\nvseg: %d\n",hseg,vseg);
           board[row][col] = as.array[num];
           draw_board(board, rows, cols);
        }
    }
    printf("fin\n");
    free(as.array);
    free(in_other_seg.array);
    return board;
}

int main()
{
    int rows = SUDOKU_SIZE, cols = rows;
    int **board = allocate_board(rows, cols);
    board = zeroes_board(board, rows, cols);
    // ########## debug ################
    /*
    for(int j=0;j<cols;j++)
    {
        if(j == 0)
        {
            board[0][j] = 6;
        }
        else
        {
            board[0][j] = 0;
        }
    }
    
    board[0][0] = 3;
    board[0][1] = 7;
    board[0][2] = 1;
    // ##########################
    as = check_row(board, 1, cols);
    as = check_col(board, as, rows, 0);
    as = check_segment(board, as, 0, 0);
    for(int i=0;i<as.size;i++)
    {
        printf("%d ", as.array[i]);
    }
    printf("\n");
    board = get_values(board, rows, cols);
    */
    // free(allowed_values);
    // draw_board(board, rows, cols);
    board = get_values(board, rows, cols);
    draw_board(board, rows, cols);
    free_board(board, rows);
    return 0;
}
