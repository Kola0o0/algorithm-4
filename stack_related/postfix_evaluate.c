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

int isoperator(int ch){
    switch(ch){
        case '+':
        case '-':
        case '*':
        case '/': return 1;
        default: return 0;
    }
}

int perform(int op1, int operator, int op2){
    switch(operator){
        case '+': return op1 + op2;
        case '-': return op1 - op2;
        case '*': return op1 * op2;
        case '/': return op1/op2;
    }
}

int main(){
    struct stack stack1;
    stack1.top = -1;
    char expression[MAXSIZE];
    int ch, i = 0,length = 0;
    while((ch = getchar()) != '\n'){
        expression[i++] = ch;
    }
    expression[i] = '\0';

    for(i =0; expression[i]; i++){
        if (isoperator(expression[i])){
            int operand2 = pop(&stack1);
            int operand1 = pop(&stack1);
            int result = perform(operand1, expression[i], operand2);
            push(&stack1, result);
        }
        else{
            push(&stack1, expression[i]-'0');
        }
    }

    printf("Result: %d", pop(&stack1));
    exit(0);
}

