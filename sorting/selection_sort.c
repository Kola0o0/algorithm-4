#include <stdio.h>
#include <stdlib.h>
#define PRINT_ARRAY(ARR, LEN) for(_tmp=0; _tmp < LEN; _tmp++)printf("%d->", ARR[_tmp]); printf("\n");
//scanf("%d%*[\t\n ]%c", &j, &ch);
int _tmp = 0;

void selection_sort_dumb(int arr[], int len){
    int i =  0, j = 0, min = i;
    for(; i < len; i++){
        min = i;
        for(j=i; j< len; j++){
            min = (arr[j] < arr[min]) ? j : min;
        }
        int c = arr[i];
        arr[i] = arr[min];
        arr[min] = c;
    }
}

int main(){
    int arr[] = {5, 4, 3, 2, 7, 8};
    PRINT_ARRAY(arr, 6);
    selection_sort_dumb(arr, 6);
    PRINT_ARRAY(arr, 6);
    exit(0);
}

