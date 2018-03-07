#pragma once
#include <iostream>
using namespace std;
template <typename T>
struct Node{
	Node<T> *next;
	T t;
};
template <typename T>
class LinkList
{
public:
	LinkList(void);
	~LinkList(void);
	void LinkList_Clear();
	int LinkList_Length();
	int LinkList_Insert(T &t, int pos);
	int LinkList_Get(int pos, T &t);
	int LinkList_Delete(int pos, T &t);
private:
	Node<T> *head;//建一个带有头结点的链表
	int len;
};
