#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "parity.h"

// Calculate and return the parity byte 
// for an array of bytes, using ODD parity.
uint8_t findParity(uint8_t *array, uint8_t len) {
    return 0;
}

// (Done for you). 
// Converts a hexadecimal digit into decimal
// nibble = digit to convert, as an ASCII
// character. E.g. '0', 'F', '3', etc.
uint8_t finddec(char nibble) {

    if(nibble >= '0' && nibble <= '9')
        return nibble - '0';

    switch(nibble){
        case 'a':
        case 'A': return 10;
        case 'b':
        case 'B': return 11;
        case 'c':
        case 'C': return 12;
        case 'd': 
        case 'D': return 13;
        case 'e':
        case 'E': return 14;
        case 'f':
        case 'F': return 15;

        default:
            return 0;
    }
}
// Converts a 2-digit hexadecimal number in the form
// of a C string.
// The "byte" parameter must be an array of 3 characters. 
// E.g. If it represents 0x3F, then "byte" contains
// the string "3F".

uint8_t hex2dec(char *byte) {
    // Converts 2-digit hexadecimal number in "byte"
    // into decimal. Complete this function in a 
    // "return" statement. E.g. return bytes[1] + byte[2];
    // No credit if you use >1 line.
    return 0;
}

// Converts a string of hexadecimal numbers into an array of 
// 8-bit values.
// E.g. 3A 4C 10 2B will convert to a 4 element array containing
// 58, 76, 16 and 43, which are the decimal equivalents of
// 3A, 4C, 10 and 2B. The "len" parameter returns the number 
// of bytes converted,in this case 4. 
// You may want to look at the strtok function.

void string2bytes(char *str, uint8_t *bytes, uint8_t *len) {
}

// Receives a string of bytes in hexadecimal, and returns the parity
// byte as an 8-bit value.
// str = String of bytes in hexadecimal separated by spaces
// E.g. "08 1C 4B 1E". Do not use the 0x prefix for the bytes.
uint8_t calculateParity(char *str) {
    return 0;
}
