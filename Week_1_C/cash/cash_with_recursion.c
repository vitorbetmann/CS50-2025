#include <cs50.h>
#include <stdio.h>

int coins_amount(int change, int values[], int index);

int main(void)
{
    int change;
    do
    {
        change = get_int("Change owed: ");
    }
    while (change <= 0);

    int values[] = {25, 10, 5, 1};
    printf("%i\n", coins_amount(change, values, 0));
}

int coins_amount(int change, int values[], int index)
{
    if (change == 0)
    {
        return 0;
    }

    int max_coin_amount = change / values[index];
    int remainder = change % values[index];
    return max_coin_amount + coins_amount(remainder, values, ++index);
}
