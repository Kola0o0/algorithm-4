#include <stdio.h>
#include <stdlib.h>
//scanf("%d%*[\t\n ]%c", &j, &ch);
#define PRINT_ARRAY(ARR, LEN) for(_tmp=0; _tmp < LEN; _tmp++)printf("%d->", ARR[_tmp]); printf("\n");
int _tmp = 0;

void insertion_sort(int a[], int len){
    int i = 1, j = 0;
    for(; i < len; i++){
        int key = a[i];
        for(j=i-1; j>-1 && (a[j]>key); j--){
                a[j+1] = a[j];
        }
        a[j+1] = key;
    }
}

int main(){
    int arr[] = {5, 6, 1};
    PRINT_ARRAY(arr, 3);
    insertion_sort(arr, 3);
    PRINT_ARRAY(arr, 3);
    exit(0);
}



