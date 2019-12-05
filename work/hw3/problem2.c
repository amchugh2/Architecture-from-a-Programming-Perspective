#include <stdio.h>
#include <stdlib.h>

struct problem1{
	long x;
	char c1, c2;
	int i;
	short s;
};

int main(){
	struct problem1 abby;
	printf("long: %d\n", sizeof(abby.x));
	printf("char: %d\n", sizeof(abby.c1));
	printf("char2: %d\n", sizeof(abby.c2));
	printf("int: %d\n", sizeof(abby.i));
	printf("short: %d\n", sizeof(abby.s));
	printf("%d\n", sizeof(abby));
}
