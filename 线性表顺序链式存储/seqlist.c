#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"seqlist.h"

typedef struct _tag_SeqList{
	int length;
	int capacity;				//�������
	unsigned int **node;		//��̬�����ڴ���ָ��	����0	ָ������
}TSeqList;

//��̬�������Ա��ڴ棬����ָ���ڴ�
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
	//����capacity�Ĵ�С������Ŀռ�
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
//���ͷŽ������ָ�룬���ͷ������ڴ�
void SeqList_Destroy(SeqList *list)
{
	TSeqList *tlist = NULL;
	tlist = (TSeqList*)list;			//�ڲ�ʶ��list
	if(list == NULL)
	{
		return ;
	}
	if(tlist->node != NULL)
	{
		free(tlist->node);					//��������ͷ�
	}
	free(tlist);
	return ;
}
//���������������0����
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
//Ԫ�غ��ƣ�����Ԫ��
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
	//�ж��ǲ�������
	if(tlist->length == tlist->capacity)
	{
		ret = -2;
		printf("func SeqList_Insert()(length >= capacity)err:%d\n", ret);
		return ret;
	}
	//�ݴ�������pos���ڳ���С�����������
	if(pos > tlist->length)
	{
		pos = tlist->length;
	}
	//Ԫ�غ���
	for(i=tlist->length; i>pos; i--)
	{
		tlist->node[i] = tlist->node[i-1];	
	}
	//����Ԫ��
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
//Ԫ��ǰ�ƣ����ȼ�1
SeqListNode* SeqList_Delete(SeqList *list, int pos)
{
	int i = 0;
	SeqListNode *ret = 0;
	TSeqList *tlist = NULL;
	tlist = (TSeqList*)list;
	if(list == NULL || pos<0)//���
	{
		printf("func SeqList_Insert() err:%d\n", ret);
		return NULL;
	}
	ret = (SeqListNode*)tlist->node[pos];//����posλ��
	for(i=pos+1; i<tlist->length; i++)
	{
		tlist->node[i] = tlist->node[i-1];//pos����Ԫ��ǰ��
	}
	tlist->length--;
	return ret;
}