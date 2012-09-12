#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 10
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
    print_graph(&g);
    exit(0);
}

