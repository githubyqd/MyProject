#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"LinkList.h"

typedef struct _tag_LinkList{
	LinkListNode header;
	int length;
}TLinkList;

LinkList* LinkList_Create()
{
	TLinkList *ret = NULL;
	ret = (TLinkList *)malloc(sizeof(TLinkList));
	if(ret == NULL)
	{
		printf("func LinkList_Create() err: %d\n", ret);
	}
	memset(ret, 0, sizeof(TLinkList));
	ret->header.next = NULL;
	ret->length = 0;
	return ret;
}

//销毁链表直接释放链表
void LinkList_Destroy(LinkList* list)	
{
	if(list != NULL)
	{
		free(list);
		list ==NULL;
	}
	return;
}
//回到初始值头部和长度初始化
void LinkList_Clear(LinkList* list)
{
	TLinkList *tlist = (TLinkList *)list;
	if(list == NULL)
	{
		return;
	}
	tlist->header.next = NULL;
	tlist->length = 0;
	return;
}
int LinkList_Length(LinkList* list)
{
	TLinkList *tlist = (TLinkList *)list;
	tlist = (TLinkList*)list;
	if(list == NULL)
	{
		return;
	}
	return tlist->length;
}
int LinkList_Insert(LinkList* list, LinkListNode* node, int pos)
{
	LinkListNode *crurrent =NULL;
	TLinkList *tlist = NULL;
	int i = 0, ret = 0;;
	tlist = (TLinkList*)list;
	if(list==NULL||node==NULL||pos<0)
	{
		ret = 0;
		printf("func LinkList_Insert() err: %d\n", ret);
		return ret;
	}
	crurrent = &(tlist->header);
	for(i=0; i<pos; i++)
	{
		crurrent = crurrent->next;
	}
	node->next = crurrent->next;
	crurrent->next = node;
	tlist->length++;
	return 0;
}
LinkListNode* LinkList_Get(LinkList* list, int pos)
{
	int i = 0;
	TLinkList *tlist = NULL;
	LinkListNode* crurrent =NULL;
	tlist = (TLinkList*)list;
	if(list==NULL||pos<0)
	{
		printf("func LinkList_Get() err: %d\n");
		return NULL;
	}
	crurrent = &(tlist->header);
	for(i=0; i<pos; i++)
	{
		crurrent = crurrent->next;
	}
	return crurrent->next;
}
LinkListNode* LinkList_Delete(LinkList *list, int pos)
{
	int i = 0;
	TLinkList *tlist = NULL;
	LinkListNode* crurrent =NULL;
	LinkListNode* temp = NULL;
	tlist = (TLinkList*)list;
	if(list==NULL||pos<0)
	{
		printf("func LinkList_Delete() err: %d\n");
		return NULL;
	}
	crurrent = &(tlist->header);
	for(i=0; i<pos; i++)
	{
		crurrent = crurrent->next;
	}
	temp = crurrent->next;
	crurrent->next = crurrent->next->next;
	tlist->length--;
	return temp;
}
