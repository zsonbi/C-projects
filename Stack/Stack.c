#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>

// Set the stack to it's initial state
void InitStack(Stack *stack)
{
    stack->Tail = NULL;
    stack->Count = 0;
}
// Push a new element on top of the stack
void Push(Stack *stack, int value)
{
    StackItem *lastItem = stack->Tail;
    stack->Tail = (StackItem *)malloc(sizeof(StackItem));
    stack->Tail->prevItem = lastItem;
    stack->Tail->value = value;
    stack->Count++;
}
// Gets the top element in the stack
int Pop(Stack *stack)
{
    if (stack->Count == 0)
    {
        printf("Stack is empty");
        return 0;
    }

    StackItem *lastItem = stack->Tail;
    stack->Tail = lastItem->prevItem;
    int val = (*lastItem).value;
    free(lastItem);
    stack->Count--;
    return val;
}
// Gets the top element but doesn't remove it
int Peek(Stack *stack)
{
    if (stack->Count == 0)
    {
        printf("Peek not possible stack is empty");
        return 0;
    }
    return stack->Tail->value;
}
// Gets how many elements are in the stack
int GetStackCount(Stack *stack)
{
    return stack->Count;
}

// Deletes the stack's content and frees up the memory
void DeleteStack(Stack *stack)
{
    StackItem *prevItem = stack->Tail;

    while (prevItem != NULL)
    {
        StackItem *tempPtr = prevItem->prevItem;
        free(prevItem);

        prevItem = tempPtr;
    }

    stack->Count = 0;
    stack->Tail = NULL;
}