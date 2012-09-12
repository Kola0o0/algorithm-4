#include <stdio.h>
#include <stdlib.h>
#define MAX 100
//scanf("%d%*[\t\n ]%c", &j, &ch);

int finished = 0;


int correct_solution(int a[], int k, int input){
    return (k==input);
}

void process_solution(int a[], int input){
    int i = 0;
    printf("{");
    for(; i < input; i++){
            if(a[i])
                printf("%d ", i+1);
    }
    printf("}\n");

}


void construct_candidates(int a[], int k, int input, int c[], int *num_candidates){
    c[0] = 1;
    c[1] = 0;
    *num_candidates = 2;
}

void backtrack(int a[], int k, int input){
    int candidates[MAX+1];
    int num_candidates = 0;
    if(correct_solution(a, k, input))
        process_solution(a, input);
    else {
        k++;
        construct_candidates(a, k, input, candidates, &num_candidates);
        int i = 0;
        for(; i < num_candidates; i++){
            a[k-1] = candidates[i];
            backtrack(a, k, input);
        }
    }

}




int main(){
    int a[] = {1,2,3};
    backtrack(a, 0, 3);
    exit(0);
}

