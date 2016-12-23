#include <stdio.h>
#include <stdlib.h>

void main()
{
	int *p, *q;

	p = (int *)malloc(sizeof(int));
	q = (int *)malloc(sizeof(int));
	*p = 10;
	*q = 20;
	*p = *q;
	printf("%d\n", *p);
}