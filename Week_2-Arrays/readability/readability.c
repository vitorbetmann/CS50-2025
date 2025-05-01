#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

float get_index(string text);
float get_letters_average(int letter_count, int word_count);
float get_sentences_average(int sentence_count, int word_count);
int get_letter_count(string text);
int get_word_count(string text);
int get_sentence_count(string text);

int main()
{
    string text = get_string("Text: ");

    int index = (int) round(get_index(text));
    if (index < 1){
        printf("Before Grade 1\n");
    }
    else if (index > 16){
        printf("Grade 16+\n");
    }
    else {
        printf("Grade %i\n", index);
    }

    return 0;
}

float get_index(string text)
{
    int letter_count = get_letter_count(text);
    int word_count = get_word_count(text);
    int sentence_count = get_sentence_count(text);
    float L = get_letters_average(letter_count, word_count);
    float S = get_sentences_average(sentence_count, word_count);
    return 0.0588 * L - 0.296 * S - 15.8;
}

float get_letters_average(int letter_count, int word_count)
{
    // L = average number of letters per 100 words
    return 100.0 * letter_count / word_count;
}

float get_sentences_average(int sentence_count, int word_count)
{
    // S = average number of sentences per 100 words
    return 100.0 * sentence_count / word_count;
}

int get_letter_count(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i])){
            count++;
        }
    }
    return count;
}

int get_word_count(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            count++;
        }
    }
    return ++count;
}

int get_sentence_count(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}
