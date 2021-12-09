#include "List.h"
#include <stdio.h>
#include <stdlib.h>

//Returns a pointer to the listItem in the list at the specified index
struct ListItem *GetListItemAtIndex(List *list, int index)
{
   struct ListItem *listItem = list->Head;
   while (index-- != 0)
   {
      if (listItem->Next == 0)
      {
         printf("over indexed");
         exit(1);
      }
      listItem = listItem->Next;
   }
   return listItem;
}

//Creates a new list
void InitList(List *list)
{
   if(list->Head > 0){
   printf("List is already initialized");
   }
   list->Head = 0;
   list->Count=0;
}

//Adds a new element at the end of the list
void Add(List *list, int val)
{
   struct ListItem *item;
   //Allocates memory for the item
   item = (struct ListItem *)malloc(sizeof(struct ListItem));
   item->data = val;
   item->Next = 0;
   struct ListItem *next = list->Head;
   //If it's the first element add it directly
   if (list->Head == 0)
   {
      list->Head = item;
   }
   //Otherwise search for the last element
   else
   {
      while (next->Next != 0)
      {
         next = next->Next;
      }
      next->Next = item;
   }
   list->Count++;
}
//Returns the number of elements in the List
int Count(List *list)
{
   return list->Count;
}
//Gets the value at the specified index
int GetItem(List *list, int index)
{
   return GetListItemAtIndex(list, index)->data;
}
//Sets the value at the index to the parameters
void SetItem(List *list, int index, int val)
{
   GetListItemAtIndex(list, index)->data = val;
}
//Removes the element at the specified index from the List
void RemoveAt(List *list, int index)
{
   //Check for over indexing
   if (index >= list->Count || index < 0)
   {
      printf("index out of bounds");
      exit(1);
   }
   struct ListItem *pointerToRemove;
   //If it's the first element just replace the head
   if (index == 0)
   {
      pointerToRemove = list->Head;
      list->Head = list->Head->Next;
   }
   //Find the element and replace the next pointers
   else
   {
      pointerToRemove = list->Head;
      while (index-- != 1)
      {
         pointerToRemove = pointerToRemove->Next;
      }
      struct ListItem *tempPointer = pointerToRemove->Next;
      pointerToRemove->Next = tempPointer->Next;
      pointerToRemove = tempPointer;
   }
   //Frees the memory
   free(pointerToRemove);
   list->Count--;
}

//Deallocates the list's contents
void DeleteList(List *list)
{
   struct ListItem *pointerIndex = list->Head; //A pointer so we can index through the whole List
   struct ListItem *tempPointer; //A pointer to store the next element while we deallocate the current pointerIndex

   //While the pointer is pointing to an active ListItem
   while (pointerIndex != 0)
   {
      tempPointer = pointerIndex->Next;
      //Frees the memory
            free(pointerIndex); 
      pointerIndex = tempPointer;
   }
   //Set the head to 0 so it doesn't cause problems later
   list->Head=0;
   list->Count=0;
}