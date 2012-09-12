#include <stdio.h>
#include <stdlib.h>
//scanf("%d%*[\t\n ]%c", &j, &ch);
#define MAXSIZE 100

struct stack{
    int top;
    int arr[MAXSIZE];
};

int empty(struct stack *s){
    return (s->top == -1);
}

void push(struct stack *s, int elem){
    if (s->top < MAXSIZE)
        s->arr[++s->top] = elem;
}

int pop(struct stack *s){
    if (!empty(s))
        return s->arr[s->top--];
}

int stacktop(struct stack *s){
    return s->arr[s->top];
}

int isoperator(int ch){
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')')
        return 1;
    return 0;
}

int precedes(int operator1, int operator2){
    if(operator1 == '(' || operator2 == ')'){
        return 1;
    } else if (operator1 == ')'){
        return 0;
    } else if (operator1 == '*'){
        if(operator2 == '(' || operator2 == '*' || operator2 == '/')
            return 0;
        return 1;
    } else if (operator1 == '/'){
        if(operator2 == '(' || operator2 == '*' || operator2 == '/')
            return 0;
        return 1;
    } else {
        return 0;
    }
}

int main(){
    struct stack s;
    s.top = -1;

    char expression[MAXSIZE];
    char result[MAXSIZE];
    int i=0, resp=0, ch=0;
    while((ch = getchar()) != '\n')
        expression[i++] = ch;
    expression[i] = '\0';

    for(i=0; expression[i]; i++){
        if (isoperator(expression[i])){
            if(precedes(stacktop(&s), expression[i])){
                if((stacktop(&s) != '(') && (stacktop(&s) != ')'))
                    result[resp++] = pop(&s);
                else
                    pop(&s);
            }
            push(&s, expression[i]);
            printf("Pushed %c to stack. Result: %s\n", expression[i], result);
        }
        else{
            result[resp++] = expression[i];
        }
    }
    while(!empty(&s)){
        if ((stacktop(&s) != '(') && (stacktop(&s) != ')'))
            result[resp++] = pop(&s);
        else
            pop(&s);
    }

    result[resp] = '\0';

    printf("Result is: %s\n", result);
    exit(0);
}

