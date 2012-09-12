#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
//scanf("%d%*[\t\n ]%c", &j, &ch);

enum member { int_type, float_type, char_type };
struct stackelem {
    int type;
    union {
        int i_elem;
        char c_elem;
        float f_elem;
    } value;
};

struct stack {
    int top;
    struct stackelem arr[MAXSIZE];
};


void push(struct stack* s, struct stackelem elem){
    if (s->top < MAXSIZE)
        s->arr[++s->top] = elem;
}

struct stackelem pop(struct stack *s){
    if (!empty(s))
        return s->arr[s->top--];
}

int empty(struct stack *s){
    return s->top == -1;
}


int main(){
    struct stack s;
    s.top = -1;
    struct stackelem elem1, elem2, elem3, elem4;
    elem1.type = int_type;
    elem1.value.i_elem = 4;

    elem2.type = char_type;
    elem2.value.c_elem = 'c';

    elem3.type = float_type;
    elem3.value.f_elem = 4.0;

    push(&s, elem1);
    push(&s, elem2);
    push(&s, elem3);

    elem4 = pop(&s);
    elem4 = pop(&s);
    if (elem4.type == int_type)
        printf("%d\n", elem4.value.i_elem);
    else if (elem4.type == char_type)
        printf("%c\n", elem4.value.c_elem);
    else
        printf("%f\n", elem4.value.f_elem);


    exit(0);
}

