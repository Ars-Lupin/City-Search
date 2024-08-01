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

void dequePushBack(Deque *f, dataType item)
{
    if (f->size >= f->allocated)
    {
        f->allocated *= 2;

        dataType *newArray = (dataType *)malloc(f->allocated * sizeof(dataType));

        for (int i = 0; i < f->size; i++)
        {
            int idx = (f->start + i) % f->size;
            newArray[i] = f->arr[idx];
        }
        f->start = 0;
        f->end = f->size;

        free(f->arr);
        f->arr = newArray;
    }
    f->arr[f->end] = item;
    f->end = (f->end + 1) % f->allocated;
    f->size++;
}

void dequePushFront(Deque *f, dataType item)
{
    if (f->size >= f->allocated)
    {
        f->allocated *= 2;

        dataType *newArray = (dataType *)malloc(f->allocated * sizeof(dataType));

        for (int i = 0; i < f->size; i++)
        {
            int idx = (f->start + i) % f->size;
            newArray[i] = f->arr[idx];
        }
        f->start = 0;
        f->end = f->size;

        free(f->arr);
        f->arr = newArray;
    }

    if (f->start - 1 < 0)
        f->start = f->allocated;

    f->arr[f->start - 1] = item;
    f->start = (f->start - 1) % f->allocated;
    f->size++;
}

int dequeSize(Deque *f)
{
    return f->size;
}

dataType dequePopBack(Deque *f)
{
    if (f->end - 1 < 0)
        f->end = f->allocated;

    dataType popped = f->arr[f->end - 1];
    f->end = (f->end - 1) % f->allocated;
    f->size--;
    return popped;
}

dataType dequePopFront(Deque *f)
{
    dataType popped = f->arr[f->start];
    f->start = (f->start + 1) % f->allocated;
    f->size--;
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

bool dequeIsEmpty(Deque *f)
{
    if (f->size == 0)
    {
        return true;
    }
    return false;
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