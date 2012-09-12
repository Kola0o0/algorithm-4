#include <stdio.h>
#include <stdlib.h>
//scanf("%d%*[\t\n ]%c", &j, &ch);

#define PRINT_LIST(X) temp = X; for(temp=X; temp != NULL; temp = temp->next)printf("%d ->", temp->elem); printf("\n");
#define PRINT_ARRAY(X, L) _tmp = 0; for(; _tmp < L; _tmp++)printf("%d->", X[_tmp]);printf("\n");

//scanf("%d%*[\t\n ]%c", &j, &ch);
struct node {
    int elem;
    struct node *next;
};

struct tree_node {
    int elem;
    struct tree_node *left;
    struct tree_node *right;
};

struct node* temp;
int _tmp;
void fill_list(struct node* list, int arr[], int len){
    int i = 0;
    struct node *temp = list;
    for(; i < len; i++){
        temp->elem = arr[i];
        temp->next = (i < len-1)?(struct node*)malloc(sizeof(struct node)):NULL;
        temp = temp->next;
    }
}

int list_length(struct node *list){
    int cnt = 0;
    while(list){
        cnt++;
        list = list->next;
    }
    return cnt;
}


struct tree_node* convert_recurse(struct node **list, int length){
    if(length <= 0)
        return NULL;

    struct tree_node* left = convert_recurse(list, length/2);
    struct tree_node* root = (struct tree_node*)malloc(sizeof(struct tree_node));
    root->left = left;
    root->elem = (*list)->elem;
    *list = (*list)->next;
    root->right = convert_recurse(list, length-length/2-1);
    return root;
}

struct tree_node *convert(struct node **list){
    int length = list_length(*list);
    return convert_recurse(list, length);
}

void inorder(struct tree_node * tree){
    if(!tree)
        return;

    inorder(tree->left);
    printf("%d -> ", tree->elem);
    inorder(tree->right);
}


int main(){
    struct node *list1 = (struct node*)malloc(sizeof(struct node));
    int arr1[] = {12, 6, 29};
    fill_list(list1, arr1, 3);
    PRINT_LIST(list1);
    struct tree_node *tree = convert(&list1);
    inorder(tree);
    exit(0);
}

