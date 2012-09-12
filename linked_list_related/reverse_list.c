#include <stdio.h>
#include <stdlib.h>
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


void reverse(struct node **list){
    if(!(*list))
        return;
    struct node *first = *list;
    struct node *rest = first->next;

    if(!rest)
        return;

    reverse(&rest);
    first->next->next = first;
    first->next = NULL;
    *list = rest;
}


void reverse_iter(struct node **list){
    struct node *tmp = *list;
    struct node *cur = tmp, *prev = NULL, *next = tmp->next;
    while(cur){
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    *list = prev;
}

void reverse_recur(struct node **list, struct node **end){
    struct node *new_list = NULL;
    struct node *l = *list;
    while(l){
        struct node *elem = l;
        l = l->next;
        elem->next = new_list;
        new_list = elem;
    }
    *list = new_list;
}


void reverse_k(struct node **list, int k){
    struct node* l = *list;
    struct node *prev = NULL, *next, *cur = l;
    while(cur){
        int i = 0;
        for(; i<k; i++){
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        l->next = cur;
        *list = prev;
        PRINT_LIST(*list);
        for(i=0; i < k; i++){
            if(cur){
                prev = cur;
                cur = cur->next;
            }
            else
                return;
        }

    }

}


int main(){
    struct node *list = (struct node*)malloc(sizeof(struct node));
    int arr[] = {1, 2, 3, 4, 5, 6};
    fill_list(list, arr, 6);
    PRINT_LIST(list);
    reverse_k(&list, 2);
    PRINT_LIST(list);
}

