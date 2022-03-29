#include "string_analysis.h"
#include "stack.h"
#include "cstack.h"
#include "graph.h"

#include <stdio.h>

int main() {
    char *s = str_input();
    s = infix_to_postfix(str_del_sp(s));;
    print_g(s, calc);
    if (s)
        free(s);
}
