#include <stdio.h>
#include <stdlib.h>
//scanf("%d%*[\t\n ]%c", &j, &ch);

struct node{
    int elem;
    struct node *left;
    struct node *right;
    void (*insert)(struct node **, int);
    void (*inorder)(struct node *);
};

void insert(struct node** tree, int value){
    struct node *t = *tree;
    if(!t){
        t = (struct node*)malloc(sizeof(struct node));
        t->left = NULL;
        t->right = NULL;
        t->elem = value;
        *tree = t;
        return;
    }
    if(t->elem < value)
        insert(&(t->right), value);
    else
        insert(&(t->left), value);
}

void inorder(struct node *tree){
    if(!tree)
        return;
    inorder(tree->left);
    printf("%d ->", tree->elem);
    inorder(tree->right);
}


int main(){
    struct node* tree = (struct node*)malloc(sizeof(struct node));
    tree->elem = 5;
    tree->left = NULL;
    tree->right = NULL;

    insert(&tree, 4);
    insert(&tree, 1);
    insert(&tree, 2);
    insert(&tree, 3);
    inorder(tree);
    exit(0);
}

