#include <stdio.h>
#include "hashFunc.h"

table* tableInit() {
    table* hashTable = NULL;
    hashTable = mallocWithoutNull(sizeof(hashTable) * 1);

    hashTable->len = 0;
    hashTable->buckets = NULL;

    return hashTable;
}

void addWord(table* hashTable, char* message) {
    int len = 0;
    unsigned int* hash = getHash(messageComplementaion(message, &len), len);

    for (int i = 0; i < hashTable->len; i++) {
        if (hashEquality(hashTable->buckets[i].key, hash) == 1) {
            hashTable->buckets[i].messages = reallocWithoutNull(hashTable->buckets[i].messages, sizeof(char*) * (++hashTable->buckets[i].len));
            hashTable->buckets[i].messages[hashTable->buckets[i].len - 1] = message;
            return;
        }
    }

    if (hashTable->len == 0) {
        hashTable->buckets = mallocWithoutNull(sizeof(bucket) * (hashTable->len + 1));
    } else {
        hashTable->buckets = reallocWithoutNull(hashTable->buckets, sizeof(bucket) * (hashTable->len + 1));
    }

    hashTable->buckets[hashTable->len].key = hash;
    hashTable->buckets[hashTable->len].len = 1;
    hashTable->buckets[hashTable->len].messages = mallocWithoutNull(sizeof(char*) * 1);
    hashTable->buckets[hashTable->len].messages[0] = message;
    hashTable->len++;
}

void printTable(table* hashTable) {

    printf("\n\tCurrent hash table:");
    for(int i = 0; i < hashTable->len; i++) {
        printf("\n\t\t%d-th bucket | key = %u-%u-%u-%u", i+1, hashTable->buckets[i].key[0], 
                hashTable->buckets[i].key[1], hashTable->buckets[i].key[2], hashTable->buckets[i].key[3]);

        for(int j = 0; j < hashTable->buckets[i].len; j++) {
            printf("\n\t\t\t%s", hashTable->buckets[i].messages[j]);
        }
    }
    printf("\n");

}

void freeTable(table* hashTable) {
    for(int i = 0; i < hashTable->len; i++) {
        for(int j = 0; j < hashTable->buckets[i].len; j++) {
            free(hashTable->buckets[i].messages[j]);
            hashTable->buckets[i].messages[j] = NULL;
        }
        free(hashTable->buckets[i].messages);
        hashTable->buckets[i].messages = NULL;
        free(hashTable->buckets[i].key);
        hashTable->buckets[i].key = NULL;
    }
    free(hashTable->buckets);
    hashTable->buckets = NULL;

    free(hashTable);
}
