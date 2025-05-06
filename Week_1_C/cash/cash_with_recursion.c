#include <cs50.h>
#include <stdio.h>

// prototypes
int get_change();
int coin_amount(int change, int index);

// variables
int coins[] = {25, 10, 5, 1};

int main(void)
{
    // prompt user for change amount
    int change = get_change();
    // calculate minimum amount of coins to pay change
    int amount = coin_amount(change, 0);
    // print amount
    printf("%d\n", amount);
}

int get_change()
{
    int change = -1; // set it to -1 because if just declared, it contains garbage value
    do
    {
        change = get_int("Change owed: ");
    }
    while (change < 0);
    return change;
}

int coin_amount(int change, int index){
    if (change == 0){
        return 0;
    }

    int value = coins[index];
    int amount = change / value;
    change = change % value;
    return amount + coin_amount(change, ++index);
 }
