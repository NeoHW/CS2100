#include <stdio.h>

typedef unsigned char byte_t;
void printByte(byte_t);

int main(void) {
	byte_t a, b;
     a = 5;  // 00000101
     b = 22; // 00010110
     printf("a = "); printByte(a); printf("\n");
     printf("b = "); printByte(b); printf("\n");
     printf("a|b = "); printByte(a|b); printf("\n");
     printf("a&b = "); printByte(a&b); printf("\n");
     printf("a^b = "); printByte(a^b); printf("\n"); // XOR
     printf("~a = "); printByte(~a); printf("\n"); // 1's complement of a
     printf("~b = "); printByte(~b); printf("\n"); // 1's complement of b
     printf("a<<2 = "); printByte(a<<2); printf("\n");
     printf("b<<2 = "); printByte(b<<2); printf("\n");
     return 0;
}

void printByte(byte_t x) {
	printf("%c%c%c%c%c%c%c%c",
		(x & 0x80 ? '1' : '0'), // 0x80 is 10000000 in binary, isolating MSB
		(x & 0x40 ? '1' : '0'), // 0x40 is 01000000 in binary, isolating 2nd SB
		(x & 0x20 ? '1' : '0'), // 0x20 is 00100000 in binary, isolating 3rd SB
		(x & 0x10 ? '1' : '0'),
		(x & 0x08 ? '1' : '0'),
		(x & 0x04 ? '1' : '0'),
		(x & 0x02 ? '1' : '0'),
		(x & 0x01 ? '1' : '0'));
}