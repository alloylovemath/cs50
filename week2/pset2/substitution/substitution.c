#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    //doesn’t cooperate
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];
    int n = strlen(key);

    //invalid key
    if (n != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        if (isalpha(key[i]) == 0)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }

        for (int j = i + 1; j < n; j++)
        {
            if (key[i] == key[j])
            {
                printf("Key must contain 26 characters.\n");
                return 1;
            }
        }
    }

    string plaintext = get_string("plaintext:  ");
    printf("ciphertext: ");
    int length = strlen(plaintext);

    //cipher
    int ASC = 0;
    int asc = 0;
    for (int i = 0; i < length; i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                ASC = ((int) plaintext[i]) - 65;
                printf("%c", toupper(key[ASC]));
            }
            else
            {
                asc = ((int) plaintext[i]) - 97;
                printf("%c", tolower(key[asc]));
            }
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}