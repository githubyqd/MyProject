#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"linkqueue.h"
#include"linklist.h"

typedef struct _tag_LinkQueueNode
{
	LinkListNode node;
	void* item;
}TLinkQueueNode;
void LinkQueue_Destroy(LinkQueue* queue)
{
	LinkQueue_Clear(queue);
	LinkList_Destroy(queue);
	return ;
}
void LinkQueue_Clear(LinkQueue* queue)
{
	//释放每个结点内存
	while (LinkQueue_Length(queue)>0)
	{
		LinkQueue_Retrieve(queue);
	}
	LinkList_Clear(queue);
	return ;
}
int LinkQueue_Append(LinkQueue* queue, void* item)
{
	int ret = 0;
	TLinkQueueNode* temp = NULL;
	temp = (TLinkQueueNode*)malloc(sizeof(TLinkQueueNode));
	if(temp == NULL)
	{
		ret = -1;
		printf("func LinkQueue_Append() err: %d\n", ret);
		return ret;
	}
	memset(temp, 0, sizeof(TLinkQueueNode));
	temp->item = item;
	ret = LinkList_Insert(queue, (LinkListNode*)temp, LinkList_Length(queue));
	if(ret != 0)
	{
		printf("func LinkList_Insert() err: %d\n", ret);
		if(temp != NULL) free(temp);
		return ret;
	}
	return ret;
}
void* LinkQueue_Retrieve(LinkQueue* queue
{
	TLinkQueueNode* temp = NULL;
	void* ret = NULL;
	temp = (TLinkQueueNode*)LinkList_Delete(queue, 0);
	if(temp == NULL)
	{
		printf("func LinkList_Delete() err: %d\n");
		return NULL;
	}
	ret = temp->item;
	if(temp!=NULL)
	{
		free(temp);
	}
	return ret;
}
void* LinkQueue_Header(LinkQueue* queue)
{
	TLinkQueueNode* temp = NULL;
	temp = (TLinkQueueNode*)LinkList_Get(queue, 0);
	if(temp == NULL)
	{
		printf("func LinkList_Get() err: %d\n");
		return NULL;
	}
	return temp->item;
}
int LinkQueue_Length(LinkQueue* queue)
{
	return LinkList_Length(queue);
}
