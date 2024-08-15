
// MEMORY
void* mallocWithoutNull(unsigned size);
void* reallocWithoutNull(void* inputPtr, unsigned newSize);
void* callocWithoutNull(unsigned num, unsigned size);

// NUMBER SCANS
int intScanWithLimitCheck(int min, int max);

// STRINGS
char* inputString();
