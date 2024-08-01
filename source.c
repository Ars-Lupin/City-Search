// Includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "source.h"
#include "heap.h"
#include "deque.h"
#include "city.h"
#include "neighbor.h"

// Constants
#define MAX_LENGTH_NAME 30
#define MAX_TAM_DIRECTORY 1001

struct tSource
{
    char sourceAlgorithm[4];
    void *structure;
    void (*push)(void *structure, void *element);
    void *(*pop)(void *structure);
    int (*is_empty)(void *structure);
};

void doTheSearch(int idxSource, int idxDest, Vector *cities, int numCities, char *algorithm)
{
    tSource *source = sourceConstruction(idxSource, idxDest, cities, numCities, algorithm);
    if (!strcmp(algorithm, "DFS"))
    {
        strcpy(source->sourceAlgorithm, algorithm);
        source->push(source->structure, getInitialCity(cities, idxSource));
        for (int i = 0; i < getNumNeighbors(getInitialCity(cities, idxSource)); i++)
        {
            
            tNeighbor *neighbor = getNeighbor(getInitialCity(cities, idxSource), i);
            tCity *cityNeighbor = vectorGet(cities, getNeighborIdx(neighbor));
            source->push(source->structure, cityNeighbor);
        }
        // printDeque(source->structure);
        if (compareCities(getName(getInitialCity(cities, idxDest)), getName(source->pop(source->structure))))
        {
            printf("Cidades iguais\n");
        }

        printf("%s", source->sourceAlgorithm);
    }
    else if (!strcmp(algorithm, "BFS"))
    {
        strcpy(source->sourceAlgorithm, algorithm);
        printf("%s", source->sourceAlgorithm);
    }

    else if (!strcmp(algorithm, "UCS"))
    {
        strcpy(source->sourceAlgorithm, algorithm);
        printf("%s", source->sourceAlgorithm);
    }

    else if (!strcmp(algorithm, "A*"))
    {
        strcpy(source->sourceAlgorithm, algorithm);
        printf("%s", source->sourceAlgorithm);
    }
}

tSource *sourceConstruction(int idxSource, int idxDest, Vector *cities, int numCities, char *algorithm)
{

    tSource *source = (tSource *)calloc(1, sizeof(tSource));
    if (!strcmp(algorithm, "DFS"))
    {

        source->structure = dequeConstruct();
        source->push = dequePushBack;
        source->pop = dequePopBack;
        source->is_empty = dequeIsEmpty;
    }
    else if (!strcmp(algorithm, "BFS"))
    {
        source->structure = dequeConstruct();
        source->push = dequePushBack;
        source->pop = dequePopFront;
        source->is_empty = dequeIsEmpty;
    }

    else if (!strcmp(algorithm, "UCS"))
    {
        source->structure = heapConstruct(compareCitiesByDistance);
        source->push = (void (*)(void *, void *))heapPush;
        source->pop = (void *(*)(void *))heapPop;
        source->is_empty = (int (*)(void *))heapIsEmpty;
    }

    else if (!strcmp(algorithm, "A*"))
    {
        source->structure = heapConstruct(compareCitiesByDistance);
        source->push = (void (*)(void *, void *))heapPush;
        source->pop = (void *(*)(void *))heapPop;
        source->is_empty = (int (*)(void *))heapIsEmpty;
    }
}