#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
//So we can leave out the struct before the varriable
typedef struct List List;

//A single node in the list
struct ListItem{
    struct ListItem* Next;
    int data;
};

//The List itself
struct List
{
    int Count; //The number of elements in the list 
   struct ListItem* Head;
};


//Creates a new list
void InitList(List*);
//Deallocates the list's contents
void DeleteList(List*);
//Returns the number of elements in the List
int Count(List*);
//Adds a new element at the end of the list
void Add(List*,int val);
//Sets the value at the index to the parameters
void SetItem(List*,int index,int val);
//Gets the value at the specified index
int GetItem(List*,int index);
//Removes the element at the specified index from the List
void RemoveAt(List*, int index);

#endif