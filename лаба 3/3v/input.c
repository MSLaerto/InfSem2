#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
int prost(int a){
    int c = a;
    while (1){
        int f = 1;
        for (int i = 2; i<c; i++){
            if (c % i == 0){
                f = 0;
                break;
            }
        }
        if (f){
            return c;
        }
        c += 1;
    }
}
char *getStr(){
    char *ans = malloc(sizeof(char));
    char n;
    int len = 0;
    n = getchar();
    while(n != EOF && n != '\n'){
        ans = realloc(ans, sizeof(char) * (len + 2));
        ans[len] = n;
        len += 1;
        n = getchar();
    }
    ans[len] = '\0';
    return ans;
}
int getInt(){
    int n, a;
    do{
        n = scanf("%d", &a);
        if (n < 0){
            return 0;
        }
        if (n == 0 || a < 0){
            printf("Invalid character entered, try again:\n");
            scanf("%*[^\n]");
            scanf("%*c");
        }
    }while(n == 0 || a < 0);
    scanf("%*[^\n]");
    scanf("%*c");
    return a;
}

