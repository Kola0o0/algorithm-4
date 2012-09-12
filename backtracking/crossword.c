/*
 *Program to check whether a given string
 *occurs in a crossword.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
//scanf("%d%*[\t\n ]%c", &j, &ch);

char crossword[5][6] = {"abhin", "abcde", "qwerty", "asdfg", "zxcvb"};
int finished = 0;
struct point{
    int x;
    int y;
};

struct elem{
    char ch;
    struct point pos;
};

int correct_solution(struct elem a[], int k, char* input){
    char tmp[k];
    int i = 1;
    for(; i <= k; i++)
        tmp[i-1] = a[i].ch;
    tmp[i-1] = '\0';
    if(k == strlen(input)){
        return (!strcmp(tmp, input));
    }
    return 0;
}

int process_solution(struct elem a[], int k, char* input){
    char tmp[k];
    int i = 1;
    for(; i <=k; i++)
        tmp[i-1] = a[i].ch;
    tmp[i-1] = '\0';
    printf("*************************PASSSSSSS %s\n", tmp);
}

void construct_candidates(struct elem a[], int k, char *input, struct elem c[], int * num){
    if( k == 1) {
        *num = 1;
        c[0].ch = crossword[0][0];
        c[0].pos.x = 0;
        c[0].pos.y = 0;
    } else {
        struct point p = a[k-1].pos;
        int x = p.x, y = p.y;
        if(x+1 < 5){
            c[*num].ch = crossword[x+1][y];
            c[*num].pos.x = x+1;
            c[*num].pos.y = y;
            *num = *num+1;
        }
        if(y+1 < 5){
            c[*num].ch = crossword[x][y+1];
            c[*num].pos.x = x;
            c[*num].pos.y = y+1;
            *num = *num+1;
        }
        if(x+1 < 5 && y+1 < 5){
            c[*num].ch = crossword[x+1][y+1];
            c[*num].pos.x = x+1;
            c[*num].pos.y = y+1;
            *num = *num+1;
        }
    }
}

void backtrack(struct elem a[6], int k, char *input){
    struct elem candidates[MAX];
    int num_candidates = 0;
    if(correct_solution(a, k, input))
        process_solution(a, k, input);
    else {
        k++;
        construct_candidates(a, k, input, candidates, &num_candidates);
        int i = 0;
        for(; i < num_candidates; i++){
            a[k].ch = candidates[i].ch;
            a[k].pos = candidates[i].pos;
            backtrack(a, k, input);
        }
        if(finished)
            return;
    }

}



int main(){
    // replace with a dictionary of valid words.
    char *valid_word = "abefb";
    struct elem a[6];
    backtrack(a, 0, valid_word);
    exit(0);
}

