#include "List.h"
#include <stdio.h>
int main(){
List list;

InitList(&list);
Add(&list,10);
Add(&list,15);
Add(&list,17);
Add(&list,55);
Add(&list,143);
for (int i = 0; i < Count(&list); i++)
{
  printf("%d \n",GetItem(&list,i));
}
RemoveAt(&list,3);
RemoveAt(&list,3);
for (int i = 0; i < Count(&list); i++)
{
  printf("%d \n",GetItem(&list,i));
}
DeleteList(&list);
}