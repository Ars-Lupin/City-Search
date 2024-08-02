
#ifndef _DEQUE_H_
#define _DEQUE_H_

#include <stdbool.h>

typedef void *dataType;
typedef struct Deque Deque;

Deque *dequeConstruct();
void dequePushBack(void *f, dataType item);
void dequePushFront(void *f, dataType item);
void *dequePopBack(void *f);
void *dequePopFront(void *f);
void dequeDestroy(Deque *f);
int dequeSize(Deque *f);
int dequeIsEmpty(void *f);
void printDeque(Deque *f);



#endif