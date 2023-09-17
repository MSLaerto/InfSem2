#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "type.h"
#include "input.h"
#include "table.h"
#include "menu.h"
int main() {
    Table board = {NULL, N};
    if (init(&board) == 0){
        return 0;
    }
    int num_func;
    int (*fptr[])(Table *) = {NULL, menu_add, menu_find, menu_delete, CleanShow, DirtyShow, input , Reorg};
    while(num_func = menu()){
        if (!fptr[num_func](&board)){
            break;
        }
    }
    clear(&board);
    printf("END");
    return 0;
}
