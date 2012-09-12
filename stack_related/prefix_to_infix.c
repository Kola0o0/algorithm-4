#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//scanf("%d%*[\t\n ]%c", &j, &ch);
#define MAXSIZE 100

struct stack{
    int top;
    char arr[MAXSIZE][MAXSIZE];
};

int empty(struct stack *s){
    return (s->top == -1);
}

void push(struct stack *s, char *elem){
    if (s->top < MAXSIZE)
        strcpy(s->arr[++s->top], elem);
}

char* pop(struct stack *s){
    if (!empty(s))
        return s->arr[s->top--];
    return NULL;
}

char* stacktop(struct stack *s){
    return s->arr[s->top];
}

int isoperator(char* elem){
    char ch = elem[0];
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '$' )
        return 1;
    return 0;
}

int main(){
    struct stack s;
    s.top = -1;

    char expression[MAXSIZE];
    int i=0, resp=0, ch=0;
    while((ch = getchar()) != '\n')
        expression[i++] = ch;
    expression[i] = '\0';
    char tmp[MAXSIZE];
    sprintf(tmp, "%c", expression[0]);
    push(&s, tmp);
    sprintf(tmp, "%c", expression[1]);
    push(&s, tmp);
    sprintf(tmp, "%c", expression[2]);
    push(&s, tmp);

    printf("%d\n", __LINE__);
    for(i=3; expression[i]; i++){
        do{
            char *op1 = pop(&s);
            char *op2 = pop(&s);
            char *operator = pop(&s);
            if(!isoperator(op1) && !isoperator(op2)){
                sprintf(tmp, "(%s %s %s)", op2, operator, op1);
                push(&s, tmp);
                //printf("Pushed:%s\n", tmp);

            } else {
                if(operator)
                    push(&s, operator);
                if(op2)
                    push(&s, op2);
                if(op1)
                    push(&s, op1);
                break;
            }
        } while(!empty(&s));
        sprintf(tmp, "%c", expression[i]);
        push(&s, tmp);
        //printf("Pushed:%s\n", tmp);
    }
    printf("%d\n", __LINE__);
    char *result = pop(&s);
    while(!empty(&s)){
        char *operand2 = pop(&s);
        char *operator = pop(&s);
        sprintf(tmp, "(%s %s %s)", operand2, operator, result);
        push(&s, tmp);
        result = pop(&s);
    }
    printf("Result: %s\n", result);
    exit(0);
}

