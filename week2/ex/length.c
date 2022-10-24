#include <cs50.h>
#include <stdio.h>
#include <string.h>
//int string_length(string s);

int main(void)
{
    string name = get_string("name: ");
    int length = strlen(name);
    printf("%i\n",length);
}

/*define a function to get the length of a string.
int string_length(string s)
{
    int i = 0;
    while (s[i] != '\0') //null character is a char!
    {
        i++;
    }
    return i;
}
*/