#include <cs50.h>
#include <stdio.h>

int main(void)
{
    const int DAVID = 2;
    int points = get_int("How many points did you lose? ");

    if (points < DAVID)
    {
        printf("You lost fewer points than David.\n");
    }
    else if (points > DAVID)
    {
        printf("You lost more points than David.\n");
    }
    else
    {
        printf("You lost the same point as David.\n");
    }
}