#ifndef HEAP_H
#define HEAP_H

#include "vector.h"

typedef void *dataType;

typedef struct Heap Heap;

Heap *heapConstructor(int (*cmpFn)(dataType, dataType));
void heapPush(Heap *heap, dataType data);
void *heapPop(Heap *heap);
int heapSize(Heap *heap);
void heapDestroy(Heap *heap, void (*destroyDataType)(dataType));

#endif 
