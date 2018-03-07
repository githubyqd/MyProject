#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"linkqueue.h"
#include"linklist.h"
void main()
{
	int i, a[10];
	LinkQueue *queue = NULL;
	queue = LinkQueue_Create();
	if(queue == NULL)
	{
		return;
	}
	for(i=0; i<5; i++)
	{
		a[i] = i + 1;
		LinkQueue_Append(queue, &a[i]);
	}
	printf("len: %d\n", LinkQueue_Length(queue));
	printf("header: %d\n", *(int*)LinkQueue_Header(queue));
	while(LinkQueue_Length(queue)>0)
	{
		int temp = *(int*)LinkQueue_Retrieve(queue);
		printf("temp: %d", temp);
	}
	system("pause");
}
