#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "parity.h"

#define BUF_LEN 1024

int main() {
    char buffer[BUF_LEN];

    printf("Enter string of bytes in two-hexadecimal digits separated by spaces. ");
    printf("Do not use the 0x prefix. An example is 1A 2F 03 4C: ");

    fgets(buffer, BUF_LEN, stdin);

    printf("\n\n");

    uint8_t parity = calculateParity(buffer);

    printf("Parity in Decimal: %d, hexadecimal: %X\n", parity, parity);

    return 0;
}
