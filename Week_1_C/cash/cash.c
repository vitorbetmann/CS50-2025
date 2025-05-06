#include <cs50.h>
#include <stdio.h>

// prototypes
int get_change();
int coin_amount(int change);

int main(void)
{
    // prompt user for change amount
    int change = get_change();
    // calculate minimum amount of coins to pay change
    int amount = coin_amount(change);
    // print amount
    printf("%d\n", amount);
}

int get_change()
{
    int change = -1; // set to -1 because if just declared, it contains garbage value
    do
    {
        change = get_int("Change owed: ");
    }
    while (change < 0);
    return change;
}

int coin_amount(int change){
    int amount = 0;

    // get amount of 25 cent coins
    amount += change / 25;
    change %= 25; // get remainder of change after paying the max amount possible with that value
    // get amount of 10 cent coins
    amount += change / 10;
    change %= 10;
    // get amount of 5 cent coins
    amount += change / 5;
    change %= 5;
    amount += change; // add the remainder to amount because anything left has to be all 1 cent coins

    return amount;
}

