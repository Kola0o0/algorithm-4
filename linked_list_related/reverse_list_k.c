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

struct node * reverse_k(struct node **head, int k){
    if(!(*head))
        return NULL;
    struct node *tmp = *head, *prev = NULL, *next = tmp->next;
    int i = 0;
    for(; i < k ; i++){
        next = tmp->next;
        tmp->next = prev;
        prev = tmp;
        tmp = next;
    }
    if(next)
       (*head)->next = reverse_k(&(next), k);
    return prev;
}


int main(){
    struct node *list = (struct node*)malloc(sizeof(struct node));
    int arr[] = {1, 2, 3, 4, 5, 6};
    fill_list(list, arr, 6);
    PRINT_LIST(list);
    reverse_k(&list, 2);
    PRINT_LIST(list);
    exit(0);
}

