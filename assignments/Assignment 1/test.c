#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parity.h"

// Length of buffer to read string
#define BUF_LEN     1024

// Length of buffer to read parity
#define PBUF_LEN    8

// Runs test 1 and returns a test score
// We are just testing the find_parity function
uint16_t test1() {
    uint8_t arr[5][8] = {{135, 172, 155, 20, 17, 82, 21, 44},
                        {15, 72, 115, 31, 175, 143, 2, 23},
                        {17, 21, 44, 54, 123, 34, 82, 123},
                        {117, 232, 43, 87, 122, 182, 34, 112},
                        {23, 144, 65, 112, 89, 188, 72, 115}};
    uint8_t answers[5] = {33, 225, 145, 128, 151};

    uint16_t ctr=0;
    for(int i=0; i<5; i++) {
        if(findParity(arr[i], 8) == answers[i])
            ctr++;
    }

    return ctr;
}

// Runs test 2 and returns a test score.
// We are testing the full string to parity byte
// function.

void test2(char *filename, uint16_t *entries, uint16_t *score) {
    // Open the test file
    FILE *fp = fopen(filename, "r");

    if(!fp) {
        printf("Cannot open test file %s.\n", filename);
        *entries = 0;
        *score = 0;
        return;
    }

    // Read each line
    // Each line consist of a series of 
    // two digit hexadecimal bytes, followed
    // by the odd parity value in decimal
    // between 0 and 255 on the next line.
    // E.g.
    // 1A 2F 30 4C
    // 182
    // 2B 10 35 1A
    // 235
    // etc

    uint16_t ctr = 0, right = 0;

    while(!feof(fp)) {
        char buffer[BUF_LEN];
        char pbuffer[PBUF_LEN];
        uint8_t parity;

        // Read in the string
        fgets(buffer, BUF_LEN, fp);

        if(strlen(buffer) > 2) {
            fgets(pbuffer, PBUF_LEN, fp);
            parity = atoi(pbuffer);

            // Compute the parity
            uint8_t yourParity = calculateParity(buffer);

            printf("Calculated Parity: %d\tCorrect Parity: %d ", 
            yourParity, parity);

            ctr++;
            if(yourParity == parity) {
                printf("MATCHED! Score now is %d of %d\n", ++right, ctr);
            }
            else {
                printf("MISMATCH!\n");
            }
        }

    }

    *entries = ctr;
    *score = right;
}

int main() {

    uint16_t score, count = 5;
    uint16_t t2count, t2score;

    score = test1();
    test2("test.txt", &t2count, &t2score);

    score += t2score;
    count += t2count;

    printf("Score: %d of %d\n", score, count);
    
    return 0;
}

