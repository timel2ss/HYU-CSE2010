#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *input;
FILE *output;

typedef struct Stack {
    int *key;
    int top;
    int max_stack_size;
}Stack;

void Push(Stack *S, int X);
int Pop(Stack *S);
int Postfix(Stack *S, char input_str);
void DeleteStack(Stack *S);

Stack* CreateStack(int max);


int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Not enough arguments.\n");
        return 1;
    }
    input = fopen(argv[1], "r");
    if(input == NULL){
        printf("File cannot be found.\n");
        return 2;
    }
    output = fopen(argv[2], "wt");
    Stack *stack;
    char input_str[101];
    int max, i=0, a, b, result;

    fgets(input_str, 101, input);
    max = 10;
    stack = CreateStack(max);

    fprintf(output, "Top numbers : ");

    for(i = 0; i < strlen(input_str) && input_str[i] != '#'; i++){
        result = Postfix(stack, input_str[i]);
    }

    fprintf(output, "\nevaluation result : %d\n", result);
    fclose(input);
    fclose(output);
    DeleteStack(stack);
    return 0;
}

Stack* CreateStack(int max){
    Stack* S = NULL;
    S = (Stack*)malloc(sizeof(Stack));
    S->key = (int*)malloc(sizeof(int) * max);
    S->max_stack_size = max;
    S->top = -1;
    return S;
}

void Push(Stack *S, int X) {
    if(S->top <= S->max_stack_size)
        S->key[++(S->top)] = X;
}

int Pop(Stack *S) {
    return S->key[(S->top)--];
}

int Postfix(Stack *S, char input_str) {
    int val1, val2;
    int result = 0;
    switch(input_str){
        case '+':
            val2 = Pop(S);
            val1 = Pop(S);
            result = val1 + val2;
            fprintf(output, "%d ", result);
            Push(S, result);
            break;
        case '-':
            val2 = Pop(S);
            val1 = Pop(S);
            result = val1 - val2;
            fprintf(output, "%d ", result);
            Push(S, result);
            break;
        case '*':
            val2 = Pop(S);
            val1 = Pop(S);
            result = val1 * val2;
            fprintf(output, "%d ", result);
            Push(S, result);
            break;
        case '/':
            val2 = Pop(S);
            val1 = Pop(S);
            result = val1 / val2;
            fprintf(output, "%d ", result);
            Push(S, result);
            break;
        case '%':
            val2 = Pop(S);
            val1 = Pop(S);
            result = val1 % val2;
            fprintf(output, "%d ", result);
            Push(S, result);
            break;
        default:
            Push(S, input_str - 48);
            fprintf(output, "%c ", input_str);
            break;
    }
    return result;
}

void DeleteStack(Stack *S) {
    free(S->key);
    free(S);
}
