/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>

#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>



typedef struct node{
    
    unsigned char word[LENGTH + 1];
    struct node* next;
    
} node;

unsigned long
hash(unsigned char *str);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // TODO
    
    FILE *fp;
    fp = fopen(dictionary, "r");
    
    node hashtable[100000];    
    if (fp == NULL) {
        printf("Couldn't allocate memory for file\n");
        return 1;
    }
    int hashtable_size = 10000;
    

    char buffer[LENGTH + 1];

    while (fgets(buffer, sizeof(buffer), fp)) {
        node* new_node = malloc(sizeof(node));
        sscanf(buffer, "%s", new_node -> word);
        unsigned long hash_code = hash(new_node -> word);
        int bucket_no = hash_code % hashtable_size;
        hashtable[bucket_no] = *new_node;
        // hashtable[]
        //printf("%s", buffer);
    }
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}


// struct node 



unsigned long
hash(unsigned char *str)
    {
        unsigned long hash = 5381;
        int c;

        while (c = *str++) {
            hash = ((hash << 5) + hash) + c; 
        }

        return hash;
    }
