#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
//scanf("%d%*[\t\n ]%c", &j, &ch);

struct queue{
    int arr[MAXSIZE];
    int front, rear;
};

int empty(struct queue *q){
    return (q->front == q->rear) ;
}

int qpop(struct queue *q){
    if(!empty(q)){
        int elem = q->arr[q->front++];
        if (q->front == MAXSIZE)
                q->front = 0;

        return elem;
    }
    return -1;
}

int qpush(struct queue *q, int elem){
    int front = q->front, rear = q->rear;
    if( !empty(q) && ((rear+1 == front) || (((rear + 1) % MAXSIZE) == front )))
        printf("Sorry, can't insert %d, queue full\n", elem);
    else{
        q->arr[q->rear] = elem;
        q->rear = (q->rear + 1) % MAXSIZE;
    }
}



int main(){
    struct queue q;
    q.front = 0;
    q.rear = 0;
    int i = 0;
    for(; i < 1000; i++){
        qpush(&q, i);
        int a = qpop(&q);
        printf("%d\n", a);
    }
    exit(0);
}

