#include <stdio.h>
#include "../StringMethods/stringMethods.h"

// Converts the hex value to decimal (16 bit number)
unsigned short HexToDecimal(const char *hexVal)
{

    int len = GetStringLength(hexVal);

    // Initializing base value to 1, i.e 16^0
    int base = 1;

    unsigned short dec_val = 0;

    // Extracting characters as digits from last
    // character
    for (int i = len - 1; i >= 0; i--)
    {
        // if character lies in '0'-'9', converting
        // it to integral 0-9 by subtracting 48 from
        // ASCII value
        if (hexVal[i] >= '0' && hexVal[i] <= '9')
        {
            dec_val += ((hexVal[i]) - 48) * base;

            // incrementing base by power
            base = base * 16;
        }

        // if character lies in 'A'-'F' , converting
        // it to integral 10 - 15 by subtracting 55
        // from ASCII value
        else if (hexVal[i] >= 'A' && hexVal[i] <= 'F')
        {
            dec_val += ((hexVal[i]) - 55) * base;

            // incrementing base by power
            base = base * 16;
        }

        else
        {
            printf("\nINVALID HEX FORMAT: %c \n", hexVal[i]);
        }
    }
    return dec_val;
}

// Reads in an ipv6 address without the prefix
void ReadInIp(unsigned short address[8])
{
    char input[50];
    printf("Give an ipv6 network address without prefix: \n");
    scanf("%s49", input);

    // Makes it full uppercase
    ToUpper(input);

    // Convert it to decimals (unsigned shorts)
    int numberOfHextet = CountOfCharacters(input, ':') + 1;
    int addressIndex = 0;
    for (int i = 0; i < numberOfHextet; i++)
    {
        char splitted[5];
        Cut(input, ":", i, splitted);
        if (splitted[0] == '\0')
        {

            for (int j = 0; j <= 8 - numberOfHextet; j++)
            {
                address[addressIndex] = 0;
                addressIndex++;
            }
        }
        else
        {
            address[addressIndex] = HexToDecimal(splitted);
            addressIndex++;
        }
    }
}

// Summarize 2 ipv6 networks into 1
void Summarize(unsigned short firstAddress[8], unsigned short secondAddress[8], unsigned short result[8], unsigned char *prefix)
{
    // Null it out
    for (unsigned char i = 0; i < 8; i++)
    {
        result[i] = 0;
    }
    (*prefix) = 0;

    for (int i = 0; i < 8; i++)
    {
        if (firstAddress[i] ^ secondAddress[i])
        {
            for (int j = 15; j >= 0; j--)
            {
                if ((firstAddress[i] >> j) ^ (secondAddress[i] >> j))
                {
                    // printf("\n first: %x second: %x itr %d \n",firstAddress[i] >> j,secondAddress[i] >> j, j);
                    return;
                }
                else
                {
                    result[i] += (1 << j) * ((firstAddress[i] >> j) % 2);
                    (*prefix)++;
                }
            }
        }
        else
        {
            result[i] = firstAddress[i];
            (*prefix) += 16;
        }
    }
}

// Start of the code
int main()
{
    unsigned short firstIpv6[8];
    ReadInIp(firstIpv6);

    unsigned short secondIpv6[8];
    ReadInIp(secondIpv6);

    unsigned short result[8];
    unsigned char prefix;
    Summarize(firstIpv6, secondIpv6, result, &prefix);

    printf("Result: \n");

    for (size_t i = 0; i < 8; i++)
    {
        printf("%x", result[i]);
        if (i < 7)
        {
            printf(":");
        }
    }

    printf("/%d", prefix);
}