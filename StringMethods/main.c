#include<stdio.h>
#include "stringMethods.h"


//Examples
int main(){

char arr[] ="172.25.62.7";

printf("Size of string: %d\n", GetStringLength(arr));

printf("OG string: %s \n",arr);
Replace(arr,'4','8');

printf("Replaced string: %s\n",arr);

printf("Contains: %d\n",Contains(arr,"."));

char splitted[4];
Cut(arr,".",2,splitted);

printf("Splitted: %s\n",splitted);

char subStr[20];
SubString(arr,subStr,2,-1);

printf("Substring: %s",subStr);

    return 0;
}