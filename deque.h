
#ifndef _DEQUE_H_
#define _DEQUE_H_

#include <stdbool.h>
#include <string.h>

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
int dequeFind(Deque *f, dataType item, int(*eq_name)(void*,void*));



#endif