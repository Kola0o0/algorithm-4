#include <stdio.h>
#include <stdlib.h>
//scanf("%d%*[\t\n ]%c", &j, &ch);


int binary_search(int *arr, int key, int low, int high){
    int mid = (low + high)/2;
    if (low >= mid)
        return -1;
    if(arr[mid] == key)
        return mid;
    if(arr[mid] > key)
        return binary_search(arr, key, low, mid-1);
    if(arr[mid] < key)
        return binary_search(arr, key, mid+1, high);
}

int main(){
    int arr[] = {1, 4, 5, 7, 9, 10};
    int key = 8;
    printf("Key search result: %d\n", binary_search(arr, key, 0, 5));
    exit(0);
}

