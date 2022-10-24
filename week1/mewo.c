#include <stdio.h>

void mewo(int n);

int main(void)
{
    mewo(3);
}

void mewo(int n)
{
    for (int i =0;i<n;i++)
    {
        printf("mewo\n");
    }
}