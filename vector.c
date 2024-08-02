#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

struct Vector
{
    dataType *data;
    int size;
    int allocated;
};

Vector *vectorConstruct()
{

    Vector *vetor = (Vector *)calloc(1, sizeof(Vector));
    vetor->allocated = 1;

    if (!vetor)
    {
        printf("ERRO: falha na alocacao do vector");
        exit(1);
    }

    vetor->data = (dataType *)calloc(1, sizeof(dataType));

    if (!vetor->data)
    {
        printf("ERRO: falha na alocacao dos dados de vector");
        exit(1);
    }

    return vetor;
}

void vectorPushBack(Vector *v, dataType val)
{

    if (v->size >= v->allocated)
    {
        v->allocated *= 2;
        v->data = (dataType *)realloc(v->data, v->allocated * (sizeof(dataType)));
    }

    v->data[v->size] = val;
    v->size++;
}

int vectorSize(Vector *v)
{

    if (v)
        return v->size;

    return 0;
}

dataType vectorGet(Vector *v, int i)
{

    if (i >= 0 && i < vectorSize(v))
        return v->data[i];

    printf("ERRO: indice invalido");
    exit(1);
}

void vectorSet(Vector *v, int i, dataType val)
{

    if (i >= 0 && i < vectorSize(v))
    {
        v->data[i] = val;
    }
    else
    {
        printf("ERRO: indice invalido");
        exit(1);
    }
}

int vectorFind(Vector *v, dataType val, int cmp(const void *, const void *))
{
    int i;
    for (i = 0; i <= vectorSize(v) - 1; i++)
    {
        if (cmp(v->data[i], val) == 0)
            return i;
    }

    return -1;
}

void vectorDestroy(Vector *v, void (*destroyDataType)(dataType))
{
    int i;
    if (v)
    {
        if (v->data)
        {
            for (i = 0; i < vectorSize(v); i++)
            {
                if (v->data[i])
                    destroyDataType(v->data[i]);
            }
            free(v->data);
        }
        free(v);
    }
}

dataType vectorMax(Vector *v, int cmp(const void *, const void *))
{
    int i;
    dataType max = v->data[0];

    for (i = 1; i < vectorSize(v); i++)
    {

        if (cmp(max, v->data[i]) < 0)
            max = v->data[i];
    }

    return max;
}

dataType vectorMin(Vector *v, int cmp(const void *, const void *))
{
    int i;
    dataType min = v->data[0];

    for (i = 1; i < vectorSize(v); i++)
    {

        if (cmp(min, v->data[i]) > 0)
            min = v->data[i];
    }

    return min;
}

int vectorArgmax(Vector *v, int cmp(const void *, const void *))
{

    return vectorFind(v, vectorMax(v, cmp), cmp);
}

int vectorArgmin(Vector *v, int cmp(const void *, const void *))
{

    return vectorFind(v, vectorMin(v, cmp), cmp);
}

dataType vectorRemove(Vector *v, int i)
{

    dataType elementRemoved = v->data[i];

    for (; i < vectorSize(v) - 1; i++)
    {
        v->data[i] = v->data[i + 1];
    }

    v->size--;

    return elementRemoved;
}

dataType vectorPopFront(Vector *v)
{

    dataType frontElement = vectorRemove(v, 0);

    return frontElement;
}

dataType vectorPopBack(Vector *v)
{

    dataType backElement = vectorRemove(v, v->size - 1);

    return backElement;
}

void vectorInsert(Vector *v, int i, dataType val)
{
    int j;
    if (vectorSize(v) == v->allocated)
    {
        v->allocated++;
        v->data = (dataType *)realloc(v->data, v->allocated * (sizeof(dataType)));
    }

    for (j = v->size; j > i; j--)
    {
        v->data[j] = v->data[j - 1];
    }

    v->data[i] = val;
    v->size++;
}

void vectorSwap(Vector *v, int i, int j)
{

    dataType aux = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = aux;
}

void vectorSort(Vector *v, int(cmp_fn)(const void *prod1, const void *prod2))
{
    int j;
    int swapped;

    while (1)
    {

        swapped = 0;

        for (j = 0; j < vectorSize(v) - 1; j++)
        {

            if (cmp_fn(v->data[j], v->data[j + 1]) > 0)
            {
                vectorSwap(v, j, j + 1);
                swapped = 1;
            }
        }

        if (!swapped)
            break;
    }
}

int vectorBinarySearch(Vector *v, dataType val)
{

    int idxMin = 0, idxMax = vectorSize(v) - 1, idxMid;

    while (idxMin <= idxMax)
    {

        idxMid = (idxMin + idxMax) / 2;

        if (v->data[idxMid] == val)
        {
            return idxMid;
        }
        else if (val < v->data[idxMid])
        {
            idxMax = idxMid - 1;
        }
        else if (val > v->data[idxMid])
        {
            idxMin = idxMid + 1;
        }
    }

    return -1;
}

void vectorReverse(Vector *v)
{

    if (vectorSize(v) == 1)
        return;

    int i = 0, j = vectorSize(v) - 1;

    while (1)
    {

        vectorSwap(v, i, j);
        i++;

        if (i >= j)
            break;

        j--;
    }
}


