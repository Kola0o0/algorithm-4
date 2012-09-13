#include <stdio.h>
#include <stdlib.h>
//scanf("%d%*[\t\n ]%c", &j, &ch);
#define PRINT_MATRIX(A, r,c) for(_tmp1=0;_tmp1 < r; _tmp1++){for(_tmp2=0;_tmp2<c;_tmp2++)printf("%d  ", A[_tmp1][_tmp2]);printf("\n");}
int _tmp1, _tmp2;


void spiral(int matrix[][3], int row, int col){
    int min_row = 0, max_row = row-1, min_col = 0, max_col = col-1;
    while((min_row < max_row)){
        int i = min_col;
        for(; i <= max_col; i++)
            printf("%d -> ", matrix[min_row][i]);
        min_row++;
        for(i=min_row;i <= max_row; i++)
            printf("%d -> ", matrix[i][max_col]);
        max_col--;
        for(i=max_col; i >= min_col; i--)
            printf("%d -> ", matrix[max_row][i]);
        max_row--;
        for(i=max_row; i >= min_row; i--)
            printf("%d -> ",matrix[i][min_col]);
        min_col++;

    }
    while(min_col <= max_col)
        printf("%d ->", matrix[min_row][min_col++]);
    printf("\n");

}


int main(){
    int matrix[4][3] = {{1, 2, 3},
                        {4, 5, 6},
                        {1, 1, 1},
                        {7, 8, 9}};
    printf("==================================\n");
    PRINT_MATRIX(matrix, 4, 3);
    spiral(matrix, 4, 3);
    exit(0);
}

