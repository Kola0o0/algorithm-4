#include <stdio.h>
#include <stdlib.h>
#define print_array(a, l) for(_tmp=0; _tmp < l; _tmp++)printf("%d ", a[_tmp]);printf("\n");
//scanf("%d%*[\t\n ]%c", &j, &ch);

int _tmp = 0;

void merge(int arr[], int begin, int mid, int end){
    int i = begin, j = mid+1;
    int arr1[mid-begin+1], arr2[end-mid];
    for(; i<= mid; i++){
        arr1[i-begin] = arr[i];
    }
    for(; j<=end; j++){
        arr2[j-mid-1] = arr[j];
    }
    int k = begin;
    for(i = 0, j = 0; (i < mid-begin+1) && (j < end-mid ); k++){
        if(arr1[i] < arr2[j])
            arr[k] = arr1[i++];
        else
            arr[k] = arr2[j++];
    }
    for(; j< end-mid ; j++)
        arr[k++] = arr2[j];
    for(; i< mid-begin+1; i++)
        arr[k++] = arr1[i];
}


void merge_sort(int arr[], int begin, int end){
    if(begin >= end)
        return;
    int mid = (begin+end)/2;
    merge_sort(arr, begin, mid);
    merge_sort(arr, mid+1, end);
    merge(arr, begin, mid, end);
}


int main(){
    int arr[] = {4, 3, 2, 1, 5, 6, 7};
    print_array(arr, 7);
    merge_sort(arr, 0, 6);
    print_array(arr, 7);
    exit(0);
}

