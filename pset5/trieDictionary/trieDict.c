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


#define CHILDREN_SIZE (27)

// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a') + 1


// trie node
typedef struct _TrieNode
{
	struct _TrieNode *children[CHILDREN_SIZE];

	// isLeaf is true if the node represents
	// end of a word
	bool isWord;
} TrieNode;

int actualDictionarySize = 0;



TrieNode* root;

TrieNode *getNode();
int getIndex(char c);


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
	// TODO

	/*char lowercase[LENGTH + 1];
	int i = 0;
	while (word[i] != '\0') {
		lowercase[i] = tolower(word[i]);
		i++;
	}
	lowercase[i] = '\0';
	node *traversal = hashtable[hash(lowercase)];
	while (traversal != NULL) {
		// printf("word = %s\n", traversal -> word);
		if (strcmp(lowercase, traversal -> word) == 0) return true;
		traversal = traversal -> next;
	}*/



	TrieNode *pCrawl = root;

	int level;
	int length = strlen(word);
	int index;
	bool isWord = false;

	for (level = 0; level < length; level++)
	{
		index = getIndex(tolower(word[level]));
		if (!pCrawl->children[index])
			return false;
		pCrawl = pCrawl->children[index];
		isWord = pCrawl -> isWord;

	}
	return isWord;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
	// TODO

	void insert(const char *key);

	FILE* fp = fopen(dictionary, "r");
	if (fp == NULL)
	{
		printf("Could not open %s.\n", dictionary);
		unload();
		return 1;
	}

	root = getNode();
	char wordToInsert[LENGTH + 1];


	/**
	*Can be made more effiecient by loading a trie with each read in letter
	*/

	int index = 0;
	for (int c = fgetc(fp); c != EOF; c = fgetc(fp)) {
		if (c == '\n' || c == EOF) {
			// printf("loading word %s\n", wordToInsert);
			wordToInsert[index] = '\0';
			insert(wordToInsert);
			actualDictionarySize++;
			index = 0;
		}
		else {
			wordToInsert[index] = c;
			index++;
		}
	}
	return true;
}


void insert(const char *key)
{

	int level;
	int length = strlen(key);
	int index;

	TrieNode *pCrawl = root;

	for (level = 0; level < length; level++)
	{
		index = getIndex(key[level]);
		if (!pCrawl->children[index])
			pCrawl->children[index] = getNode();

		pCrawl = pCrawl->children[index];
	}

	// mark last node as word
	pCrawl->isWord = true;
}

// Returns new trie node (initialized to NULLs)
TrieNode *getNode()
{
	TrieNode *pNode = NULL;

	pNode = (TrieNode *)malloc(sizeof(TrieNode));

	if (pNode)
	{
		int i;

		pNode->isWord = false;

		for (i = 0; i < CHILDREN_SIZE; i++)
			pNode->children[i] = NULL;
	}

	return pNode;
}



int getIndex(char c) {
	if (c == '\'')
	{
		return 0;
	}

	else
	{
		return CHAR_TO_INDEX(c);
	}

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

	void free_all(TrieNode* curs);


	free_all(root);

	//stupid type of unloading - try with hash unloading later



	return true;
}


void free_all(TrieNode* curs)
{
    int i;
    if(!curs) return;

    // recursive case (go to end of trie)
    for (i = 0; i < 27; i++)
       free_all(curs->children[i]);

    free(curs);
}


