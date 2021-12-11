#include "List.h"
#include <stdio.h>
int main(){
//Creates a new list
List list;
InitList(&list);

//Adds the elements into the list
Add(&list,10);
Add(&list,15);
Add(&list,17);
Add(&list,55);
Add(&list,143);

//Writes out the list's contents
for (int i = 0; i < Count(&list); i++)
{
  //Get the element at the i index and print it
  printf("%d \n",GetItem(&list,i));
}
//Remove elements at the 3 index
RemoveAt(&list,3);
RemoveAt(&list,3);
//Writes out the list's contents
for (int i = 0; i < Count(&list); i++)
{
  printf("%d \n",GetItem(&list,i));
}
//Deletes the list and frees up the memory
DeleteList(&list);
}