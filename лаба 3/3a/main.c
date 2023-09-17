#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Item{
    char *element;
}Item;
typedef struct KeySpace{
    Item *info; // Сам предмет
    char *key; // ключ элемента
    int busy; // признак занятости элемента

}KeySpace;
typedef struct Table{
    KeySpace *ks; // указатель на пространство ключей
    int msize; // размер области пространства ключей
    int csize; // количество элементов в области пространства ключей
}Table;
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
            printf("Invalid character entered, please try again:\n");
            scanf("%*[^\n]");
            scanf("%*c");
        }
    }while(n == 0 || a < 0);
    scanf("%*[^\n]");
    scanf("%*c");
    return a;
}
int Add(Table *board){
    if (board->csize == board->msize) {
        printf("Error: Overflow. Try Reorganization.\n");
        return 1;
    }
    printf("Enter key:\n");
    char *key = getStr();
    for (int i = 0 ; i<board->csize ; i++){
        if (strcmp(key ,board->ks[i].key) == 0){
            printf("An element with this key is already in the table\n");
            return 1;
        }
    }
    board->ks = realloc(board->ks, sizeof(KeySpace) * (board->csize + 1));
    board->ks[board->csize].info = malloc(sizeof(Item));
    board->ks[board->csize].busy = 1;
    board->ks[board->csize].key = key;
    printf("Enter value by key:\n");
    char *el = getStr();
    board->ks[board->csize].info->element = el;
    board->csize += 1;
    return 1;
}

int Find(Table *board) {
    printf("Enter the key whose elements you want to see:\n");
    char *key = getStr();
    int f = 1;
    for (int i = 0; i < board->csize; i++) {
        if (strcmp(board->ks[i].key, key) == 0 && board->ks[i].busy != 0) {
            printf("busy: %d key: %s element: %s\n", board->ks[i].busy, board->ks[i].key, board->ks[i].info->element);
        }
        if (f) {
            printf("No such key exists.\n");
        }
        free(key);
        return 1;
    }
}
int StrHash(char *str){
    int hash = 0 ;
    for (int i = 0 ; i < strlen(str); i++){
        hash = hash + str[i];
    }
    return hash;
}
int DeleteRange(Table *board){
    int key1_int;
    int key2_int;
    printf("Enter the first key from the range:\n");
    char *key1 = getStr();
    printf("Enter the second key from the range:\n");
    char *key2 = getStr();
    if (StrHash(key1) < StrHash(key2)){
        key1_int = StrHash(key1);
        key2_int = StrHash(key2);
    }else{
        key1_int = StrHash(key2);
        key2_int = StrHash(key1);
    }
    for (int i = key1_int ; i <= key2_int ; i++ ){
        for (int j = 0; j < board->csize; j++){
            if (StrHash(board->ks[j].key) == i && board->ks[j].busy == 1) {
                board->ks[j].busy = 0;
            }
        }
    }
    free(key1);
    free(key2);
    return 1 ;
}
int Delete(Table *board){
    printf("Enter the key of the element to be removed:\n");
    char *key = getStr();
    for (int i = 0; i < board->csize; i++){
        if (strcmp(board->ks[i].key, key) == 0 && board->ks[i].busy == 1) {
            board->ks[i].busy = 0;
        }
    }
    free(key);
    return 1;
}
int CleanShow(Table *board){
    int f = 1;
    if (board->csize == 0){
        printf("The table is empty.\n");
        return 1;
    }
    for (int i = 0; i < board->csize; i++){
        if (board->ks[i].busy != 0) {
            f = 0;
            printf("busy: %d key: %s element: %s\n", board->ks[i].busy, board->ks[i].key, board->ks[i].info->element);

        }
    }
    if (f){
        printf("The table is empty.\n");
    }
    return 1;
}
int DirtyShow(Table *board){
    if (board->csize == 0){
        printf("The table is empty.\n");
        return 1;
    }
    for (int i = 0; i < board->csize; i++){
        printf("busy: %d key: %s element: %s\n", board->ks[i].busy, board->ks[i].key, board->ks[i].info->element);
    }
    return 1;
}
int Reorg(Table *board){
    int i = 0;
    while (i < board->csize){
        if (board->ks[i].busy == 0) {
            free(board->ks[i].key);
            free(board->ks[i].info->element);
            for (int j = i; j < board->csize - 1; j++) {
                board->ks[j].busy = board->ks[j + 1].busy;
                board->ks[j].key = board->ks[j + 1].key;
                board->ks[j].info->element = board->ks[j + 1].info->element;
            }
            board->csize -= 1;
            free(board->ks[board->csize].info);
            board->ks = realloc(board->ks, sizeof(KeySpace) * board->csize);
            i -= 1;
        }
        i += 1;
    }
    return 1;
}

