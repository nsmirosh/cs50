// C implementation of search and insert operations
// on Trie
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)

// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

// trie node
typedef struct _TrieNode
{
	struct _TrieNode *children[ALPHABET_SIZE];

	// isLeaf is true if the node represents
	// end of a word
	bool isWord;
} TrieNode;

TrieNode *getNode(void);
void insert(TrieNode *root, const char *key);
bool isMember(TrieNode *root, const char *key);


int main() {

	TrieNode* root = getNode();
	insert(root, "stuff");
	insert(root, "balss");

	if (isMember(root, "stuff")) {
		printf("stuff is member\n");
	}

	if (isMember(root, "balss")) {
		printf("balss is member\n");
	}

	if (!isMember(root, "dickiiis")) {
		printf("dickiiis is not a member\n");
	}

}


// Returns new trie node (initialized to NULLs)
TrieNode *getNode(void)
{
	TrieNode *pNode = NULL;

	pNode = (TrieNode *)malloc(sizeof(TrieNode));

	if (pNode)
	{
		int i;

		pNode->isWord = false;

		for (i = 0; i < ALPHABET_SIZE; i++)
			pNode->children[i] = NULL;
	}

	return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(TrieNode *root, const char *key)
{

	TrieNode *getNode(void);
	int level;
	int length = strlen(key);
	int index;

	TrieNode *pCrawl = root;

	for (level = 0; level < length; level++)
	{
		index = CHAR_TO_INDEX(key[level]);
		if (!pCrawl->children[index])
			pCrawl->children[index] = getNode();

		pCrawl = pCrawl->children[index];
	}

	// mark last node as word
	pCrawl->isWord = true;
}


bool isMember(TrieNode *root, const char *key) {

	TrieNode *pCrawl = root;
	int level;
	int length = strlen(key);
	int index;
	bool isMember = false;

	for (level = 0; level < length; level++)
	{
		index = CHAR_TO_INDEX(key[level]);
		if (!pCrawl->children[index])
			return false;
		pCrawl = pCrawl->children[index];
		isMember = pCrawl -> isWord;

	}
	return isMember;

}
