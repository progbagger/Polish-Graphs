#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_analysis.h"
#include "stack.h"

Stack *create() {
    Stack *S;
    S = (Stack*)malloc(sizeof(Stack));
    S->top = NULL;
    return S;
}

int top(Stack *S) {
    int ret;
    if (S->top) {
        ret = (S->top->prio);
    } else {
        ret = 0;
    }
    return ret;
}

char topD(Stack *S) {
    char ret;
    if (S->top) {
        ret = (S->top->data);
    } else {
        ret = 0;
    }
    return ret;
}

char pop(Stack *S) {
    char a;
    Node *p;
    p = S->top;
    a = p->data;
    S->top = p->next;
    free(p);
    return a;
}

void push(Stack *S, char d, int pr) {
    Node *p;
    p =(Node *) malloc(sizeof(Node));
    p->data = d;
    p->prio = pr;
    p->next = S->top;
    S->top = p;
}

char *infix_to_postfix(char *strng) {
    Stack *S = create();
    int n = strlen(strng);
    char *postfix = NULL;
    int topPr = 0;
    int i = 0;
    while (strng[i]) {
        char tmp = strng[i];
        int prio = 0;
        switch (tmp) {
            case '(':
                prio = 5;
                if (prio >= topPr) {
                    push(S, tmp, prio);
                    topPr = prio;
                }
            break;
            case ')':
                prio = 1;
                
                    while (topD(S) != '(') {
                        postfix = str_push(postfix, pop(S));
                        postfix = str_push(postfix, ' ');
                    }
                    pop(S);
                    topPr = 5;
            break;
            case '+':
                prio = 2;
                switchCase(S, prio, &postfix, &topPr, tmp);
            break;
            case '-':
                prio = 2;
                switchCase(S, prio, &postfix, &topPr, tmp);
            break;
            case '*':
                prio = 3;
                switchCase(S, prio, &postfix, &topPr, tmp);
            break;
            case '/':
                prio = 3;
                switchCase(S, prio, &postfix, &topPr, tmp);
            break;
            case 's':
                prio = 4;
                switchCase(S, prio, &postfix, &topPr, tmp);
            break;
            case 'c':
                prio = 4;
                switchCase(S, prio, &postfix, &topPr, tmp);
            break;
            case 't':
                prio = 4;
                switchCase(S, prio, &postfix, &topPr, tmp);
            break;
            case 'l':
                prio = 4;
                switchCase(S, prio, &postfix, &topPr, tmp);
            break;
            case 'q':
                prio = 4;
                switchCase(S, prio, &postfix, &topPr, tmp);
            break;
            case 'g':
                prio = 4;
                switchCase(S, prio, &postfix, &topPr, tmp);
            break;
            case '^':
                prio = 4;
                switchCase(S, prio, &postfix, &topPr, tmp);
            break;
            default:
                if (strng[i + 1] != '(' && strng[i + 1] != ')' &&
                strng[i + 1] != '*' && strng[i + 1] != '/' &&
                strng[i + 1] != '+' && strng[i + 1] != '-' &&
                strng[i + 1] != '^' && strng[i + 1] != 's' &&
                strng[i + 1] != 't' && strng[i + 1] != 'c' &&
                strng[i + 1] != 'l') {
                    postfix = str_push(postfix, tmp);
                } else {
                    postfix = str_push(postfix, tmp);
                    postfix = str_push(postfix, ' ');
                }
        }
        i++;
    }
    if (i == n) {
            if (strng[i - 1] - '0' >= 0 && strng[i - 1] - '9' <= 9) {
                postfix = str_push(postfix, ' ');
            }
            while (S->top != NULL) {
                if (S->top->next != NULL) {
                    postfix = str_push(postfix, pop(S));
                    postfix = str_push(postfix, ' ');
                } else {
                    postfix = str_push(postfix, pop(S));
                }
            }
        }
    if (strng)
        free(strng);
    return postfix;
}

void switchCase(Stack *S, int pri, char **posfix, int *toPr, char temp) {
    if (pri > *toPr) {
        push(S, temp, pri);
        *toPr = pri;
    } else {
        while (pri <= *toPr && topD(S) != '(') {
            *posfix = str_push(*posfix, pop(S));
            *posfix = str_push(*posfix, ' ');
            *toPr = top(S);
        }
        push(S, temp, pri);
        *toPr = pri;
    }
}

void destroy(Stack *S) {
    while (S->top != NULL) {
        Node *p = S->top;
        S->top = p->next;
        free(p);
    }
    free(S);
}
