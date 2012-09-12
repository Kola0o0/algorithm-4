#include <stdio.h>
#include <stdlib.h>
//scanf("%d%*[\t\n ]%c", &j, &ch);

#define MAXSIZE 100
struct stack{
    int top;
    int arr[MAXSIZE];
};

void push(struct stack *s, int elem){
    if (s->top < MAXSIZE)
        s->arr[++s->top] = elem;
}

int pop(struct stack *s){
    if (!empty(s))
        return s->arr[s->top--];
}

int empty(struct stack *s){
    return s->top == -1;
}

int stacktop(struct stack *s){
    return s->arr[s->top];
}


int isvalidparan(struct stack* s, int ch){
    switch(ch){
        case '}': return (stacktop(s) == '{');
        case ')': return (stacktop(s) == '(');
        case ']': return (stacktop(s) == '[');
        default: return 0;
    }
}

int isopeningparan(int ch){
    switch(ch){
        case '{':
        case '(':
        case '[':return 1;
        default: return 0;
    }
}

int isclosingparan(int ch){
    switch(ch){
        case '}':
        case ')':
        case ']':return 1;
        default: return 0;
    }
}


int main(){
    struct stack stack1;
    stack1.top = -1;
    char expression[MAXSIZE];
    int ch, i = 0,length = 0, paranbalance = 0;
    while((ch = getchar()) != '\n'){
        expression[i++] = ch;
    }
    expression[i] = '\0';
    for(i =0; expression[i]; i++){
        if (isopeningparan(expression[i])){
            push(&stack1, expression[i]);
            paranbalance += 1;
        }
        else if (isclosingparan(expression[i])){
                if(isvalidparan(&stack1, expression[i])){
                    paranbalance -= 1;
                    pop(&stack1);
                }
                else{
                    break;
                }
        }
        else
            continue;
    }
    printf("Expression is %s\n", paranbalance ? "Invalid" : "Valid");
    exit(0);
}

