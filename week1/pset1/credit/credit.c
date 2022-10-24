#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number = 0;
    do
    {
        number = get_long("Number: ");
    }
    while (number<1);

    //get its digits
    long digits = 1000000000000;
    for (long i=1000000000000;i<=1000000000000000;i=i*10)
    {
        if (number/i<10)
        {
            digits = i;
            break;
        }
    }


    //luhu's Algorithm
    int a = 0;
    int b = 0;
    for (long j=10;j<=digits;j=j*100)
    {
        int c = 0;
        c = 2 * ((number / j) % 10);
        a = a+(c/10)+(c%10);
    }
    for (long k=1;k<=digits;k=k*100)
    {
        int d = 0;
        d = (number / k) % 10;
        b = b + d;
    }
    int e = a + b;

    //heads
    int head_1 = number / digits;
    int head_2 = number / (digits/10);

    //test
    if (head_1 == 4)
    {
        if (e%10 == 0 && digits == 1000000000000)
        {
            printf("VISA\n");
        }
        else if (e%10 == 0 && digits == 1000000000000000)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (head_2 == 51 || head_2 == 52 || head_2 == 53 || head_2 == 54 || head_2 == 55)
    {
        if (e%10 == 0 && digits == 1000000000000000)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (head_2 == 34 || head_2 == 37)
    {
        if (e%10 == 0 && digits == 100000000000000)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}