#ifndef TABLE_H
#define TABLE_H
int init(Table *board);
int input(Table *board);
int count_rel(Table *board, unsigned int key);
unsigned int hash1(unsigned int key, Table *board);
unsigned int hash2(unsigned int key, Table *board);
int Add(Table *board, unsigned int key, unsigned int el);
Table Find(Table *board, unsigned int key);
int Delete(Table *board, unsigned int key);
int CleanShow(Table *board);
int DirtyShow(Table *board);
int Reorg(Table *board);
void clear(Table *board);
#endif
