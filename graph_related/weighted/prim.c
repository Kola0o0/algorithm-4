#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_VERTICES 100
#define MAX_INT INT_MAX
struct edge {
    int y;
    int weight;
    struct edge *next;
};

struct stack {
    int arr[MAX_VERTICES+2];
    int top;
};

int empty(struct stack *s){
    return (s->top == -1);
}

void push(struct stack *s, int elem){
    s->arr[++(s->top)] = elem;
}

int pop(struct stack *s){
    return s->arr[(s->top)--];
}



struct graph{
    int num_edges;
    int num_vertices;
    struct edge *edges[MAX_VERTICES+1];
    int degree[MAX_VERTICES+1];
    int directed;
};

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

void insert_edge(struct graph *g, int x, int y, int w, int directed){
    struct edge *e = (struct edge*)malloc(sizeof(struct edge));
    e->weight = w;
    e->y = y;
    e->next = g->edges[x];
    g->edges[x] = e;
    g->degree[x]++;
    if(!directed)
        insert_edge(g, y, x, w,  1);
}

void print_graph(struct graph *g){
    int i = 1, j = 1;
    for(; i <= g->num_vertices; i++){
        struct edge *tmp = g->edges[i];
        while(tmp){
            tmp = tmp->next;
        }
        printf("\n");
    }
}


int intree[MAX_VERTICES+1], parent[MAX_VERTICES+1], distance[MAX_VERTICES+1];

void prim(struct graph *g, int start){
    int i = 1;
    for(; i < MAX_VERTICES+1; i++){
        intree[i] = 0;
        parent[i] = -1;
        distance[i] = MAX_INT;
    }

    distance[start] = 0;
    struct edge * tmp;
    int v = start, last_v = start;
    printf("%d", v);
    while(!intree[v]){
        intree[v] = 1;
        tmp = g->edges[v];
        int flag = 0;
        while(tmp){
            int y = tmp->y;
            if(!intree[y]){
                flag = 1;
                distance[y] = (distance[y] < tmp->weight) ? distance[y] : tmp->weight;
                parent[y] = (distance[y] < tmp->weight) ? parent[y] : v;
            }
            tmp = tmp->next;
        }
        int dist = MAX_INT;
        last_v = v;
        v = 1;
        for(i = 1; i < MAX_VERTICES+1; i++){
            if(!intree[i] && (distance[i] < dist)){
                dist = distance[i];
                v = i;
            }
        }
        printf("%d -> %d\n", last_v, parent[last_v]);
    }
    printf("\n");
}

int main(){
    struct graph g;
    int directed = 0;
    init_graph(&g, directed);
    scanf("%d %d", &(g.num_vertices), &(g.num_edges));
    int i = 0;
    for(; i < g.num_edges; i++){
        int x = 0, y =0, w = 0;
        scanf("%d %d %d", &x, &y, &w);
        insert_edge(&g, x, y, w, directed);
    }
    prim(&g, 1);

    printf("\n");
    exit(0);
}

