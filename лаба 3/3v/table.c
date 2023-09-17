#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "type.h"
#include "input.h"
#include "table.h"
int init(Table *board){
    printf("Enter the maximum table size\n");
    int k = getInt();
    if (k == 0){
        return 0;
    }
    int len = prost(k);
    printf("Memory allocated for %d elements.\n", len);
    board->ks = calloc(len, sizeof(KeySpace));
    board->msize = len;
    int i = 0;
    return 1;
}
int input(Table *board) {
    FILE *start;
    printf("Enter file name:\n");
    char *st = getStr(), st1[100], st2[100];
    start = fopen(st, "r");
    if (start == NULL) {
        printf("No such file exists.\n");
        free(st);
        return 1;
    }
    while (!feof(start)){
        unsigned int res;
        unsigned int res2;
        fscanf(start, "%d[^\n]", &res);
        fscanf(start, "%*1[\n]");
        fscanf(start, "%d[^\n]", &res2);
        fscanf(start, "%*1[\n]");
        Add(board, res, res2);
    }
    free(st);
    fclose(start);
    return 1;
}
int count_rel(Table *board, unsigned int key){
    int i = 0;
    int rel = 0;
    while (i < board->msize){
        unsigned int h = (hash1(key, board) + i * hash2(key, board))%board->msize;
        if (board->ks[h].info){
            if (board->ks[h].key == key && board->ks[h].busy != 0){
                rel += 1;
            }
        }
        else{
            break;
        }
        i += 1;
    }
    return rel;
}
unsigned int hash1(unsigned int key, Table *board){
    unsigned int i = 0;
    for (int j = 0; j < key / 3; j++){
        i += key * 3;
    }
    for (int j = 0; j < key/2; j++){
        i += key * 2;
    }
    for (int j = 0; j < key; j++){
        i += key;
    }
    return i % board->msize;
}
unsigned int hash2(unsigned int key, Table *board) {
    unsigned int i = 0;
    for (int j = 0;j < key; j++){
        i += key;
    }
    return i % (board->msize - 1) + 1;
}
int Add(Table *board, unsigned int key, unsigned int el){
    int i = 0;
    int r = 1;
    while (i < board->msize){
        unsigned int h = (hash1(key, board) + i * hash2(key, board))%board->msize;
        if (board->ks[h].busy == 0){
            board->ks[h].info = malloc(sizeof(Item));
            board->ks[h].info->element = el;
            board->ks[h].key=key;
            board->ks[h].release = r;
            board->ks[h].busy=1;
            return 1;
        }
        if ((board->ks[h].busy==1)&& board->ks[h].key == key){
            r += 1;
        }
        i++;
    }
    return 0;
}
Table Find(Table *board, unsigned int key){
    int i = 0;
    Table board2 = {NULL, 0};
    while (i < board->msize){
        unsigned int h = (hash1(key, board) + i * hash2(key, board))%board->msize;
        if (board->ks[h].info){
            if (board->ks[h].key == key && board->ks[h].busy != 0){
                 board2.ks = realloc(board2.ks, sizeof(KeySpace) * (board2.msize + 1));
                 board2.ks[board2.msize].info = malloc(sizeof(Item));
                 board2.ks[board2.msize].busy = board->ks[h].busy;
                 board2.ks[board2.msize].key = board->ks[h].key;
                 board2.ks[board2.msize].release = board->ks[h].release;
                 board2.ks[board2.msize].info->element = board->ks[h].info->element;
                 board2.msize += 1;
            }
        }
        else{
            break;
        }
        i += 1;
    }
    return board2;
}
int Delete(Table *board, unsigned int key){
    int rel = count_rel(board, key);
    int i = 0;
    printf("Enter the version of the item you want to remove or 0 if all:\n");
    int r = getInt();
    if (r != 0){
        while (i < board->msize){
            unsigned int h = (hash1(key, board) + i * hash2(key, board))%board->msize;
            if (board->ks[h].info){
                if (board->ks[h].key == key && board->ks[h].busy != 0 && board->ks[h].release == r){
                    board->ks[h].busy = 0;
                }
                else if (board->ks[h].key == key && board->ks[h].busy != 0 && board->ks[h].release>r){
                    board->ks[h].release -= 1;
                }
            }
            else{
                break;
            }
            i += 1;
        }
    }
    else{
        while (i < board->msize){
            unsigned int h = (hash1(key, board) + i * hash2(key, board))%board->msize;
            if (board->ks[h].info){
                if (board->ks[h].key == key && board->ks[h].busy != 0){
                    board->ks[h].busy = 0;
                }
            }
            else{
                break;
            }
            i += 1;
        }
    }
    return 1;
}
int Reorg(Table *board){
    int i = 0;
    int j = 0;
    while (i < board->msize){
        unsigned int h = (hash1(board->ks[i].key, board) + i * hash2(board->ks[i].key, board))%board->msize;
        if (board->ks[h].info){
            if (board->ks[h].busy != 0){
                board->ks[h].busy = 0;
            }
        }
        else{
            break;
        }
        i += 1;
    }
    return 1;
};
int CleanShow(Table *board){
    int f = 1;
    for (int i = 0; i < board->msize; i++){
        if (board->ks[i].busy != 0) {
            f = 0;
            printf("ind: %d busy: %d key: %d release: %d element: %d\n", i, board->ks[i].busy, board->ks[i].key, board->ks[i].release, board->ks[i].info->element);
        }
    }
    if (f){
        printf("The table is empty.\n");
    }
    return 1;
}
int DirtyShow(Table *board){
    int f = 1;
    for (int i = 0; i < board->msize; i++){
        if (board->ks[i].info){
            printf("ind: %d busy: %d key: %d release: %d element: %d\n", i, board->ks[i].busy, board->ks[i].key, board->ks[i].release, board->ks[i].info->element);
            f = 0;
        }
    }
    if (f){
        printf("The table is empty.\n");
    }
    return 1;
}
void clear(Table *board){
    for (int i = 0; i < board->msize; i++){
        if (board->ks[i].info && board->ks[i].info->element)
            free(board->ks[i].info);
    }
    free(board->ks);
}
