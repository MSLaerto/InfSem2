#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "input.h"
int input(char **line){
    char n;
    int count_o = 0, count_v = 0, len = 0;
    n = getchar();
    while (n != '\n' && n != EOF){
        if (n != ' ') {
            if (!((n >= 'a' && n <= 'z') || (n >= 'A' && n <= 'Z') || n == '+' || n == '*' || n == '/' || n == '-')){
                return 0;
            }
            else if (n == '+' || n == '*' || n == '/' || n == '-'){
                count_o += 1;
            }
            else{
                count_v += 1;
            }
            (*line) = realloc((*line), sizeof(char) * (len + 2));
            (*line)[len] = n;
            (*line)[len+1] = '\0';
            len += 1;
        }
        n = getchar();
    }
    if (n == EOF || count_v - count_o != 1){
        return 0;
    } else{
        return 1;
    }
}
