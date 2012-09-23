#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MATCH 0
#define INSERT 1
#define DELETE 1
#define MAXLEN 100
//scanf("%d%*[\t\n ]%c", &j, &ch);

struct cell {
    int operation;
    int value;
};

struct cell table[MAXLEN+1][MAXLEN+1];

void row_init(int i){
    table[0][i].value = i;
    if(i == 0){
        table[0][i].operation = -1;
    } else {
        table[0][i].operation = INSERT;
    }
}

void column_init(int i){
    table[i][0].value = i;
    if(i == 0){
        table[i][0].operation = -1;
    } else {
        table[i][0].operation = DELETE;
    }
}


int distance(char *s1, char *s2){
    // distance between s1[0..i], 0 is i+1
    int i = 0, j = 0;
    for(; i < MAXLEN; i++){
        row_init(i);
        column_init(i);
    }

    int cost[3];
    for(i = 1; i < strlen(s1); i++){
        for(j = 1; j < strlen(s2); j++){
            cost[0] = ((s1[i] == s2[j]) ? table[i-1][j-1].value : (table[i-1][j-1].value + 100));
            cost[1] = table[i-1][j].value + 1;
            cost[2] = table[i][j-1].value + 1;

            int k = 0, min = cost[0], operation = 0;
            for(; k < 3; k++){
                if(cost[k] < min){
                    min = cost[k];
                    operation = k;
                }
            }
            table[i][j].value = min;
            table[i][j].operation = operation;
        }
    }
    return table[strlen(s1)-1][strlen(s2)-1].value;
}

char lcs[MAXLEN];
int cur_pos = 0;
void reconstruct_path(char *s, int i, int j){
    if(!(i||j))
        return;
    if(table[i][j].operation == 0){
        reconstruct_path(s, i-1, j-1);
        lcs[cur_pos++] = s[i];
    }
    else if(table[i][j].operation == 1){
        reconstruct_path(s, i-1, j);
    }
    else if(table[i][j].operation == 2){
        reconstruct_path(s, i, j-1);
    }
}

void print_table(int l1, int l2){
    int i =0, j = 0;
    char *operations[] = {"substitute", "insert", "delete"};
    for(; i < l1; i++){
        for(j = 0; j < l2; j++){
            printf("Table[%d][%d] = %s\n", i, j, operations[table[i][j].value]);
            }

        }
    }


int main(){
    char *str1 = "republican", *str2 = "democrat";
    int d = distance(str1, str2);
    //print_table(strlen(str1), strlen(str2));
    reconstruct_path(str1, strlen(str1)-1, strlen(str2)-1);
    lcs[cur_pos] = '\0';
    printf("%s", lcs);
    exit(0);
}

