#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"seqlist.h"

typedef struct _tag_SeqList{
	int length;
	int capacity;				//最大容量
	unsigned int **node;		//动态分配内存用指针	大于0	指针数组
}TSeqList;

//动态分配线性表内存，数组指针内存
SeqList* SeqList_Create(int capacity)
{
	int ret = 0;
	TSeqList *temp = NULL;
	temp = (TSeqList*)malloc(sizeof(TSeqList));
	if(temp == NULL)
	{
		ret = -1;
		printf("func SeqList_Create err%d\n", ret);
		return NULL;
	}
	memset(temp, 0, sizeof(TSeqList));
	//根据capacity的大小分配结点的空间
	temp->node = (unsigned int**)malloc(sizeof(unsigned int*)*capacity);
	if(temp->node == NULL)
	{
		ret = -2;
		printf("func SeqList_Create err%d\n", ret);
		return NULL;
	}
	temp->capacity = capacity;
	temp->length = 0;
	return temp;
}
//先释放结点数组指针，再释放链表内存
void SeqList_Destroy(SeqList *list)
{
	TSeqList *tlist = NULL;
	tlist = (TSeqList*)list;			//内部识别list
	if(list == NULL)
	{
		return ;
	}
	if(tlist->node != NULL)
	{
		free(tlist->node);					//后分配先释放
	}
	free(tlist);
	return ;
}
//清空链表，链表长度置0即可
void SeqList_Clear(SeqList *list)
{
	TSeqList *tlist = NULL;
	tlist = (TSeqList*)list;
	if(list == NULL)
	{
		return ;
	}
	tlist->length = 0;
	return ;
}
int SeqList_Length(SeqList *list)
{
	TSeqList *tlist = NULL;
	tlist = (TSeqList*)list;
	if(list == NULL)
	{
		return -1;
	}
	return tlist->length;
}
int SeqList_Capcity(SeqList *list)
{
	TSeqList *tlist = NULL;
	tlist = (TSeqList*)list;
	if(list == NULL)
	{
		return -1;
	}
	return tlist->capacity;
}
//元素后移，插入元素
int SeqList_Insert(SeqList *list, SeqListNode *node, int pos)
{
	int i = 0, ret = 0;
	TSeqList *tlist = NULL;
	tlist = (TSeqList*)list;
	if(list == NULL || node == NULL || pos<0)
	{
		ret = -1;
		printf("func SeqList_Insert() err:%d\n", ret);
		return ret;
	}
	//判断是不是满了
	if(tlist->length == tlist->capacity)
	{
		ret = -2;
		printf("func SeqList_Insert()(length >= capacity)err:%d\n", ret);
		return ret;
	}
	//容错修正（pos大于长度小于最大容量）
	if(pos > tlist->length)
	{
		pos = tlist->length;
	}
	//元素后移
	for(i=tlist->length; i>pos; i--)
	{
		tlist->node[i] = tlist->node[i-1];	
	}
	//插入元素
	tlist->node[pos] = (unsigned int*)node;
	tlist->length++;
	return 0;
}
SeqListNode* SeqList_Get(SeqList *list, int pos)
{
	SeqListNode *ret = 0;
	TSeqList *tlist = NULL;
	tlist = (TSeqList*)list;
	if(list == NULL || pos<0)
	{
		printf("func SeqList_Insert() err:%d\n", ret);
		return NULL;
	}
	ret = (void*)tlist->node[pos];
	return ret;
}
//元素前移，长度减1
SeqListNode* SeqList_Delete(SeqList *list, int pos)
{
	int i = 0;
	SeqListNode *ret = 0;
	TSeqList *tlist = NULL;
	tlist = (TSeqList*)list;
	if(list == NULL || pos<0)//检查
	{
		printf("func SeqList_Insert() err:%d\n", ret);
		return NULL;
	}
	ret = (SeqListNode*)tlist->node[pos];//缓存pos位置
	for(i=pos+1; i<tlist->length; i++)
	{
		tlist->node[i] = tlist->node[i-1];//pos后面元素前移
	}
	tlist->length--;
	return ret;
}