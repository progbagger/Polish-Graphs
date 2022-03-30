#include "string_analysis.h"

// Pushing symbol into string
char *str_push(char *str, const char c) {
    if (str != NULL) {
        char *p = str;
        str = realloc(p, (strlen(str) + 2) * sizeof(char));
        str[strlen(str) + 1] = '\0';
        str[strlen(str)] = c;
    } else {
        str = malloc(2 * sizeof(char));
        str[1] = '\0';
        str[0] = c;
    }
    return str;
}

// Deleting string
char *str_free(char *str) {
    if (str)
        free(str);
    return NULL;
}

// Getting string from stdin
char *str_input() {
    char *result = NULL, c = getchar();
    while (c != '\0' && c != '\n') {
        result = str_push(result, c);
        c = getchar();
    }
    return result;
}

// Deleting spaces and prepairing string to converting
char *str_del_sp(char *str) {
    const char ops[] = "+_-*/()";
    char *result = NULL;
    int i = 0;
    if (str) {
        while (str[i]) {
            if (str[i] == 's') {
                if (str[i + 1] == 'i' && str[i + 2] == 'n') {
                    result = str_push(result, 's');
                    i += 2;
                } else if (str[i + 1] == 'q' && str[i + 2] == 'r' && str[i + 3] == 't') {
                    result = str_push(result, 'q');
                    i += 3;
                }
            } else if (str[i] == 'c') {
                if (str[i + 1] == 'o' && str[i + 2] == 's') {
                    result = str_push(result, 'c');
                    i += 2;
                } else if (str[i + 1] == 't' && str[i + 2] == 'g') {
                    result = str_push(result, 'g');
                    i += 2;
                }
            } else if (str[i] == 't' && str[i + 1] == 'g') {
                result = str_push(result, 't');
                i += 1;
            } else if (str[i] == 'l' && str[i + 1] == 'n') {
                result = str_push(result, 'l');
                i += 1;
            } else if (str[i] == ' ') {
                i++;
                continue;
            } else if (str[i] == '-' && str[i + 1] != ' ') {
                result = str_push(result, '_');
            } else if ((str[i] >= '0' && str[i] <= '9') || strchr(ops, str[i]) || str[i] == 'x') {
                result = str_push(result, str[i]);
            } else {
                printf("[ERROR] Incorrect expression");
                result = str_free(result);
                break;
            }
            i++;
        }
    }
    str_free(str);
    return result;
}

// Converting string into int
int str_to_int(const char *str) {
    int temp = 0, result = 0, i = 0;
    while (str[i] != '\0') {
        if (str[i] - '0' >= 0 && str[i] - '9' <= 9) {
            temp += ((int) (str[i] - '0')) * pow(10, i);
            i++;
        } else {
            result = -1;
            break;
        }
    }
    i--;
    if (result != -1) {
        for (; i >= 0; i--) {
            result += (temp % 10) * pow(10, i);
            temp /= 10;
        }
    }
    return result;
}
