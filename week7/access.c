


#include <unistd.h>

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <error.h>

/**
 * Checks, in order, whether index.php or index.html exists inside of path.
 * Returns path to first match if so, else NULL.
 */
char* indexes(const char* path)
{



	char *result = malloc(strlen(path) + 10);
	strcpy(result, path);
	strcat(result, "/index.php");

	if (access( result, F_OK ) != -1 ) {

		printf("%s exists\n", result);
		return result;
		// file exists
	}
	strcpy(result + strlen(path), "/index.html");

	if (access( result, F_OK ) != -1 ) {
		// file doesn't exist
		printf("%s exists\n", result);
		return result;
	}

	// TODO
	printf("returning NULL\n");

	return NULL;
}


int main ()
{

	indexes("/home/nick/coding/cs50/week7/someDir");
	indexes("/home/nick/coding/cs50/week7");
	indexes("/home/nick/coding/cs50");




	return (0);
}