int menu(){
    const char *msg[] = {"0. Quit", "1. Add", "2. Find", "3. Delete", "4. DeleteRange","5. Clean Show", "6. Dirty Show", "7. Reorganization" , "8. ReadFromFile"};
    const int msg_count = sizeof(msg) / sizeof(msg[0]);
            int n;
            for (int i = 0; i < msg_count; i++){
                printf("%s\n", msg[i]);
            }
            printf("Input command:\n");
            do{
                n = getInt();
                if (n < msg_count && n >= 0){
                    return n;
                }
                printf("Invalid number entered. Try again.\n");
            } while(n >= msg_count);
    }
    void clear(Table *board){
        for (int i = 0; i < board->csize; i++){
            free(board->ks[i].info->element);
            free(board->ks[i].info);
            free(board->ks[i].key);
        }
        free(board->ks);
    }



    int fileadd(Table *board, char* key , char* element){
        if (board->csize == board->msize) {
            printf("Error: Overflow. Try Reorganization.\n");
            return 1;
        }
        for (int i = 0 ; i<board->csize ; i++){
            if (strcmp(key ,board->ks[i].key) == 0){
                printf("Some elements with this keys is already in the table\n");
                return 1;
            }
        }
        board->ks = realloc(board->ks, sizeof(KeySpace) * (board->csize + 1));
        board->ks[board->csize].info = malloc(sizeof(Item));
        board->ks[board->csize].busy = 1;
        board->ks[board->csize].key = key;
        board->ks[board->csize].info->element = element;
        board->csize += 1;
        return 0;
    }
    int input(Table *board) {
        FILE *start;
        printf("Input name of file:\n");
        const char *st = getStr();
        start = fopen(st, "r");
        if (start == NULL) {
            printf("No file!.\n");
            free(st);
            return 1;
        }
        while (!feof(start)){
            int overflowflag = 1 ;
            char buf[1] = {0}, *res , *msg;
            int f = 1, str_len = 0 , msg_len = 0;
            res = malloc(sizeof(char));
            msg = malloc(sizeof(char));
            while(f == 1){
                int buflen = 0;
                fscanf(start, "%1[^\n]%n", buf, &buflen);
                if (buflen == 1){
                    res = realloc(res, sizeof(char) * (str_len + 2));
                    res[str_len] = buf[0];
                    str_len += 1;
                }else{
                    f = 0;
                }
            }
            f = 1 ;
            fscanf(start, "%*1[\n]");
            while(f == 1){
                int buflen = 0;
                fscanf(start, "%1[^\n]%n", buf, &buflen);
                if (buflen == 1) {
                    msg = realloc(msg, sizeof(char) * (msg_len + 2));
                    msg[msg_len] = buf[0];
                    msg_len += 1;
                }else{
                    f = 0;
                }
            }
            if (str_len == 0){
                free(res);
                fscanf(start, "%*1[\n]");
            }
            if (msg_len == 0){
                free(msg);
                fscanf(start, "%*1[\n]");
            }
            if (msg_len !=0 && str_len !=0){
                res[str_len] = '\0';
                msg[msg_len] = '\0';
                overflowflag = fileadd(board, res, msg);
                fscanf(start, "%*1[\n]");
            }
            if (overflowflag){
                free(st);
                return 1;
            }
        }
        fclose(start);
        free(start);
        free(st);
        return 1;
    }


    int main() {
    Table board = {NULL, 3, 0};
    int num_func;
    int (*fptr[])(Table *) = {NULL, Add, Find, Delete, DeleteRange,CleanShow, DirtyShow, Reorg ,input };
    while(num_func = menu()){
        if (!fptr[num_func](&board)){
            break;
        }
    }
    clear(&board);
    return 0;
}
