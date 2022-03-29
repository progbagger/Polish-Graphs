#include "string_analysis.h"
#include "stack.h"
#include "graph.h"
#include "postfix.h"

int main() {
    char *str = str_input();
    str = str_del_sp(str);
    char *result = infix_to_postfix(str);
    if (result)
        printf("%s\n", result);
    double x = calc_postfix(result, M_PI / 2);
    printf("%.1lf", x);
    str_free(result);
    str_free(str);
    return 0;
}
