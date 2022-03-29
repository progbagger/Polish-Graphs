#ifndef SRC_STACK_H_
#define SRC_STACK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_analysis.h"

struct node {
    void *data;
    struct node *next;
};

typedef struct {
    struct node *top;
    void** returned;
    size_t r_size;
} Stack;

Stack *init_stack();
Stack* destroy_stack(Stack *s);
int is_stack_empty(Stack *s);

void push_stack(Stack *s, void *value, size_t v_size);
void *pop_stack(Stack *s);
void *top_stack(Stack *s);

#endif  // SRC_STACK_H_
