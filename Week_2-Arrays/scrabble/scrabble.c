#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int calculate_points(string word);

int POINTS[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    string p1_word = get_string("Player 1: ");
    string p2_word = get_string("Player 2: ");

    int p1_points = calculate_points(p1_word);
    int p2_points = calculate_points(p2_word);

    if (p1_points > p2_points)
    {
        printf("Player 1 wins!\n");
    }
    else if (p1_points < p2_points)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int calculate_points(string word)
{
    int result = 0;
    int i = 0;
    while (word[i] != '\0')
    {
        char letter = tolower(word[i]);
        i++;
        if (letter < 'a' || letter > 'z')
        {
            continue;
        }
        result += POINTS[(int) letter - (int) 'a'];
    }
    return result;
}
