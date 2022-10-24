#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    float L = (letters / (float) words) * 100.0;
    float S = (sentences / (float) words) * 100.0;
    int index = (int) round(0.0588 * L - 0.296 * S - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string text)
{
    int n = strlen(text);
    int nums_letters = 0;

    for (int i = 0; i < n; i++)
    {
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            nums_letters += 1;
        }
        else if (text[i] >= 'A' && text[i] <= 'Z')
        {
            nums_letters += 1;
        }
    }
    return nums_letters;
}

int count_words(string text)
{
    int n = strlen(text);
    int nums_words = 0;

    for (int i = 0; i < n; i++)
    {
        if (text[i] == ' ')
        {
            nums_words += 1;
        }
    }
    nums_words += 1;
    return nums_words;
}

int count_sentences(string text)
{
    int n = strlen(text);
    int nums_sentences = 0;

    for (int i = 0; i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            nums_sentences += 1;
        }
    }
    return nums_sentences;
}