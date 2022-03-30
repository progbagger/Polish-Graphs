#include "stack.h"

// Initialization of stack to use
Stack *init_stack() {
    Stack *s = (Stack*) malloc(sizeof(Stack));
    s->top = NULL;
    s->returned = NULL;
    s->r_size = 0;
    return s;
}

// Clean memory of the stack
Stack* destroy_stack(Stack *s) {
    if (s) {
        while (s->top) {
            struct node *elem = s->top;
            s->top = s->top->next;
            if (elem->data)
                free(elem->data);
            free(elem);
        }
        if (s->returned) {
            for (size_t i = 0; i < s->r_size; i++)
                if (s->returned[i])
                    free(s->returned[i]);
            free(s->returned);
        }
        free(s);
    }
    return NULL;
}

// Check if stack empty
int is_stack_empty(Stack *s) {
    int result = 1;
    if (s->top)
        result = 0;
    return result;
}

// Add element into stack
void push_stack(Stack *s, void *value, size_t v_size) {
    struct node *elem = (struct node*) malloc(sizeof(struct node));
    void *data = malloc(v_size);
    for (size_t i = 0; i < v_size; i++)
        *((char*) data + i) = *((char*) value + i);
    elem->data = data;
    elem->next = s->top;
    s->top = elem;
}

// Remove element from stack
void *pop_stack(Stack *s) {
    struct node *elem = s->top;
    void *result = NULL;
    if (elem) {
        s->top = s->top->next;
        result = elem->data;
        free(elem);
        void **tmp = s->returned;
        s->returned = reallocarray(tmp, ++(s->r_size), sizeof(void*));
        s->returned[s->r_size - 1] = result;
    }
    return result;
}

void *top_stack(Stack *s) {
    void *result = NULL;
    if (s->top)
        result = s->top->data;
    return result;
}
