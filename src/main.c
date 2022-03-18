#include "string_analysis.h"
#include "stack.h"
#include "cstack.h"
#include "graph.h"

#include <stdio.h>

int main() {
    char *s = str_input();
    s = infix_to_postfix(str_del_sp(s));;
    int field[Y][X];
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            field[i][j] = 0;
        }
    }
    print_g(field, s, calc);
    graph(field);
}
