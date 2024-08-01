
#ifndef _DEQUE_H_
#define _DEQUE_H_

#include <stdbool.h>

typedef void *dataType;
typedef struct Deque Deque;

Deque *dequeConstruct();
void dequePushBack(Deque *f, dataType item);
void dequePushFront(Deque *f, dataType item);
void *dequePopBack(Deque *f);
void *dequePopFront(Deque *f);
void dequeDestroy(Deque *f);
int dequeSize(Deque *f);
bool dequeIsEmpty(Deque *f);
void printDeque(Deque *f);


#endif