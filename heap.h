#ifndef HEAP_H
#define HEAP_H

#include "vector.h"
#include <stdbool.h>

typedef void *dataType;

typedef struct Heap Heap;

Heap *heapConstruct(int (*cmpFn)(const void *, const void *));
void heapPush(void *h, dataType data);
void *heapPop(void *h);
int heapSize(Heap *heap);
void heapDestroy(Heap *heap, void (*destroyDataType)(dataType));
int heapIsEmpty(void *h);
#endif 
