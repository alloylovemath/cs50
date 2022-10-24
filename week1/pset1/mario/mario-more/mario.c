#include <cs50.h>
#include <stdio.h>

void row(int k, int n);
void pyramids(int n);

int main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n<1 || n>8);
    pyramids(n);
}

void row(int k, int n)
{
    int empty = n-k;

    for (int i=1;i<=empty;i++)
    {
        printf(" ");
    }
    for (int j=1;j<=k;j++)
    {
        printf("#");
    }
    printf("  ");
    for (int j=1;j<=k;j++)
    {
        printf("#");
    }
    printf("\n");
}

void pyramids(int n)
{
    for (int k=1;k<=n;k++)
    {
        row(k,n);
    }
}