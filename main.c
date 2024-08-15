#include <stdio.h>
#include "tools.h"
#include "tools.c"
#include "table.h"
#include "table.c"
#include "hashFunc.c"

void menu() {
    int choice;
    
    table* hashTable = tableInit();

    while (1) {
        printf("\n\tMenu:");
        printf("\n\t1) Add string");
        printf("\n\t2) Print current table");
        printf("\n\t3) Clear all buckets");
        printf("\n\t4) End the program");
        printf("\n\tChoouse the action: ");

        switch(choice = intScanWithLimitCheck(1, 4)) {
            case 1:
                addWord(hashTable, inputString());
                break;
            case 2:
                printTable(hashTable);
                break;
            case 3:
                freeTable(hashTable);
                hashTable = tableInit();
                break;
            case 4:
                freeTable(hashTable);
                hashTable = NULL;
			    return;
            default:
                printf("\n\nIncorrect input");
                break;
        }
    }
}

int main() {
    printf("\n------------------------\n");

    menu();

	printf("\n------------------------\n");

    return 1;
}





