#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //get x(the way to comment)
    long x = get_long("X: ");
    long y = get_long("Y: ");
    printf("%li\n",x+y);
}