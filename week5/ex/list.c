#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    //use space in stack & can't resize
    //int list[3];

    //use space in heap & can be resize
    int *list = malloc(3 * sizeof(int));

    list[0] = 1;
    list[1] = 2;//the same as *(list + 1) = 2;
    list[2] = 3;

    //add a new item in the list
    //int *tmp = malloc(4 * sizeof(int));
    int *tmp = realloc(list, 4 * sizeof(int));
    if (tmp == NULL)
    {
        free(list);
        return 1;
    }

    /*
    for (int i = 0; i < 3; i++)
    {
        tmp[i] = list[i];
    }
    */

    // what you actually free is the address, list is a pointer, but pointer is also a variable
    //however, if you use realloc(), the function will do this for you automatically
    //free(list);

    list = tmp;

    list[3] = 4;

    for (int i = 0; i < 4; i++)
    {
        printf("%i\n", list[i]);
    }

    free(list);// the same as free(tmp); since they are the same
    return 0;
}