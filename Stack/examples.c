#include<stdio.h>
#include "Stack.h"

int main(){

Stack stack;
InitStack(&stack);

//Adds a ton of numbers to the stack
Push(&stack, 23);
Push(&stack, 27);
Push(&stack, 21);
Push(&stack, 22);
Push(&stack, 251);
Push(&stack, 245);
Push(&stack, 28);
Push(&stack, 253);

//Pops the top 3 elements
printf("First Pop: %d\n",Pop(&stack));
printf("Second Pop: %d\n",Pop(&stack));
printf("Third Pop: %d\n",Pop(&stack));

//Add a single element
Push(&stack, 1235);
//Peek at the top value without removing it
printf("Peek value %d , size: %d \n",Peek(&stack),GetStackCount(&stack));
//Pop it
printf("After adding a new element (fourth) Pop: %d\n",Pop(&stack));

//Prints the number of elements
printf("Number of Elements: %d \n",GetStackCount(&stack));

//Frees the memory
DeleteStack(&stack);

}