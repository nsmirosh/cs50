#include <stdio.h>
#include <string.h>
#include <stdlib.h>



typedef struct _node {
	char* key;
	struct _node* next;
} node;


int size = 2;
node *hashtable[2];

unsigned int hash(char *str);
node* search(char* key);


int main()
{
	int addNode(char* key);


	/* Initialize the elements of the table */
	for (int i = 0; i < size; i++) hashtable[i] = NULL;

	addNode("stuff");

	addNode("balls");
	addNode("balls1");
	addNode("balls2");
	addNode("balls");




	node* found = search("stuff");
	if (found != NULL) {
		printf("found = %s\n", found -> key);
	}

}



int addNode(char* key) {
	// if the key is already in the hash table
	if (search(key) != NULL) {
		printf("key is already in the table. Exiting \n");
		return 1;
	}
	int position = hash(key);
	printf("position for %s = %i\n", key, position);
	node* newNode;
	if ((newNode = malloc(sizeof(node))) == NULL) return 2;
	newNode -> key = key;
	newNode -> next = hashtable[position];
	hashtable[position] = newNode;

	return 0;

}


node* search(char* key) {
	int position = hash(key);
	node* traversal = hashtable[position];
	while (traversal != NULL) {
		if (strcmp(traversal -> key, key) == 0) return traversal;
		traversal = traversal -> next;
	}
	return NULL;
}





unsigned int hash(char *str)
{
	unsigned int hashval;

	/* we start our hash out at 0 */
	hashval = 0;

	/* for each character, we multiply the old hash by 31 and add the current
	 * character.  Remember that shifting a number left is equivalent to
	 * multiplying it by 2 raised to the number of places shifted.  So we
	 * are in effect multiplying hashval by 32 and then subtracting hashval.
	 * Why do we do this?  Because shifting and subtraction are much more
	 * efficient operations than multiplication.
	 */
	for (; *str != '\0'; str++) hashval = *str + (hashval << 5) - hashval;

	/* we then return the hash value mod the hashtable size so that it will
	 * fit into the necessary range
	 */

	printf("unsigned int hashval = %u\n", hashval);

	return hashval % 2;
}
