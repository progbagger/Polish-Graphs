#ifndef SRC_STRING_ANALYSIS_H_
#define SRC_STRING_ANALYSIS_H_

#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

char *str_input();
char *str_del_sp(char *str);
char *str_push(char *str, const char c);
int str_to_int(const char *str);
char *str_free(char *str);

#endif  // SRC_STRING_ANALYSIS_H_
