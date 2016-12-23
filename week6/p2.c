#include <stdio.h>
#include <stdlib.h>

void main()
{
	int *p, *q;

	p = (int *)malloc(sizeof(int));
	q = p;
	*p = 10;
	printf("%d\n", *q);
	*q = 20;
	printf("%d\n", *q);
}