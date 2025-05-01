#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_valid_key(string text);
string tocipher(string text, string key);

int main(int argc, string argv[])
{

    if (!(argc == 2))
    {
        printf("Usage: ./substitution key");
        return 1;
    }
    if (strlen(argv[1]) != 26 || !is_valid_key(argv[1]))
    {
        printf("Key mist contain 26 characters.");
        return 1;
    }

    string text = get_string("plaintext: ");
    text = tocipher(text, argv[1]);

    printf("ciphertext: %s\n", text);
    return 0;
}

bool is_valid_key(string text)
{
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (tolower(text[i]) == tolower(text[j]) || !isalpha(text[i]))
            {
                return false;
            }
        }
    }
    return true;
}

string tocipher(string text, string key)
{
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (!isalpha(text[i]))
        {
            continue;
        }
        int index = text[i] % 32 - 1;
        text[i] = isupper(text[i]) ? toupper(key[index]) : tolower(key[index]);
    }

    return text;
}
