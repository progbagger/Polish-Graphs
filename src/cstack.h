#ifndef SRC_CSTACK_H_
#define SRC_CSTACK_H_

struct cnode {
    double data;
    struct cnode* next;
};

typedef struct cstack {
    struct cnode *top;
} cstack;

cstack *init();
void cpush(const double data, cstack *s);
double cpop(cstack *s);
void c_destroy(cstack *s);

void operator(const char *expression, int *i, cstack *s);
double calc(const char *expression, double x);

#endif  // SRC_CSTACK_H_
