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

struct node* sum_of_list(struct node* list1, struct node* list2){
    struct node *sum_list = (struct node*)malloc(sizeof(struct node));
    struct node *tmp = list1, *tmp2 = list2, *tmp3 = sum_list, *prev = NULL;
    int carry = 0;
    while(tmp || tmp2){
        int sum = (tmp ? tmp->elem : 0) + (tmp2? tmp2->elem: 0) + carry;
        if(sum >= 10){
            sum -= 10;
            carry = 1;
        } else
            carry = 0;

        prev = tmp3;
        tmp3->elem = sum;
        tmp3->next = (struct node*)malloc(sizeof(struct node));
        tmp3 = tmp3->next;
        tmp2 = tmp2 ? tmp2->next : NULL;
        tmp = tmp ? tmp->next : NULL;
    }
    if(carry){
        tmp3->elem = carry;
        tmp3->next = NULL;
    } else {
        prev->next = NULL;
        free(tmp3);
    }
    return sum_list;
}

int main(){
    struct node *list = (struct node*)malloc(sizeof(struct node));
    struct node *list2 = (struct node*)malloc(sizeof(struct node));
    int arr[] = {1, 2, 5};
    int arr2[] = {3, 4, 5};
    fill_list(list, arr, 3);
    fill_list(list2, arr2, 3);
    struct node* sum_list = sum_of_list(list, list2);
    PRINT_LIST(list);
    PRINT_LIST(list2);
    PRINT_LIST(sum_list);
    exit(0);
}

