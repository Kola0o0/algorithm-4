#include <stdio.h>
#include <stdlib.h>
#define print_array(A, L) for(_tmp=0; _tmp < L; _tmp++)printf("%d ", A[_tmp]); printf("\n");

int _tmp = 0;
//scanf("%d%*[\t\n ]%c", &j, &ch);


int partition(int arr[], int begin, int end){
    int i = begin;
    int pivot = arr[end];
    int highindex = begin;
    for(; i< end; i++){
        if(arr[i] < pivot ){
            int c = arr[i];
            arr[i] = arr[highindex];
            arr[highindex]= c;
            highindex++;
        }
    }
    int c = arr[end];
    arr[end] = arr[highindex];
    arr[highindex] = c;
    return highindex;
}


void quicksort(int arr[], int begin, int end){
    if(begin > end){
        return;
    }
    int pivot = partition(arr, begin, end);
    quicksort(arr, begin, pivot-1);
    quicksort(arr, pivot+1, end);
}


int main(){
    int arr[] = {6, 4, 3, 1, 2, 5};
    print_array(arr, 6);
    quicksort(arr, 0, 5);
    print_array(arr, 6);
    exit(0);
}

