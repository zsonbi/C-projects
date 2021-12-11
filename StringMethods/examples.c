#include<stdio.h>
#include "stringMethods.h"


//Examples
int main(){

//The example string
//(it has to be of type char[] with char* it doesn't work)
char arr[] ="asD4624dsA..";

//Gets the number of characters in the string
printf("Size of string: %d\n", GetStringLength(arr));

//Replaces the string's '4' characters to '8'
printf("OG string: %s \n",arr);
Replace(arr,'4','8');
printf("Replaced string: %s\n",arr);

//Checks if the string contains '.'
printf("Contains: %d\n",Contains(arr,"."));

//Gets the substring after second '.' till the third '.'
char splitted[4];
Cut(arr,".",1,splitted);
printf("Splitted: %s\n",splitted);

//Creates a substring from the third character till the end of the string
char subStr[20];
SubString(arr,subStr,2,-1);
printf("Substring: %s \n",subStr);

//Gets the number of '.' characters
printf("There are %d '.' in the string \n", CountOfCharacters(arr,'.'));

//Makes the string full lower case
ToLower(arr);
printf("Lowercase string: %s \n",arr);

//Makes the string full upper case
ToUpper(arr);
printf("Lowercase string: %s \n",arr);

    return 0;
}