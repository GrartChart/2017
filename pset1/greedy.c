#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)

{
    
    float change;
    int quarters = 0;
    int dimes = 0;
    int nickels = 0;
    int remaining_coins = 0;

    do
    {
        printf("How much change is owed to the customer? ");
        change = GetFloat();
    }
    while (change <= 0.00);

    int cents = round(change * 100);
    /* converts dollars to cents, float to an int */
    int count = 0;
    /* creates a variable called count set to 0 */
    
    quarters = cents / 25;
    /* gets the number of quarters */
    remaining_coins = cents % 25;
    /* remainder of modelo goes into dimes */
    
    dimes = remaining_coins / 10;
    remaining_coins = remaining_coins % 10;
    
    nickels = remaining_coins / 5;
    remaining_coins = remaining_coins % 5;
    
    count = quarters + dimes + nickels + remaining_coins;
    
    {
        printf("%i\n", count);
    }
    
}



    
    