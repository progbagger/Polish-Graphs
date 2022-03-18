#ifndef SRC_GRAPH_H_
#define SRC_GRAPH_H_

#include <math.h>
#include <stdio.h>

#define X 80
#define Y 25

void graph(int array[][X]);
void print_g(int matrix[][X], const char *s, double (*func)(const char *, double));

#endif  // SRC_GRAPH_H_
