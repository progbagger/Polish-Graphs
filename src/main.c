#include "string_analysis.h"
#include "stack.h"
#include "graph.h"
#include "postfix.h"

int main() {
    char *str = str_input();
    str = str_del_sp(str);
    char *result = NULL;
    if (str)
        result = infix_to_postfix(str);
    if (result)
        print_graph(result, calc_postfix);
    str_free(result);
    str_free(str);
    return 0;
}
