#include <stdio.h>
#include <stdlib.h>
//scanf("%d%*[\t\n ]%c", &j, &ch);

int main(){
    int arr[6] = {5, 10, 11, 1000, 1000, 1000};
    int arr2[3] = {6, 7, 9};
    int p1 = 2, p2 = 2, max = 6;

    while((p1 >= 0) && (p2 >= 0)){
        arr[max-1] = (arr[p1] >= arr2[p2]) ? arr[p1--] :arr2[p2--];
        max--;
    }
    while(p2 > 0){
        arr[max-1] = arr[p2--];
    }
    int i = 0;
    for(; i < 6; i++)
        printf("%d -> ", arr[i]);
    printf("\n");
}

