// Includes
#include <stdlib.h>
#include <stdio.h>
#include "neighbor.h"

// Constants
#define MAX_LENGTH_NAME 30
#define MAX_TAM_DIRECTORY 1001

struct tNeighbor
{
    float distance;
    int idx;
};

tNeighbor *neighborConstructor(int idx, int distance)
{

    tNeighbor *neighbor = (tNeighbor *)calloc(1, sizeof(tNeighbor));

    if (!neighbor)
        exit(printf("ERRO: falha ao alocar memoria para neighbor"));

    neighbor->distance = distance;
    neighbor->idx = idx;

    return neighbor;
}

float getDistance(tNeighbor *n)
{

    return (n->distance);
}

int getNeighborIdx(tNeighbor *n)
{

    return (n->idx);
}

void neighborDestroy(tNeighbor *n)
{

    if (n)
        free(n);
}
