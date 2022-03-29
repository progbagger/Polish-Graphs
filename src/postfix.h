#ifndef SRC_POSTFIX_H_
#define SRC_POSTFIX_H_

#include "stack.h"

typedef struct {
    char op;
    int priority;
} Operator;

Operator add_operator(const char op);
char *infix_to_postfix(const char *str);
double calc_postfix(const char *str, const double x);

#endif  // SRC_POSTFIX_H_
