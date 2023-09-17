#ifndef TYPE_H
#define TYPE_H
#define N 11
typedef struct Item{
    unsigned int element;
}Item;
typedef struct KeySpace{
    Item *info;
    unsigned int key;
    int busy;
    int release;

}KeySpace;
typedef struct Table{
    KeySpace *ks;
    int msize;
}Table;
#endif
