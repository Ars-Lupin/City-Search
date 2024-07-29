#include "deque.h"
#include <stdlib.h>
typedef void *dataType;

struct Deque
{

    dataType *data;
    int start;
    int end;
    int size;
    int allocated;
};

Deque *dequeConstruct()
{

    Deque *deque = (Deque *)calloc(1, sizeof(Deque));
    deque->data = (dataType *)calloc(1, sizeof(dataType));

    deque->allocated = 1;

    return deque;
}

void dequePushBack(Deque *f, dataType item)
{

    int idx_source;
    int idx_dest;

    if (f->size >= f->allocated)
    {
        f->allocated *= 2;

        dataType *new_data = (dataType *)malloc(f->allocated * sizeof(dataType));

        for (int i = 0; i < f->size; i++)
        {
            idx_source = (f->start + i) % f->size;
            idx_dest = i;

            new_data[idx_dest] = f->data[idx_source];
        }

        f->start = 0;
        f->end = f->size;
        free(f->data);
        f->data = new_data;
    }

    f->data[f->end] = item;
    f->end = (f->end + 1) % f->allocated;
    f->size++;
}

void dequePushFront(Deque *f, dataType item)
{

    int idx_source;
    int idx_dest;

    if (f->size >= f->allocated)
    {
        f->allocated *= 2;

        dataType *new_data = (dataType *)malloc(f->allocated * sizeof(dataType));

        for (int i = 0; i < f->size; i++)
        {
            idx_source = (f->start + i) % f->size;
            idx_dest = i;

            new_data[idx_dest] = f->data[idx_source];
        }

        f->start = 0;
        f->end = f->size;
        free(f->data);
        f->data = new_data;
    }

    if (f->start - 1 < 0)
        f->start = f->allocated;

    f->data[f->start - 1] = item;
    f->start = (f->start - 1) % f->allocated;
    f->size++;
}

dataType dequePopBack(Deque *f)
{

    if (f->end - 1 < 0)
        f->end = f->allocated;

    dataType popped = f->data[f->end - 1];
    f->end = (f->end - 1) % f->allocated;
    f->size--;
    return popped;
}

dataType dequePopFront(Deque *f)
{

    dataType popped = f->data[f->start];
    f->start = (f->start + 1) % f->allocated;
    f->size--;
    return popped;
}

void dequeDestroy(Deque *f)
{

    if (f)
    {

        int idx;

        for (int i = 0; i < f->size; i++)
        {
            idx = (f->start + i) % f->allocated;
            free(f->data[idx]);
        }

        free(f->data);
        free(f);
    }
}

int dequeSize(Deque *f)
{
    return f->size;
}

int dequeAllocated(Deque *f)
{
    return f->allocated;
}
