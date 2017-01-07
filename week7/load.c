#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <error.h>

// types
typedef char BYTE;



bool load(FILE* file, BYTE** content, size_t* length)
{
	// TODO
	char *code;
	size_t n = 0;
	int c;

	if (file == NULL)
		return NULL; //could not open file

	code = malloc(1024);

	while ((c = fgetc(file)) != EOF)
	{
		code[n++] = (char) c;
	}

	// don't forget to terminate with the null character
	code[n] = '\0';
	*content = code;
	*length = n;
	return true;
}

int main ()
{

	FILE* fp = fopen("text.txt", "r");

	char* content;
	size_t length;
	load(fp, &content, &length);

	printf("length = %li\n", length);
	printf("content = %s\n", content);


	return (0);
}
