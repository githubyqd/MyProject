#ifndef _MY_SEQSTACK_H_
#define _MY_SEQSTACK_H_

typedef void LinkStack;

LinkStack* LinkStack_Create();
void LinkStack_Destroy(LinkStack* stack);
void LinkStack_Clear(LinkStack* stack);
int LinkStack_Push(LinkStack* stack, void* item);
void* LinkStack_Pop(LinkStack* stack);
void* SLinkStack_Top(LinkStack* stack);
int LinkStack_Size(LinkStack* stack);
int LinkStack_Capacity(LinkStack* stack);
#endif
