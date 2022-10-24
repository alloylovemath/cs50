#include <stdio.h>

int main(void)
{
    int numbers[] = {2, 4, 6, 8, 10};

    printf("%p\n", numbers);
    printf("%i\n", *(numbers + 1));
    printf("%i\n", *(numbers + 2));
}