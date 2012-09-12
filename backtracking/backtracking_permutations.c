/*
 *Program to generate all permutations of a given set.
 *
 */
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
            printf("%d ", a[i]);
    }
    printf("}\n");

}


void construct_candidates(int a[], int k, int input, int c[], int *num_candidates){
    int i = 1, j = 0;
    int in_perm[MAX];
    for(; j < MAX; j++){
        in_perm[j] = 0;
    }
    for(j = 0; j < k-1; j++){
        in_perm[a[j]] = 1;
    }

    for(j = 1; j <= input; j++){
        if(!in_perm[j]){
            c[*num_candidates] = j;
           *num_candidates = *num_candidates +1;
        }
    }
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

