/*
 *Program to print all paths in a graph.
 *Using backtracking.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#define MAX 100
//scanf("%d%*[\t\n ]%c", &j, &ch);

struct edge {
    int y;
    int weight;
    struct edge *next;
};

struct graph {
  int num_edges;
  int num_vertices;
  struct edge *edges[MAX+1];
  int degree[MAX+1];
  int directed;
};


int finished = 0;
struct graph g;

int correct_solution(int a[], int k, int input){
    return (a[k] == input);
}

void process_solution(int a[], int input){
    int i = 1;
    while(a[i] != input){
        printf("%d ->", a[i]);
        i++;
    }
    printf("%d\n", input);
    finished = 1;
}

void construct_candidates(int a[], int k, int input, int candidates[], int *num_candidates){
    int in_sol[MAX];
    int i = 0;
    for(; i < MAX; i++)
        in_sol[i] = 0;
    for(i=1; i <= k; i++)
        in_sol[a[i]] = 1;

    if(k == 1){
        candidates[0] = 1;
        *num_candidates = 1;

    } else {
        *num_candidates = 0;
        struct edge * e = g.edges[a[k-1]];
        while(e){
            int y = e->y;
            if(!in_sol[y]){
                candidates[*num_candidates] = y;
                *num_candidates = *num_candidates +1;
            }
            e = e->next;
        }

    }
}

void init_graph(struct graph *g, int directed){
    g->num_edges = 0;
    g->num_vertices = 0;
    g->directed = directed;
    int i = 1;
    for(; i<= MAX; i++){
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



void backtrack(int a[], int k, int input){
    int candidates[MAX];
    int num_candidates = 0;
    if(correct_solution(a, k, input)){
        process_solution(a, input);
    } else {
        k++;
        construct_candidates(a, k, input, candidates, &num_candidates);
        int j = 0;
        for(; j<num_candidates; j++){
            a[k] = candidates[j];
            backtrack(a, k, input);
            if(finished)
                return;
        }

    }
}



int main(){
    int directed = 0;
    init_graph(&g, directed);
    scanf("%d %d", &(g.num_vertices), &(g.num_edges));
    int i = 0;
    for(; i < g.num_edges; i++){
        int x = 0, y =0;
        scanf("%d %d", &x, &y);
        insert_edge(&g, x, y, directed);
    }
    int a[MAX+1] = {0,1,2,3,4,5};
    backtrack(a, 0, 5);
    exit(0);
}

