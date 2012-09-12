#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEM 100
#define print_array(a, l) for(_tmp=0; _tmp < l; _tmp++)printf("%d ", a[_tmp]);printf("\n");
//scanf("%d%*[\t\n ]%c", &j, &ch);
int _tmp = 0;

struct priority_queue {
    int queue[MAX_ELEM];
    int len;
    void (*insert)(struct priority_queue *, int);
};

int parent_node(int child){
    return child/2;
}

int left_child(int node){
    return 2*node +1;
}

int right_child(int node){
    return 2*node+2;
}


void bubble_down(struct priority_queue *pq, int node){
    if(node >= pq->len-1)
        return;
    int lc = left_child(node), rc = right_child(node);
    int greatest = node;
    if((lc < pq->len) && (pq->queue[node] < pq->queue[lc]))
        greatest = lc;
    if((rc < pq->len) && (pq->queue[greatest] < pq->queue[rc]))
        greatest = rc;

    if(greatest == node)
        return;

    int c = pq->queue[node];
    pq->queue[node] = pq->queue[greatest];
    pq->queue[greatest] = c;
    bubble_down(pq, greatest);
}

void bubble_up(struct priority_queue *pq, int node){
    if(node == 0)
        return;
    int parent = parent_node(node);
    if(pq->queue[parent] < pq->queue[node]){
        int c = pq->queue[parent];
        pq->queue[parent] = pq->queue[node];
        pq->queue[node] = c;
    }
    bubble_up(pq, parent);
}

void insert(struct priority_queue *pq, int key){
    if(pq->len == MAX_ELEM){
        printf("Priority queue is full\n");
        return;
    }
    pq->queue[pq->len++] = key;
    bubble_up(pq, pq->len-1);
}

int find_max(struct priority_queue *pq){
    return pq->queue[0];
}

int remove_max(struct priority_queue *pq){
    if (pq->len == 0){
        printf("Oops .. underflow\n");
        return;
    }
    int min = pq->queue[0];
    pq->queue[0] = pq->queue[pq->len-1];
    pq->len--;
    bubble_down(pq, 0);
    return min;

}

void heapsort(struct priority_queue *pq, int elem){
    int i = 0;
    for(; i < elem; i++){
        int c = pq->queue[0];
        pq->queue[0] = pq->queue[pq->len-1];
        pq->queue[pq->len-1] = c;
        pq->len--;
        bubble_down(pq, 0);
    }

}



int main(){
    struct priority_queue pq;
    pq.len = 0;
    pq.insert = insert;
    pq.insert(&pq, 4);
    pq.insert(&pq, 5);
    pq.insert(&pq, 3);
    pq.insert(&pq, 2);
    pq.insert(&pq, 1);
    print_array(pq.queue, pq.len);
    heapsort(&pq, 5);
    print_array(pq.queue, 5);
    exit(0);
}

