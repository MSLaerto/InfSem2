#ifndef TRANSLATE_H
#define TRANSLATE_H
typedef struct Elements {
    int type;
    char *arr;
} Elements;
typedef struct Answer{
    int len;
    Elements *formula;
} Answer;
void translate(char *line, Answer **ans);
#endif
