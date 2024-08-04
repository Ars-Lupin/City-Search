#ifndef HEAP_H
#define HEAP_H

#include "vector.h"
#include "city.h"
#include <stdbool.h>

typedef void *dataType;

typedef struct Heap Heap;

Heap *heapConstruct(int (*cmpFn)(void *, void *));
void heapPush(void *h, dataType data);
void *heapPop(void *h);
int heapSize(Heap *heap);
void heapDestroy(Heap *heap);
int heapIsEmpty(void *h);
void printSpaces(int count);
void heapPrint(Heap *heap);
#endif
