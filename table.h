#include <stdio.h>

typedef struct Bucket {

    unsigned int* key;
    char** messages;
    int len;

} bucket;

typedef struct Table {

    bucket* buckets;
    int len;

} table;

table* tableInit();
void addWord(table* hashTable, char* message);
void printTable(table* hashTable);
void freeTable(table* hashTable);
