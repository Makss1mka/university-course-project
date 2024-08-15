#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// MEMORY
void* mallocWithoutNull(unsigned size) {
	void* returnArr = NULL;
	char count = 0;

	while (1) {
		returnArr = malloc(size);
		if (returnArr != NULL) return returnArr;

		count++;
		if (count > 50) {
			printf("\n\n\tMalloc cycle error");
			exit(-1);
		}
	}
}

void* reallocWithoutNull(void* inputPtr, unsigned newSize) {
	char count = 0;

	while (1) {
		inputPtr = realloc(inputPtr, newSize);
		if (inputPtr != NULL) return inputPtr;

		count++;
		if (count > 50) {
			printf("\n\n\tRealloc cycle error");
			exit(-1);
		}
	}
	return NULL;
}

void* callocWithoutNull(unsigned num, unsigned size) {
	void* returnArr = NULL;
	char count = 0;

	while (1) {
		returnArr = calloc(num, size);
		if (returnArr != NULL) return returnArr;

		count++;
		if (count > 50) {
			printf("\n\n\tMalloc cycle error");
			exit(-1);
		}
	}
}

// NUMBER SCANS
int intScanWithLimitCheck(int min, int max) {
	int num;

	while (scanf_s("%d", &num) == 0 || getchar() != '\n'
		|| num < min || num > max) {
		printf("\n\tIncorrect input, make another input - ");
		rewind(stdin);
	}

	return num;
}

// STRINGS
char* inputString() {
	printf("\n\tInput the string - ");
    char* buffer = mallocWithoutNull(150);
    buffer = fgets(buffer, 150, stdin);
    rewind(stdin);
    buffer[strlen(buffer) - 1] = '\0';

	return buffer;
}
