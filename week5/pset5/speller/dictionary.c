// Implements a dictionary's functionality
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

//global variable counts the word in dict
int num_words = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // search
    /*steps
    find the hash number, search the linked list*/
    int bucket = hash(word);
    for (node *tmp = table[bucket]; tmp != NULL; tmp = tmp->next)
    {
        char *c_word = tmp->word;
        if (strcasecmp(c_word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //open the file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    //prepare
    int index = 0;
    char word[LENGTH + 1];

    //add the dict to the hash table
    /*we will do it in a while loop
    in three steps:
    get the word;
    get its hash;
    add it to the hash table
    */
    char c;
    while (fread(&c, sizeof(char), 1, dict))
    {
        if (c != '\n')
        {
            word[index] = c;
            index ++;
        }
        else if (c == '\n')
        {
            word[index] = '\0';
            int bucket = hash(word);
            node *tmp = malloc(sizeof(node));

            for (int i = 0; i <= index; i++)
            {
                tmp->word[i] = word[i];
            }
            tmp->next = table[bucket];
            table[bucket] = tmp;
            num_words += 1;
            index = 0;
        }
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return num_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    //for each linked list in the table, free them
    for (int i = 0; i < N; i++)
    {
        node *clean = table[i];
        while (clean != NULL)
        {
            node *tmp = clean->next;
            free(clean);
            clean = tmp;
        }
    }
    return true;
}
