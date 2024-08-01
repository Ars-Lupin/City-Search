#include <stdlib.h>
#include "heap.h"

struct Heap
{
    Vector *v;
    bool (*cmpFn)(dataType, dataType);
};

Heap *heapConstruct(bool (*cmpFn)(dataType, dataType))
{
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->v = vectorConstruct();
    heap->cmpFn = cmpFn;

    return heap;
}

void heapPush(Heap *heap, dataType data)
{
    vectorPushBack(heap->v, data);

    int idx = vectorSize(heap->v) - 1;

    while (idx > 0)
    {
        int idxFather = (idx - 1) / 2;

        if (heap->cmpFn(data, vectorGet(heap->v, idxFather)))
        {
            vectorSwap(heap->v, idx, idxFather);
            idx = idxFather;
        }
        else
        {
            break;
        }
    }
}

void *heapPop(Heap *heap)
{
    int idx = 0, min = 0;

    if (vectorSize(heap->v) >= 2)
    {
        vectorSwap(heap->v, idx, vectorSize(heap->v) - 1);
    }

    void *data = vectorRemove(heap->v, vectorSize(heap->v) - 1);

    while (1)
    {
        min = idx;
        int leftChild = 2 * idx + 1;
        int rightChild = 2 * idx + 2;

        if ((leftChild < vectorSize(heap->v)) &&
            (heap->cmpFn(vectorGet(heap->v, leftChild), vectorGet(heap->v, min))))
        {
            min = leftChild;
        }

        if ((rightChild < vectorSize(heap->v)) &&
            (heap->cmpFn(vectorGet(heap->v, rightChild), vectorGet(heap->v, min))))
        {
            min = rightChild;
        }

        if (min != idx)
        {
            vectorSwap(heap->v, idx, min);
            idx = min;
        }
        else
        {
            break;
        }
    }
    return data;
}

int heapSize(Heap *heap)
{
    return vectorSize(heap->v);
}

void heapDestroy(Heap *heap, void (*destroyDataType)(dataType))
{
    if (heap != NULL)
    {
        if (heap->v != NULL)
        {
            vectorDestroy(heap->v, destroyDataType);
        }
        free(heap);
    }
}

bool heapIsEmpty(Heap *heap)
{
    if (vectorSize(heap->v) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
