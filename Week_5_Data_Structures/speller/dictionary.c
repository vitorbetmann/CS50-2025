// Implements a dictionary's functionality

#define _GNU_SOURCE
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 765432;
unsigned int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    for (node *ptr = table[hash(word)]; ptr != NULL; ptr = ptr->next)
    {
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //return toupper(word[0]) - 'A';
    unsigned int hash = 0;
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        hash += tolower(word[i]) * ('A' + i) * i;
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }

    char buffer[LENGTH + 1];
    node *temp;
    while (fscanf(source, "%s", buffer) != EOF)
    {
        temp = malloc(sizeof(node));
        if (temp == NULL)
        {
            return false;
        }
        strcpy(temp->word, buffer);
        unsigned int index = hash(temp->word);
        temp->next = table[index];
        table[index] = temp;
        word_count++;
    }

    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        for (node *next; table[i] != NULL; table[i] = next)
        {
            next = table[i]->next;
            free(table[i]);
        }
    }
    return true;
}
