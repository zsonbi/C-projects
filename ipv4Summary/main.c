#include <stdio.h>
#include <stdlib.h>
#include "../StringMethods/stringMethods.h"

//Converts the decimal into binary
void ToBinary(unsigned char dec, unsigned char *binary)
{
    for (int i = 7; i >= 0; i--)
    {

        binary[i] = (dec >> (7-i)) & 1;
        //   binary[i] = (dec % 2 == 0) ? 0 : 1;
        //  dec /= 2;
    }
}

//Converts the binary into decimal
int ToDec(unsigned char *bin)
{
    int dec = 0;
    int multiplier = 1;

    for (int i = 7; i >= 0; i--)
    {
        dec += bin[i] * multiplier;
        multiplier *= 2;
    }

    return dec;
}

//Reads in the ip from the user
void ReadInIp(unsigned char *ipArr)
{
    char userInput[20] ;
    scanf("%19s", userInput);
    for (size_t i = 0; i < 4; i++)
    {
        char splitted[8];
        Cut(userInput, ".", i, splitted);
        ipArr[i] = (unsigned char)atoi(splitted);
    }
}

//Start of the code
int main()
{
    printf("Write the lower ip in dec:");
    unsigned char lowerIP[4];

    ReadInIp(lowerIP);
    printf("Write the higher ip in dec:");
    unsigned char higherIP[4];
    ReadInIp(higherIP);

    unsigned char lowerIpBin[4][8];
    for (size_t i = 0; i < 4; i++)
    {
        ToBinary(lowerIP[i], lowerIpBin[i]);
    }

    unsigned char higherIPBin[4][8];
    for (size_t i = 0; i < 4; i++)
    {
        ToBinary(higherIP[i], higherIPBin[i]);
    }

    unsigned char result[4][8];

  for (size_t i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
        result[i][j]=0;
        
        }
    }

    unsigned char prefix;

     for (size_t i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
        if(!(lowerIpBin[i][j] ^ higherIPBin[i][j])){
            result[i][j]=lowerIpBin[i][j];
        }
        else{
            prefix = i*8+j;
            goto Result;
        }
        }
    }


//Prints the result
Result:
printf("The summary: \nIn binary: ");
  
    for (size_t i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
        

            printf("%d", result[i][j]);
        }
        if(i<3)
        printf(".");
    }

    printf("\nIn decimals: ");
    for (size_t i = 0; i < 4; i++)
    {
        printf("%d", ToDec(result[i]));

        if(i < 3)
        {
            printf(".");
        }
    }

    printf("/%d\n",prefix);
    
    scanf("%s");
   
}