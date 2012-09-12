#include <stdio.h>

struct node;
struct queue;

int empty(struct queue *q);
int pop(struct queue *q);
void push(struct queue *q, int elem);

