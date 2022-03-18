#include "graph.h"

void graph(int array[][X]) {
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            if (array[i][j] == 0)
                printf(".");
            else
                printf("*");
        }
        printf("\n");
    }
}

void print_g(int matrix[][X], const char *s, double (*func)(const char *, double)) {
    double digit[2][X];
    double shift = 0;
    double yy[Y - 4];
    for (int i = 0; i < X; i++) {
        digit[0][i] = shift;
        shift += 4 * M_PI / 79.0;
        digit[1][i] = round(10 * func(s, digit[0][i])) / 10.0;
    }
    shift = -1;
    for (int i = 2; i < Y - 2; i++) {
        yy[i - 2] = round(10 * shift) / 10.0;
        shift += 1.0 / 10.0;
    }
    for (int j = 0; j < X; j++) {
        for (int i = 2; i < Y - 2; i++)
            if (digit[1][j] == yy[i - 2]) {
                matrix[i][j] = 1;
            }
    }
}
