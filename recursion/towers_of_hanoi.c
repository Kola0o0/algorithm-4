#include <stdio.h>
#include <stdlib.h>
//scanf("%d%*[\t\n ]%c", &j, &ch);


void traverse(char from, char to, char aux, int num){
    if (num == 1){
        printf("Move block 1 from %c to %c\n", from, to);
        return;
    } else{
        traverse(from, aux, to, num-1);
        printf("Move block %d from %c to %c\n", num, from, to);
        traverse(aux, to, from, num-1);
    }
}

int main(){
    int num = 5;
    char from = 'A', to = 'C', aux = 'B';
    traverse(from, to, aux, num);
    exit(0);
}

