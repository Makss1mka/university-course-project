#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "tools.h"

const uint32_t offset[64] = {
        7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
        5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
        4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
        6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,
    };

const uint32_t consts[64] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
};

char* messageComplementaion(char* message, int* len) {
    *len = strlen(message);

    char* compMes = mallocWithoutNull(sizeof(char) * (*len + (8 - (*len) % 8)));

    for (int i = 0; i < *len; i++) compMes[i] = message[i];

    if ((*len) % 8 != 7) {
        compMes[*len] = (char)64;

        for (int i = *len + 1; i < *len + (8 - (*len) % 8); i++) compMes[i] = (char)0;

        *len = *len + (8 - (*len) % 8);
    }

    compMes[*len] = (char)(strlen(message));

    return compMes;
}

unsigned int leftRotate(unsigned int n, unsigned int b) {
    return ((n << b) | (n >> (32 - b))) & 0xffffffff;
}

unsigned int* getHash(char* message, int len) {
    unsigned int a0 = 0x67452301;
    unsigned int b0 = 0xefcdab89;
    unsigned int c0 = 0x98badcfe;
    unsigned int d0 = 0x10325476;

    unsigned int* result = mallocWithoutNull(sizeof(unsigned int) * 4);

    char* compMes = messageComplementaion(message, &len);

    for (int i = 0; i < len; i += 8) {
        char* chunk = mallocWithoutNull(sizeof(char) * 8);

        for(int mesInd = i, chInd = 0; mesInd < i + 8; mesInd++, chInd++) chunk[chInd] = compMes[mesInd];

        uint32_t a = a0, b = b0, c = c0, d = d0, g, f, d_temp; 

        for(int j = 0; j < 64; j++) {
            if (j < 16) {
                f = (b & c) | ((~b) & d);
                g = j;
            } else if (j < 32) {
                f = (d & b) | ((~d) & c);
                g = (5*j + 1) % 16;
            } else if (j < 48) {
                f = b ^ c ^ d;
                g = (3*j + 5) % 16;
            } else {
                f = c ^ (b | (~d));
                g = (7*j) % 16;
            }

            d_temp = d;
            d = c;
            c = b;
            b = b + leftRotate((a + f + consts[j] + 
                + (g < 8) ? chunk[g % 8] % 32 : chunk[g % 8] >> 4) 
                & 0xffffffff, offset[j]) ;
            a = d_temp;
        }

        a0 = (a + a0) & 0xFFFFFFFF;
        b0 = (b + b0) & 0xFFFFFFFF;
        c0 = (c + c0) & 0xFFFFFFFF;
        d0 = (d + d0) & 0xFFFFFFFF;
    }

    result[0] = a0;
    result[1] = b0;
    result[2] = c0;
    result[3] = d0;

    return result;
}

int hashEquality(unsigned int* hash_1, unsigned int* hash_2) {

    for(int i = 0; i < 4; i++) {
        if (hash_1[i] != hash_2[i]) return 0;
    }

    return 1;
}
