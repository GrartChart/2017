#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    
    do
    {
            printf("Between 3 and 23, how high would you like Mario's pyramid to be? ");
            height = GetInt();
    }
    
    while (height < 0 || height > 23);
    
    for (int rows = 0; rows < height; rows++)
    {
            for (int spaces = 0; spaces <= height - (rows + 2); spaces++)
            {
                printf(" ");
            }
            for (int hashtags = 0; hashtags <= (rows + 1); hashtags++)
            {
                printf("#");
            }
            printf("\n");
    }
}
Contact GitHub API Training Shop Blog About
© 2017 GitHub, Inc. Terms Privacy Security Status Help
