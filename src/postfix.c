#include "postfix.h"

#include <math.h>

// Function to create an operator
Operator add_operator(const char op) {
    // * _ is unary minus
    const char ops[] = "()+-_*/sctgl";
    const char prios[] = "994423322222";
    Operator result;
    size_t i = 0;
    while (op != ops[i])
        i++;
    result.op = ops[i];
    result.priority = prios[i] - '0';
    return result;
}

// To print full function like sin, cos an etc.
char *output_func(char *str, const char op) {
    const char *funcs[] = {
        "sin",
        "cos",
        "tg",
        "ctg",
        "ln"
    };
    const char f_l[] = "sctgl";
    size_t i = 0;
    while (f_l[i] != op)
        i++;
    for (size_t j = 0; j < strlen(funcs[i]); j++)
        str = str_push(str, funcs[i][j]);
    return str;
}

char *handle_operand(char *result, const char *str, size_t *i, const char *operands) {
    while (strchr(operands, str[*i]) && str[*i]) {
        result = str_push(result, str[*i]);
        ++(*i);
    }
    result = str_push(result, ' ');
    --(*i);
    return result;
}

char *handle_close_bracket(Stack *s, char *result, const char *funcs) {
    Operator o = *((Operator*) pop_stack(s));
    while (o.op != '(') {
        result = str_push(result, o.op);
        result = str_push(result, ' ');
        if (!is_stack_empty(s))
            o = *((Operator*) pop_stack(s));
        else
            break;
    }
    Operator *top = (Operator*) top_stack(s);
    if (top) {
        if (strchr(funcs + 2, top->op)) {
            o = *((Operator*) pop_stack(s));
            result = output_func(result, o.op);
            result = str_push(result, ' ');
        }
    }
    return result;
}

char *handle_operator(Stack *s, char *result, const char *str, const size_t i, const char *funcs) {
    Operator *top = (Operator*) top_stack(s);
    Operator c_o = add_operator(str[i]);
    if (top) {
        while ((strchr(funcs + 2, top->op) || c_o.priority >= top->priority) && !is_stack_empty(s)) {
            Operator o = *((Operator*) pop_stack(s));
            if (strchr(funcs + 2, o.op))
                result = output_func(result, o.op);
            else
                result = str_push(result, o.op);
            result = str_push(result, ' ');
            top = (Operator*) top_stack(s);
            if (!top)
                break;
        }
    }
    push_stack(s, (void*) &c_o, sizeof(Operator));
    return result;
}

char *handle_error(char *result) {
    printf("[ERROR] Reading undefined symbol.");
    result = str_free(result);
    return result;
}

void handle_func(Stack *s, const char *str, const size_t i) {
    Operator o = add_operator(str[i]);
    push_stack(s, (void*) &o, sizeof(Operator));
}

char *push_last(Stack *s, char *result, const char *funcs) {
    Operator o = *((Operator*) pop_stack(s));
    if (strchr(funcs + 2, o.op))
        result = output_func(result, o.op);
    else
        result = str_push(result, o.op);
    result = str_push(result, ' ');
    return result;
}

// Function to convert infix notation into postfix
char *infix_to_postfix(const char *str) {
    char *result = NULL;
    const char ops[] = "+-*/";
    const char funcs[] = "_(sctgl";
    const char operands[] = "0123456789x";
    Stack *s = init_stack();
    size_t i = 0;
    if (str) {
        while (str[i]) {
            if (strchr(operands, str[i])) {
                result = handle_operand(result, str, &i, operands);
            } else if (strchr(funcs, str[i])) {
                handle_func(s, str, i);
            } else if (str[i] == ')') {
                result = handle_close_bracket(s, result, funcs);
            } else if (strchr(ops, str[i])) {
                result = handle_operator(s, result, str, i, funcs);
            } else {
                result = handle_error(result);
                break;
            }
            i++;
        }
        while (!is_stack_empty(s) && result) 
            result = push_last(s, result, funcs);
        if (result)
            result[strlen(result) - 1] = '\0';
    }
    destroy_stack(s);
    return result;
}

Stack *calc_operand(Stack *s, const char *str, size_t *i, const double x, const char *operands) {
    if (str[*i] == 'x') {
        push_stack(s, (void*) &x, sizeof(double));
    } else {
        char *str_number = NULL;
        while (strchr(operands, str[*i]) && str[*i]) {
            str_number = str_push(str_number, str[*i]);
            (*i)++;
        }
        (*i)--;
        double number = (double) str_to_int(str_number);
        str_number = str_free(str_number);
        push_stack(s, (void*) &number, sizeof(double));
    }
    return s;
}

Stack *calc_operator(Stack *s, const char *str, const size_t i) {
    double x2 = *((double*) pop_stack(s)), x1 = *((double*) pop_stack(s));
    double result;
    switch (str[i]) {
        case '+':
            result = x1 + x2;
            break;
        case '-':
            result = x1 - x2;
            break;
        case '/':
            if (x2 == 0) {
                s = destroy_stack(s);
            } else {
                result = x1 / x2;
            }
            break;
        case '*':
            result = x1 * x2;
            break;
    }
    if (s)
        push_stack(s, (void*) &result, sizeof(double));
    return s;
}

Stack *calc_func(Stack *s, const char *str, size_t *i) {
    double result;
    if (str[*i] == '_') {
        result = *((double*) pop_stack(s));
        result *= -1;
    } else {
        (*i)++;
        switch (str[*i]) {
            case 'i':
                result = *((double*) pop_stack(s));
                result = sin(result);
                (*i)++;
                break;
            case 'o':
                result = *((double*) pop_stack(s));
                result = cos(result);
                (*i)++;
                break;
            case 'g':
                result = *((double*) pop_stack(s));
                result = tan(result);
                break;
            case 't':
                result = *((double*) pop_stack(s));
                if (tan(result) == 0) {
                    s = destroy_stack(s);
                } else {
                    result = (double) 1 / tan(result);
                }
                (*i)++;
                break;
            case 'n':
                result = *((double*) pop_stack(s));
                if (result == 0) {
                    s = destroy_stack(s);
                } else {
                    result = log(result);
                }
                break;
        }
    }
    if (s)
        push_stack(s, (void*) &result, sizeof(double));
    return s;
}

// Function to calculate postfix expression
double calc_postfix(const char *str, const double x) {
    double result = 500;
    const char operands[] = "0123456789x";
    const char operators[] = "-+*/";
    const char funcs[] = "sctl_";
    size_t i = 0;
    Stack *s = init_stack();
    while (str[i]) {
        if (s) {
            if (strchr(operands, str[i])) {
                s = calc_operand(s, str, &i, x, operands);
            } else if (strchr(operators, str[i])) {
                s = calc_operator(s, str, i);
            } else if (strchr(funcs, str[i])) {
                s = calc_func(s, str, &i);
            }
        }
        i++;
    }
    if (s) {
        result = *((double*) pop_stack(s));
        destroy_stack(s);
    }
    return result;
}
