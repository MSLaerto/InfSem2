#ifndef LIST_H
#define LIST_H
typedef struct Elements {
    int type;
    char *arr;
    struct Elements *next;
} Elements;
typedef struct Answer{
    int m_len;
    Elements *head;
} Answer;
Answer *create_stack(int l);
void push(Answer **ans, char* data, int a);
void pop(Answer **ans, char **arr1, int *type1);
char *string(char a);
void clear(Answer **ans);
void output(Answer *ans);
#endif
