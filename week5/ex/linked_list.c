#include <stdio.h>
#include <stdlib.h>

typedef struct node//to tell the compiler what is node
{
    int number;
    struct node *next;
}
node;

int main(void)
{
    node *list = NULL;//convenient for bool test

    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        free(list);
        return 1;
    }
    n->number = 1;//the same as (*n).number = 1;
    n->next = NULL;
    list = n;

    //add a new node
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free(list);
        return 1;
    }
    n->number = 2;
    n->next = NULL;
    list->next = n;

    //add third node
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        //attention for the order of free
        free(list->next);
        free(list);
        return 1;
    }
    n->number = 3;
    n->next = NULL;
    list->next->next = n;

    //print the numbers
    //the essence of for loop:start, check, update
    for (node *tmp = list; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->number);
    }

    //free list
    //free order: 1 2 3
    while (list != NULL)
    {
        node *tmp = list->next;
        free(list);
        list = tmp;
    }
}