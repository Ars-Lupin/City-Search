
#ifndef _DEQUE_H_
#define _DEQUE_H_

typedef void *dataType;
typedef struct Deque Deque;

Deque *dequeConstruct();
void dequePushBack(Deque *f, dataType item);
void dequePushFront(Deque *f, dataType item);
void *dequePopBack(Deque *f);
void *dequePopFront(Deque *f);
void dequeDestroy(Deque *f);
int dequeSize(Deque *f);
int dequeAllocated(Deque *f);

#endif