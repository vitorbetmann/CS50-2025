#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string tocipher(string text, int key);
bool isnumber(string text);
const int ALPHABET_LENGTH = 26;

int main(int argc, string argv[])
{

    // Check if argc == 2
    if (!(argc == 2))
    {
        return 1;
    }
    // Check if argv[1] is a number
    if (!isnumber(argv[1]))
    {
        printf("Usage: ./caesar key");
        return 1;
    }
    // Convert argv[1] into an int
    int key = atoi(argv[1]);
    // Get user input
    string plaintext = get_string("plaintext: ");
    // Copy input
    char *ptr = malloc(strlen(plaintext) + 1);
    string ciphertext = strcpy(ptr, plaintext);
    // Convert input to ciphertext
    ciphertext = tocipher(ciphertext, key);
    // Print to terminal
    printf("ciphertext: %s\n", ciphertext);
    // Free pointer
    free(ptr);

    return 0;
}

bool isnumber(string text)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (!isdigit(text[i]))
        {
            return false;
        }
    }
    return true;
}

string tocipher(string text, int key)
{
    key = key % ALPHABET_LENGTH;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (!isalpha(text[i]))
        {
            continue;
        }

        if (text[i] % 32 + key > ALPHABET_LENGTH)
        {
            text[i] -= ALPHABET_LENGTH;
        }

        text[i] += key;
    }

    return text;
}
