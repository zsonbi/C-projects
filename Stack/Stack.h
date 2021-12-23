#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED


typedef struct StackItem StackItem;
typedef struct Stack Stack;

struct StackItem{
int value;
StackItem* prevItem;
};

struct Stack{
int Count;
StackItem* Tail;
};



//Set the stack to it's initial state
void InitStack(Stack* stack);
//Deletes the stack's content and frees up the memory
void DeleteStack(Stack* stack);
//Gets the top element in the stack
int Pop(Stack* stack);
//Push a new element on top of the stack
void Push(Stack* stack, int value);
//Gets how many elements are in the stack
int GetStackCount(Stack* stack);
//Gets the top element but doesn't remove it
int Peek(Stack* stack);
#endif