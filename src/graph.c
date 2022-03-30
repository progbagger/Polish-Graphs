#include "graph.h"

#include <math.h>
#include <stdio.h>

void null_matrix(int matrix[][M]) {
    for (size_t i = 0; i < N; i++)
        for (size_t j = 0; j < M; j++)
            matrix[i][j] = 0;
}

// Output plot of expression
void print_graph(const char *s, double (*func)(const char *, const double)) {
    int matrix[N][M];
    null_matrix(matrix);
    double x_y[2][M];
    double x_step = (double) (_MAX_X - _MIN_X) / (double) (M - 1);
    double y_step = (double) (_MAX_Y - _MIN_Y) / (double) (N - 1);
    for (size_t i = 0; i < M; i++) {
        x_y[0][i] = _MIN_X + (double) i * x_step;
        x_y[1][i] = func(s, x_y[0][i]);
    }
    double y_a[N];
    for (size_t i = 0; i < N; i++)
        y_a[i] = _MIN_Y + (double) i * y_step;
    for (size_t x = 0; x < M; x++) {
        for (size_t y = 0; y < N - 1; y++) {
            if (x_y[1][x] >= y_a[y] && x_y[1][x] <= y_a[y + 1]) {
                if (x_y[1][x] < (y_a[y] + y_a[y + 1]) / 2)
                    matrix[y][x] = 1;
                else
                    matrix[y + 1][x] = 1;
            }
        }
    }
    printf("Printing plot for equation in postfix notation: y = %s\n", s);
    printf("Params - ");
    printf("Step at X axis: %-8.2lf ", x_step);
    printf("Step at Y axis: %-8.2lf\n\n", y_step);
    for (size_t j = 0; j < 8 + 1; j++)
        printf(" ");
    printf("%-8.2lf", (double) _MIN_X);
    for (size_t j = 0; j < M - 16; j++)
        printf(" ");
    printf("%8.2lf\n", (double) _MAX_X);
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j <= M; j++) {
            if (j == 0) {
                printf("%8.2lf ", y_a[i]);
            } else {
                if (matrix[i][j - 1] == 1)
                    printf("*");
                else
                    printf("-");
            }
        }
        if (i != N - 1)
            printf("\n");
    }
}
