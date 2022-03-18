#include "cstack.h"
#include <stdlib.h>
#include <math.h>
#include "string_analysis.h"

cstack *init() {
    cstack *s = malloc(sizeof(cstack));
    s->top = NULL;
    return s;
}

void cpush(const double data, cstack *s) {
    struct cnode *p = malloc(sizeof(struct cnode));
    p->data = data;
    p->next = s->top;
    s->top = p;
}

double cpop(cstack *s) {
    double result;
    struct cnode *p = s->top;
    result = p->data;
    s->top = p->next;
    free(p);
    return result;
}

void destroy(cstack *s) {
    struct cnode *p;
    while (s->top) {
        p = s->top;
        s->top = p->next;
        free(p);
    }
}


void operator(const char *expression, int *i, cstack *s) {
    double x2, x1;
    switch (expression[*i]) {
        case '+':
            x2 = cpop(s);
            x1 = cpop(s);
            cpush(x1 + x2, s);
            break;
        case '-':
            x2 = cpop(s);
            x1 = cpop(s);
            cpush(x1 - x2, s);
            break;
        case '*':
            x2 = cpop(s);
            x1 = cpop(s);
            cpush(x1 * x2, s);
            break;
        case '/':
            x2 = cpop(s);
            x1 = cpop(s);
            cpush(x1 / x2, s);
            break;
        case '^':
            x2 = cpop(s);
            x1 = cpop(s);
            cpush(pow(x1, x2), s);
            break;
        case 's':
            x2 = cpop(s);
            cpush(sin(x2), s);
            break;
        case 'c':
            x2 = cpop(s);
            cpush(cos(x2), s);
            break;
        case 't':
            x2 = cpop(s);
            cpush(tan(x2), s);
            break;
        case 'g':
            x2 = cpop(s);
            cpush(1 / tan(x2), s);
            break;
        case 'l':
            x2 = cpop(s);
            cpush(log(x2), s);
            break;
        case 'q':
            x2 = cpop(s);
            cpush(sqrt(x2), s);
            break;
    }
    (*i)++;
    if (expression[*i])
        (*i)++;
}

double calc(const char *expression, double x) {
    int i = 0;
    char *digit = NULL;
    cstack *s = init();
    while (expression[i]) {
        if (expression[i] - '0' >= 0 && expression[i] - '9' <= 9) {
            digit = str_push(digit, expression[i]);
            i++;
        } else if (expression[i] == ' ') {
            int d = str_to_int(digit);
            cpush(d, s);
            free(digit);
            digit = NULL;
            i++;
        } else if (expression[i] == 'x') {
            cpush(x, s);
            i += 2;
        } else {
            operator(expression, &i, s);
        }
    }
    if (digit != NULL)
        free(digit);
    double result = cpop(s);
    destroy(s);
    return result;
}
