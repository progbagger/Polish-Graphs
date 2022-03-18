#ifndef SRC_STACK_H_
#define SRC_STACK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_analysis.h"

typedef struct Node {
    char data;
    int prio;
    struct Node *next;
} Node;

typedef struct stack {
    Node * top;
} Stack;

void push(Stack *S, char d, int pr);
char pop(Stack *S);
int top(Stack *S);
char *infix_to_postfix(char *strng);
Stack *create();
char topD(Stack *S);
void switchCase(Stack *S, int prio, char **postfix, int *topPr, char tmp);

#endif  // SRC_STACK_H_
