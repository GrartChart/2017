#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)

{
int time;
int water_used;
int bottles;

    {
        printf("minutes: ");
        time = GetInt();
    }

    water_used = time * 192;
    bottles = water_used / 16;
    
    {
        printf("bottles: %i \n", bottles);
    }
}