/* Program for Tutorial #2 Q2 */
#include <stdio.h>

void swap(int *, int *);

int main(void) {
	int x, y;

	printf("Enter x and y: ");
	scanf("%d %d", &x, &y);

	swap(&x, &y);

	printf("x = %d; y= %d\n",x, y);

	return 0;
}

// This function swaps the values of *a and *b
void swap(int *a, int *b) {
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

