#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string get_brand(long card_num);
bool is_valid(long card_num);
int card_len(long card_num);
int starting_digits(long card_num);

int main(void)
{
    long card_num = get_long("Number: ");
    printf("%s\n", get_brand(card_num));
}

string get_brand(long card_num)
{
    if (is_valid(card_num))
    {
        int start = starting_digits(card_num);
        switch (card_len(card_num))
        {
            case 15:
                if ((start == 34 || start == 37))
                {
                    return "AMEX";
                }
                break;

            case 16:
                if (51 <= start && start <= 55)
                {
                    return "MASTERCARD";
                }
                if (start / 10 == 4)
                {
                    return "VISA";
                }
                break;

            case 13:
                if (start / 10 == 4)
                {
                    return "VISA";
                }
                break;
        }
    }
    return "INVALID";
}

bool is_valid(long card_num)
{
    int singles_sum = 0;
    int doubles_sum = 0;

    int i = 0;
    while (card_num != 0)
    {
        if (!(i % 2 == 0))
        {
            int temp = 2 * (card_num % 10);
            if (temp >= 10)
            {
                temp = temp % 10 + temp / 10;
            }
            doubles_sum += temp;
        }
        else
        {
            singles_sum += card_num % 10;
        }
        ++i;
        card_num /= 10;
    }
    return ((doubles_sum + singles_sum) % 10) == 0;
}

int card_len(long card_num)
{
    int length = 0;
    while (card_num != 0)
    {
        length++;
        card_num /= 10;
    }
    return length;
}

int starting_digits(long card_num)
{
    int starting_digits = card_num / (pow(10, card_len(card_num) - 2));
    return starting_digits;
}
