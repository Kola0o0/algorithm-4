#include <stdio.h>
#include <stdlib.h>
//scanf("%d%*[\t\n ]%c", &j, &ch);
#define PRINT_LIST(X) temp = X; for(temp=X; temp != NULL; temp = temp->next)printf("%d ->", temp->elem); printf("\n");

struct node {
    int elem;
    struct node *next;
};

int K;
struct node* temp;
void fill_list(struct node* list, int arr[], int len){
    int i = 0;
    struct node *temp = list;
    for(; i < len; i++){
        temp->elem = arr[i];
        temp->next = (i < len-1)?(struct node*)malloc(sizeof(struct node)):NULL;
        temp = temp->next;
    }
}

void rotate_list(struct node** l){
    struct node *list = *l;
    struct node* tmp = list, *prev, *end = list;
    int i = 0;
    for(; i < K; i++){
        prev = tmp;
        tmp = tmp->next;
    }
    while(end->next)
        end = end->next;

    end->next = list;
    list = tmp;
    prev->next = NULL;
    *l = list;
}


int main(int argc, char* argv[]){
    if (argc < 2)
        K = 2;
    else
        K = atoi(argv[1]);

    struct node *list = (struct node*)malloc(sizeof(struct node));
    int arr[] = {1, 2, 3, 4, 5, 6};
    fill_list(list, arr, 6);
    PRINT_LIST(list);
    rotate_list(&list);
    PRINT_LIST(list);
    exit(0);
}

