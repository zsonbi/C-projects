#include <stdio.h>
int main()
{
  unsigned char dec= 213;
    unsigned char bin[8];
    for(int i = 7;i>=0;i--){
    
       bin[i]= (dec >> (7-i)) & 1 ;

    }

    for(int i=0; i<8;i++){
        printf("%d",bin[i]);
    }

}