#ifndef HEAP_H
#define HEAP_H

#include "vector.h"
#include <stdbool.h>

typedef void *dataType;

typedef struct Heap Heap;

Heap *heapConstruct(bool (*cmpFn)(dataType, dataType));
void heapPush(Heap *heap, dataType data);
void *heapPop(Heap *heap);
int heapSize(Heap *heap);
void heapDestroy(Heap *heap, void (*destroyDataType)(dataType));
bool heapIsEmpty(Heap *heap);

#endif 
