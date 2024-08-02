#include <stdio.h>
#include <stdlib.h>
#include "deque.h"
#include "city.h"

struct Deque
{
    dataType *arr;
    int start;
    int end;
    int size;
    int allocated;
};

Deque *dequeConstruct()
{
    Deque *deque = (Deque *)calloc(1, sizeof(Deque));
    deque->arr = (dataType *)calloc(1, sizeof(dataType));
    deque->allocated = 1;
    return deque;
}

void dequePushBack(void *f, dataType item)
{
    Deque *deque = (Deque *)f;
    
    if (deque->size >= deque->allocated)
    {
        deque->allocated *= 2;

        dataType *newArray = (dataType *)malloc(deque->allocated * sizeof(dataType));

        for (int i = 0; i < deque->size; i++)
        {
            int idx = (deque->start + i) % deque->size;
            newArray[i] = deque->arr[idx];
        }
        deque->start = 0;
        deque->end = deque->size;

        free(deque->arr);
        deque->arr = newArray;
    }
    deque->arr[deque->end] = item;
    deque->end = (deque->end + 1) % deque->allocated;
    deque->size++;
}

void dequePushFront(void *f, dataType item)
{
    Deque *deque = (Deque *)f;
    
    if (deque->size >= deque->allocated)
    {
        deque->allocated *= 2;

        dataType *newArray = (dataType *)malloc(deque->allocated * sizeof(dataType));

        for (int i = 0; i < deque->size; i++)
        {
            int idx = (deque->start + i) % deque->size;
            newArray[i] = deque->arr[idx];
        }
        deque->start = 0;
        deque->end = deque->size;

        free(deque->arr);
        deque->arr = newArray;
    }

    if (deque->start - 1 < 0)
        deque->start = deque->allocated;

    deque->arr[deque->start - 1] = item;
    deque->start = (deque->start - 1) % deque->allocated;
    deque->size++;
}

int dequeSize(Deque *f)
{
    return f->size;
}

dataType dequePopBack(void *f)
{
    Deque *deque = (Deque *)f;
    if (deque->end - 1 < 0)
        deque->end = deque->allocated;

    dataType popped = deque->arr[deque->end - 1];
    deque->end = (deque->end - 1) % deque->allocated;
    deque->size--;
    return popped;
}

dataType dequePopFront(void *f)
{
    Deque *deque = (Deque *)f;
    dataType popped = deque->arr[deque->start];
    deque->start = (deque->start + 1) % deque->allocated;
    deque->size--;
    return popped;
}

void dequeDestroy(Deque *f)
{
    if (f != NULL)
    {
        if (f->arr != NULL)
        {
            free(f->arr);
        }
        free(f);
    }
}

int dequeIsEmpty(void *f)
{
    Deque *deque = (Deque *)f;
    if (deque->size == 0)
    {
        return 1;
    }
    return 0;
}

void printDeque(Deque *f)
{
    for (int i = 0; i < f->size; i++)
    {
        printf("%d", f->size);
        printf("%s ", getName(f->arr[i]));
    }
    printf("\n");
}

