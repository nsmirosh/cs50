#include <stdio.h>
#include <stdlib.h>
int main()
{
	int **p;
	int *q;

	p = (int **)malloc(sizeof(int *));
	*p = (int *)malloc(sizeof(int));
	**p = 12;
	q = *p;
	printf("%d\n", *q);
	free(q);
	free(p);
}