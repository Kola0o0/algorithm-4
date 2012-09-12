#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100
//scanf("%d%*[\t\n ]%c", &j, &ch);
struct edge {
    int y;
    int weight;
    struct edge *next;
};

struct graph{
    int num_edges;
    int num_vertices;
    struct edge *edges[MAX_VERTICES+1];
    int degree[MAX_VERTICES+1];
    int directed;
};

struct queue {
    int arr[MAX_VERTICES+1];
    int front;
    int rear;
};

void init_queue(struct queue *q){
    q->front = 0;
    q->rear = -1;
}


int empty(struct queue *q){
    return (q->rear < q->front);
}

void enqueue(struct queue *q, int node){
    q->arr[++(q->rear)] = node;
}

int dequeue(struct queue *q){
    return q->arr[q->front++];
}


void init_graph(struct graph *g, int directed){
    g->num_edges = 0;
    g->num_vertices = 0;
    g->directed = directed;
    int i = 1;
    for(; i<= MAX_VERTICES; i++){
        g->degree[i] = 0;
        g->edges[i] = NULL;
    }
}

void insert_edge(struct graph *g, int x, int y, int directed){
    struct edge *e = (struct edge*)malloc(sizeof(struct edge));
    e->weight = 1;
    e->y = y;
    e->next = g->edges[x];
    g->edges[x] = e;
    g->degree[x]++;
    if(!directed)
        insert_edge(g, y, x, 1);
}

void print_graph(struct graph *g){
    int i = 1, j = 1;
    for(; i <= g->num_vertices; i++){
        printf("%d ->", i);
        struct edge *tmp = g->edges[i];
        while(tmp){
            printf("%d ", tmp->y);
            tmp = tmp->next;
        }
        printf("\n");
    }
}

int parent[MAX_VERTICES+1];
void bfs(struct graph *g, int start){
    int processed[MAX_VERTICES+1], discovered[MAX_VERTICES+1];
    struct queue q;
    init_queue(&q);
    int i = 1;
    for(; i <= g->num_vertices; i++){
        parent[i] = -1;
        processed[i] = discovered[i] = 0;
    }
    discovered[start] = 1;
    enqueue(&q, start);
    while(!empty(&q)){
        int vertex = dequeue(&q);
        //printf("Processing vertex %d ->", vertex);
        struct edge *tmp = g->edges[vertex];
        while(tmp){
            if(!discovered[tmp->y]){
                parent[tmp->y] = vertex;
                discovered[tmp->y] = 1;
                enqueue(&q, tmp->y);
            }
            tmp= tmp->next;
        }
        processed[vertex] = 1;
        //printf("\n");
    }
}

void shortest_path_print(struct graph *g, int node, int node2){
    if(parent[node2] != -1)
        shortest_path_print(g, node, parent[node2]);
    printf("%d ->", node2);
}

void shortest_path(struct graph *g, int node, int node2){
    bfs(g, node);
    shortest_path_print(g, node, node2);
    printf("\n");
    /*printf("%d -> ", node2);
    int cur = node2;
    while((parent[cur] != -1) && parent[cur] != node){
        cur = parent[cur];
        printf("%d ->", cur);
    }
    printf(" %d", node);*/
}

int main(){
    struct graph g;
    int directed = 0;
    init_graph(&g, directed);
    scanf("%d %d", &(g.num_vertices), &(g.num_edges));
    int i = 0;
    for(; i < g.num_edges; i++){
        int x = 0, y =0;
        scanf("%d %d", &x, &y);
        insert_edge(&g, x, y, directed);
    }
    bfs(&g, 1);
    shortest_path(&g, 1, 6);
    exit(0);
}

