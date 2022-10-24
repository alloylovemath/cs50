#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    char *s = get_string("t: ");
    char *t = get_string("s: ");

    if (s == t)
    {
        printf("Same address\n");
    }
    else
    {
        printf("Different address\n");
    }

    if (strcmp(s, t) == 0)
    {
        printf("Same value\n");
    }
    else
    {
        printf("Different value\n");
    }
}