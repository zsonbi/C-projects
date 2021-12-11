#include "stringMethods.h"
#include <stdio.h>
#include <ctype.h>

// Only works if the string contains at least 1 '\0' terminator otherwise makes an infinite cycle
int GetStringLength(const char *string)
{
    for (int i = 0; 1; i++)
    {
        if (string[i] == '\0')
        {
            return i;
        }
    }
    return -1;
}

// Replaces the string's specified characters (oldChar) with the (newChar)
void Replace(char *string, char oldChar, char newChar)
{
    for (char *ptr = string; (*ptr) != '\0'; ptr++)
    {
        if ((*ptr) == oldChar)
        {
            (*ptr) = newChar;
        }
    }
}

// Returns 1 if it contains 0 if it doesn't contains
unsigned char Contains(const char *string, const char *pattern)
{
    int stringSize = GetStringLength(string);
    int patternSize = GetStringLength(pattern);

    for (size_t i = 0; i <= stringSize - patternSize; i++)
    {
        for (size_t j = 0; j < patternSize; j++)
        {
            if (string[i + j] != pattern[j])
            {
                break;
            }

            if (j == patternSize - 1)
            {
                return 1;
            }
        }
    }
    return 0;
}

// Cuts the string to pieces by the delim parameter and writes the indexed piece into (splitted) char* if the piece is overindexed returns a (splitted) filled with '\0'
void Cut(const char *string, const char *delim, int index, char *splitted)
{
    int counter = 0;
    int splittedIndex = 0;
    int delimSize = GetStringLength(delim);
    for (const char *ptr = string; (*ptr) != '\0'; ptr++)
    {

        for (int i = 0; i < delimSize; i++)
        {
            if (*(ptr + i) != delim[i])
            {
                break;
            }
            if (i == delimSize - 1)
            {
                counter++;
                ptr += (delimSize);
                i=-1;

            }
        }

        if (counter == index)
        {
            splitted[splittedIndex] = (*ptr);
            splittedIndex++;
        }
        else if (counter > index)
        {
            break;
        }
    }
    splitted[splittedIndex] = '\0';
}

// Creates a substring of the string with a start index given in the parameter and an endindex(-1 if it is until end of the string)
void SubString(char string[], char *subString, int startIndex, int length)
{
    if (length == -1)
    {
        length = GetStringLength(string) - startIndex;
    }
    else if (length + startIndex > GetStringLength(string))
    {
        length = GetStringLength(string) - startIndex;
    }

    printf("Length: %d \n", length);

    for (size_t i = startIndex; i < startIndex + length; i++)
    {
        subString[i - startIndex] = string[i];
    }
    subString[length] = '\0';
}

// Counts how many times did the specified character occured in the string
int CountOfCharacters(const char *string, char charToSearch)
{
    int counter = 0;
    for (const char *ptr = string; (*ptr) != '\0'; ptr++)
    {
        if ((*ptr) == charToSearch)
        {
            counter++;
        }
    }
    return counter;
}

//Makes the string full lowercase
void ToLower(char* string){
for (char* ptr  = string; (*ptr)!='\0'; ptr++)
{
    (*ptr) = tolower((*ptr));
}
}

//Makes the string full uppercase
void ToUpper(char* string){
for (char* ptr  = string; (*ptr)!='\0'; ptr++)
{
    (*ptr) = toupper((*ptr));
}
}