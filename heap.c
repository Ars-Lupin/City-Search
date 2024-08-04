#include <stdlib.h>
#include <stdio.h>
#include "heap.h"


struct Heap
{
    Vector *v;
    int (*cmpFn)(void *, void *);
};

Heap *heapConstruct(int (*cmpFn)(void *, void *))
{
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->v = vectorConstruct();
    heap->cmpFn = cmpFn;

    return heap;
}

void heapPush(void *h, dataType data)
{
    Heap *heap = (Heap *)h;
    vectorPushBack(heap->v, data);

    int idx = vectorSize(heap->v) - 1;

    while (idx > 0)
    {
        int idxFather = (idx - 1) / 2;

        if (!heap->cmpFn(data, vectorGet(heap->v, idxFather)))
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

void *heapPop(void *h)
{
    Heap *heap = (Heap *)h;
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
            (!heap->cmpFn(vectorGet(heap->v, leftChild), vectorGet(heap->v, min))))
        {
            min = leftChild;
        }

        if ((rightChild < vectorSize(heap->v)) &&
            (!heap->cmpFn(vectorGet(heap->v, rightChild), vectorGet(heap->v, min))))
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

void heapDestroy(Heap *heap)
{
    if (heap != NULL)
    {
        if (heap->v != NULL)
        {
            vectorDestroy(heap->v);
        }
        free(heap);
    }
}

int heapIsEmpty(void *h)
{
    Heap *heap = (Heap *)h;
    if (vectorSize(heap->v) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void printSpaces(int count) {
    int i;
    for ( i = 0; i < count; i++) {
        printf("  ");
    }
}

void heapPrint(Heap *f) {
    int size = vectorSize(f->v);
    if (size == 0) {
        printf("Heap is empty.\n");
        return;
    }

    int levels = (int)log2(size) + 1; // Calcula o número de níveis na heap
    int maxWidth = (1 << levels) - 1; // Largura máxima da última linha

    int currentLevel = 0;
    int elementsInLevel = 1;
    int index = 0, i;

    while (index < size) {
        int spaceBetweenElements = (maxWidth / elementsInLevel) / 2;

        if (currentLevel == 0) {
            printSpaces(spaceBetweenElements);
        }

        for ( i = 0; i < elementsInLevel && index < size; i++) {
            printf("|%s|", getName(vectorGet(f->v, index)));
            index++;
            if (i < elementsInLevel - 1) {
                printSpaces(spaceBetweenElements * 2 - 1);
            }
        }

        printf("\n");
        currentLevel++;
        elementsInLevel *= 2;
        printSpaces(spaceBetweenElements / 2);
    }
}