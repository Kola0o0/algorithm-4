#include <stdio.h>
#include <stdlib.h>
//scanf("%d%*[\t\n ]%c", &j, &ch);
#define MAX_VERTICES 100
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
        struct edge *tmp = g->edges[i];
        while(tmp){
            tmp = tmp->next;
        }
        printf("\n");
    }
}

int time = 0, entry_time[MAX_VERTICES+1], exit_time[MAX_VERTICES+1];
int discovered[MAX_VERTICES+1], processed[MAX_VERTICES+1], parent[MAX_VERTICES+1];
struct stack s;
void process_edge(int x, int y){
    //printf("%d -> %d\n ", x, y);
}

void process_vertex_late(node){
    push(&s, node);
}


void dfs(struct graph *g, int node){
    struct edge *tmp = g->edges[node];
    time++;
    entry_time[node] = time;
    discovered[node] = 1;
    while(tmp){
        int y = tmp->y;
        if(!discovered[y]){
            parent[y] = node;
            process_edge(node, y);
            dfs(g, y);
        } else if(!processed[y]){
            if(parent[node] != y){
                printf("Sorry, %d -> %d this is not a DAG !\n", node, y);
            }
        }
        tmp = tmp->next;
    }
    time++;
    process_vertex_late(node);
    exit_time[node] = time;
    processed[node] = 1;
    printf("\n");
}

void init_stack(struct stack *s){
    s->top = -1;
}

void topological_sort(struct graph *g){
    init_stack(&s);
    dfs(g, 1);
    int i = 0;
    while(!empty(&s)){
        printf("%d ->", pop(&s));
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
        int x = 0, y =0;
        scanf("%d %d", &x, &y);
        insert_edge(&g, x, y, directed);
    }
    for(i=1; i < MAX_VERTICES+1; i++){
        processed[i] = 0;
        parent[i] = -1;
        discovered[i] = 0;
        entry_time[i] = 0;
        exit_time[i] = 0;
    }

    topological_sort(&g);
    exit(0);
}

