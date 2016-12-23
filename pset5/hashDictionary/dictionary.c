/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>

#include <string.h>
#include <stdlib.h>

#include <ctype.h>
#include "dictionary.h"





typedef struct _node {
	char word[LENGTH + 1];
	struct _node *next;
} node;




node *hashtable[HASHTABLE_SIZE];
int actualDictionarySize = 0;

unsigned int hash(const char *str)
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
	return hashval % HASHTABLE_SIZE;
}


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
	// TODO

	char lowercase[LENGTH + 1];
	int i = 0;
	while(word[i] != '\0') {
		lowercase[i] = tolower(word[i]); 
		i++;
	}
	lowercase[i] = '\0';
	node *traversal = hashtable[hash(lowercase)];
	while (traversal != NULL) {
		// printf("word = %s\n", traversal -> word);
		if (strcmp(lowercase, traversal -> word) == 0) return true;
		traversal = traversal -> next;
	}

	return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
	// TODO

	FILE* fp = fopen(dictionary, "r");
	if (fp == NULL)
	{
		printf("Could not open %s.\n", dictionary);
		unload();
		return 1;
	}

	/* Initialize the elements of the table */
	for (int i = 0; i < HASHTABLE_SIZE; i++) {
		hashtable[i] = NULL;
	}

	char wordToInsert[LENGTH + 1];
	int index = 0;
	for (int c = fgetc(fp); c != EOF; c = fgetc(fp)) {
		// char *newString = strdup(buffer);
		if (c == '\n' || c == EOF) {
			node *newNode = NULL;
			wordToInsert[index] = '\0';
			if ((newNode = malloc(sizeof(node))) == NULL) return 2;
			// printf("wordToInsert = %s\n", wordToInsert);

			int position = hash(wordToInsert);
			// printf("hashPosition = %i\n", position);
			// newNode -> word  = wordToInsert;
			strcpy(newNode -> word, wordToInsert);
			newNode -> next = hashtable[position];
			hashtable[position] = newNode;
			actualDictionarySize++;
			index = 0;
		}
		else {
			wordToInsert[index] = c;
			index++;
		}
	}

	/*for (int i = 0; i < DICTIONARY_SIZE; i++) {
		node *traversal = hashtable[i];
		while (traversal != NULL) {
			// printf("word = %s\n", traversal -> word);
			traversal = traversal -> next;
		}
	}*/
	return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
	// TODO
	return actualDictionarySize;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
	// TODO

	/*char wordToInsert[LENGTH + 1];

	for (int c = fgetc(fp); c != EOF; c = fgetc(fp)) {
		// char *newString = strdup(buffer);
		if (c == '\n' || c == EOF) {
			node *newNode = NULL;
			wordToInsert[index] = '\0';
			if ((newNode = malloc(sizeof(node))) == NULL) return 2;
			// printf("wordToInsert = %s\n", wordToInsert);

			int position = hash(wordToInsert);
			// printf("hashPosition = %i\n", position);
			// newNode -> word  = wordToInsert;
			strcpy(newNode -> word, wordToInsert);
			newNode -> next = hashtable[position];
			hashtable[position] = newNode;
			actualDictionarySize++;
			index = 0;
		}
		else {
			wordToInsert[index] = c;
			index++;
		}
	}*/



		//stupid type of unloading - try with hash unloading later


	for(int i = 0; i < HASHTABLE_SIZE; i++) {
		node* cursor = hashtable[i];
		while(cursor != NULL) {
			node *temp = cursor;
			cursor = cursor -> next;
			free(temp);
		}
	}
	return true;
}


