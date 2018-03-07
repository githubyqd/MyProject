#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"linkstack.h"
#include"linklist.h"
typedef struct _tag_LinkStack
{
	LinkListNode node;
	void* item;//ջ��ҵ����
}TLinkStack;
void LinkStack_Destroy(LinkStack* stack)
{
	LinkStack_Clear(stack);
	LinkList_Destroy(stack);
	return ;
}
//�漰��ջ��Ԫ���������ڵĹ���������ջ�Ľ�㶼��malloc�����ģ�����Ҫ�ͷŽ���ڴ�
void LinkStack_Clear(LinkStack* stack)
{
	if(stack == NULL)
	{
		return;
	}
	while (LinkStack_Size(stack)>0)
	{
		LinkStack_Pop(stack);
	}
	return ;
}
int LinkStack_Push(LinkStack* stack, void* item)
{
	TLinkStack* temp = NULL;
	int ret = 0;
	temp = (TLinkStack*)malloc(sizeof(TLinkStack));
	if(temp == NULL)
	{
		return -1;
	}
	memset(temp, 0, sizeof(TLinkStack));
	temp->item = item;
	ret = LinkList_Insert(stack, (LinkListNode*)temp, 0);
	if(ret != 0)
	{
		printf("func LinkStack_Push() err:%d\n", ret);
		if(temp!=NULL)
		{
			free(temp);
		}
	}
	return ret;
}
void* LinkStack_Pop(LinkStack* stack)
{
	TLinkStack* temp = NULL;
	void* item = NULL;
	temp = (TLinkStack*)LinkList_Delete(stack, 0);
	if (temp == NULL)
	{
		return NULL;
	}
	item = temp->item;
	free(temp);
	return item;
}
void* SLinkStack_Top(LinkStack* stack)
{
	TLinkStack* temp = NULL;
	temp = (TLinkStack*)LinkList_Get(stack, 0);
	if (temp == NULL)
	{
		return NULL;
	}
	return temp->item;
}
int LinkStack_Size(LinkStack* stack)
{
	return LinkList_Length(stack);
}
