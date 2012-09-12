#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MATCH 0
#define INSERT 1
#define DELETE 2
//scanf("%d%*[\t\n ]%c", &j, &ch);



int distance(char *s1, char *s2, int l1, int l2){
    int cost[3];

    if(!l1)
        return l2;
    if(!l2)
        return l1;

    cost[0] = distance(s1, s2, l1-1, l2-1) + ((s1[l1-1] == s2[l2-1]) ? 0 : 1);
    cost[1] = distance(s1, s2, l1, l2-1) + 1;
    cost[2] = distance(s1, s2, l2, l1-1) + 1;

    int min = cost[0], op = 0, i = 0;
    for(i=0; i < 3; i++){
        op = (min > cost[i]) ? i: op;
        min = (min > cost[i]) ? cost[i]: min;
    }
    return min;
}



int main(){
    char *str = "bhinac";
    char *str2 = "abhinav";
    int d = distance(str, str2, strlen(str), strlen(str2));
    printf("%d\n", d);
    exit(0);
}

