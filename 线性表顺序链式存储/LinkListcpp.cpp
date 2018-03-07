#include<iostream>
using namespace std;
#include"LinkList.h"
template <typename T>
LinkList<T>::LinkList(void)
{
	head = new Node<T>;
	head->next = NULL;
	this->len = 0;
}
template <typename T>
LinkList<T>::~LinkList(void){}
//回到初始值，释放每一个结点
template <typename T>
void LinkList<T>::LinkList_Clear()
{
	Node<T>* temp =NULL;
	while (head != NULL)
	{
		temp = head->next; 
		delete head;
		head = temp;
	}
	len = 0;
	head = NULL;
	return;
}
template <typename T>
int LinkList<T>::LinkList_Length()
{
	return len;
}
template <typename T>
int LinkList<T>::LinkList_Insert(T &t, int pos)
{
	Node<T> *crurrent = NULL;
	crurrent = head;
	for(int i=0; i<pos; i++)
	{
		crurrent = crurrent->next;
	}
	Node<T>* node = new Node<T>;
	node->t = t;
	node->next = NULL;
	node->next = crurrent->next;
	crurrent->next = node;
	len++;
	return 0;
}
template <typename T>
int LinkList<T>::LinkList_Delete(int pos, T &t)
{
	Node<T>* crurrent =NULL;
	Node<T>* temp =NULL;
	crurrent = head;
	for(int i=0; i<pos; i++)
	{
		crurrent = crurrent->next;
	}
	temp = crurrent->next;
	t = temp->t;
	crurrent->next = crurrent->next->next;
	len--;
	delete temp;
	return 0;
}
