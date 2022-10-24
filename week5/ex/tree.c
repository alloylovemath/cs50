#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>//use bool in c

//represent a node
typedef struct node
{
    int number;
    struct node *left;
    struct node *right;
}
node;

void free_tree(node *root);
void print_tree(node *root);

int main(void)
{
    //the root
    node *tree = NULL;

    //add one node to the tree
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return 1;
    }
    n->number = 2;
    n->left = NULL;
    n->left = NULL;
    tree = n;

    //add another node to the tree
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free_tree(tree);
        return 1;
    }
    n->number = 1;
    n->left = NULL;
    n->right = NULL;
    //sin 1 < 2, we add it to the left side of the root
    tree->left = n;

    //add third node to the tree
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free_tree(tree);
        return 1;
    }
    n->number = 3;
    n->left = NULL;
    n->right = NULL;
    tree->right = n;

    //print the tree
    print_tree(tree);

    //free_tree(tree);
    free_tree(tree);

    return 0;
}

//since tree is a recursive structure, we could implement these function by recursion


void print_tree(node *root)
{
    if (root == NULL)
    {
        return;
    }
    // small to big
    print_tree(root->left);
    printf("%i\n", root->number);
    print_tree(root->right);
    /*big to small
    print_tree(root->right);
    printf("%i\n", root->number);
    print_tree(root->left);
    */
}

void free_tree(node *root)
{
    if (root == NULL)
    {
        return;
    }
    //attention for the order
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

//let's implement a function which do bisection to search a int in the tree
bool search(node *root, int number)
{
    if (root == NULL)
    {
        return false;
    }
    else if (number < root->number)
    {
        return search(root->left, number);
    }
    else if (number > root->number)
    {
        return search(root->right, number);
    }
    else
    {
        return true;
    }
}