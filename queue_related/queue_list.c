#include <stdio.h>
#include <stdlib.h>
//scanf("%d%*[\t\n ]%c", &j, &ch);

struct node{
    struct node *next;
    int value;
};

struct queue{
    struct node *front;
    struct node *rear;
};

int empty(struct queue *q){
    return q->front == NULL;
}

int pop(struct queue *q){
    if(empty(q)){
        return -1;
    }
    else{
        struct node *temp = q->front;
        q->front = q->front->next;
        int value = temp->value;
        if(temp == q->rear)
            q->rear = q->front;
        free(temp);
        return value;
    }
}


void push(struct queue *q, int elem){
    if(q->rear){
        q->rear->next = (struct node*)malloc(sizeof(struct node));
        q->rear->next->value = elem;
        q->rear->next->next = NULL;
        q->rear = q->rear->next;
    } else {
        q->rear = (struct node*)malloc(sizeof(struct node));
        q->rear->next = NULL;
        q->rear->value = elem;
        q->front = q->rear;
    }
}

int main(){
    struct queue q;
    q.front = NULL;
    q.rear = NULL;
    int i = 0;
    for(; i < 100; i++){
        push(&q, i);
        printf("%d\n", pop(&q));
    }

    exit(0);
}

