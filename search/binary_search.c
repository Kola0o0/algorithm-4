#include <stdio.h>
#include <stdlib.h>

//scanf("%d%*[\t\n ]%c", &j, &ch);

int binary_search(int arr[], int begin, int end, int elem){
    if(begin > end)
        return -1;
    int mid = (begin+end)/2;
    if(arr[mid] == elem)
        return mid;
    if(arr[mid] > elem)
        return binary_search(arr, begin, mid-1, elem);
    return binary_search(arr, mid+1, end, elem);
}


int main(int argc, char *argv[]){
    int arr[5] = {1, 2, 3, 4, 5};
    int elem = atoi(argv[1]);
    printf("%d\n", elem);
    int index = binary_search(arr, 0, 4, elem);
    printf("Element %s found : %d\n", (index == -1) ? "not" : "" , index);
    exit(0);
}

