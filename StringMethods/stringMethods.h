#ifndef _STRING_METHODS_INCLUDED
#define _STRING_METHODS_INCLUDED
// Only works if the string contains at least 1 '\0' terminator otherwise makes an infinite cycle
int GetStringLength(const char *string);

//Replaces the string's specified characters (oldChar) with the (newChar)
void Replace(char string[], char oldChar, char newChar);

//Returns 1 if it contains 0 if it doesn't contains
unsigned char Contains(const char* string,const char* pattern);

//Cuts the string to pieces by the delim parameter and writes the indexed piece into (splitted) char* if the piece is overindexed returns a (splitted) filled with '\0'
void Cut(const char* string,const char* delim, int index, char* splitted);

//Creates a substring of the string with a start index given in the parameter and an endindex(-1 if it is until end of the string)
void SubString(char string[],char* subString, int startIndex, int length);

//Counts how many times did the specified character occured in the string
int CountOfCharacters(const char* string, char charToSearch);

//Makes the string full lowercase
void ToLower(char* string);

//Makes the string full uppercase
void ToUpper(char* string);

#endif