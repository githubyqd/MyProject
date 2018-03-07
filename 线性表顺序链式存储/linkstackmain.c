#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"linkstack.h"
void main()
{
	int i = 0;
	int a[10];
	LinkStack* stack = NULL;

	stack = LinkStack_Create();

	if(stack == NULL)
	{
		return;
	}

	for(i=0; i<5; i++)
	{
		a[i] = i + 1;
		LinkStack_Push(stack, &a[i]);
	}
	while(LinkStack_Size(stack)>0)
	{
		int temp = *(int*)LinkStack_Pop(stack);
		printf("temp: %d", temp);
	}
	printf("\n");
	system("pause");
}
