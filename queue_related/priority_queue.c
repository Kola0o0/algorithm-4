#include <stdio.h>
#include <stdlib.h>
//scanf("%d%*[\t\n ]%c", &j, &ch);

struct node {
    struct node * next;
    int value;
};

struct queue {
    struct node *front, *rear;
};

int empty(struct queue *q){
    return q->front == NULL;
}

int pop(struct queue *q){
    if(!empty(q)){
        struct node *tmp = q->front;
        q->front = q->front->next;
        if(tmp == q->rear)
            q->rear = q->front;
        int result = tmp->value;
        free(tmp);
        return result;
    }

}

void push(struct queue *q, int elem){
    if(q->rear){
        struct node *tmp = q->front, *prev = q->front;
        while(tmp && tmp->value < elem ){
            prev = tmp;
            tmp = tmp->next;
        }
        if(prev == tmp){
            struct node *new = (struct node*)malloc(sizeof(struct node));
            new->value = elem;
            new->next = prev;
            q->front = new;
        } else{
            struct node *new = (struct node*)malloc(sizeof(struct node));
            new->value = elem;
            new->next = tmp;
            prev->next = new;
            if(!tmp)
                q->rear = new;
        }
    } else {
        q->rear = (struct node*)malloc(sizeof(struct node));
        q->front = q->rear;
        q->rear->value = elem;
        q->rear->next = NULL;
    }
}

void printq(struct queue *q){
    struct node *tmp = q->front;
    while(tmp){
        printf("%d ->", tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
}

int main(){
    struct queue priority_queue;
    priority_queue.front = NULL;
    priority_queue.rear = NULL;
    push(&priority_queue, 11);
    push(&priority_queue, 9);
    push(&priority_queue, 8);
    push(&priority_queue, 7);
    push(&priority_queue, 6);
    push(&priority_queue, 1);
    push(&priority_queue, 0);

    printf("\n%d\n", pop(&priority_queue));

    exit(0);
}

