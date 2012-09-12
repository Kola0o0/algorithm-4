#include <stdio.h>
#include <stdlib.h>
#define print_matrix(M, R, C) for(_tmp=0; _tmp < R; _tmp++){for(_tmp1 = 0; _tmp1 < C; _tmp1++)printf("%d ", M[_tmp][_tmp1]); printf("\n"); }
//scanf("%d%*[\t\n ]%c", &j, &ch);

int _tmp = 0, _tmp1 = 0;


void multiply(int matrix1[][3], int matrix2[][4], int matrix3[2][4], int row1, int col1, int row2, int col2){
    int i = 0, j = 0, k = 0;
    for(i=0; i < row1; i++){
        for(j=0; j<col2; j++){
            int sum = 0;
            for(k=0; k< row2; k++){
                sum += matrix2[k][j] * matrix1[i][k];
            }
            printf("\n");
            matrix3[i][j] = sum;
        }
    }
}


int main(){
    int matrix1[2][3] = {{1, 2, 3},
                         {4, 5, 6}};

    int matrix2[3][4] = {{1,2,3,4},
                         {0,0,0,0},
                         {1,1,1,1}};

    int matrix3[2][4];

    print_matrix(matrix1, 2, 3);
    print_matrix(matrix2, 3, 4);
    multiply(matrix1, matrix2, matrix3, 2, 3, 3, 4);
    print_matrix(matrix3, 2, 4);
    exit(0);
}

