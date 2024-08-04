// Includes
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "source.h"

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

int eq_name(void *c1, void *c2)
{
    tCity *a = (tCity *)c1;
    tCity *b = (tCity *)c2;
    return compareCities(getName((tCity *)a), getName((tCity *)b));
}

void doTheSearch(int idxSource, int idxDest, Vector *cities, int numCities, char *algorithm, int (*cmp)(void *, void *))
{
    int findCity = 0;
    int i;
    tSource *source = sourceConstruction(idxSource, idxDest, cities, numCities, algorithm, cmp);
    if (!strcmp(algorithm, "DFS") || !strcmp(algorithm, "BFS"))
    {
        int (*eqName)(void *, void *);
        eqName = eq_name;
        strcpy(source->sourceAlgorithm, algorithm);
        tCity *initialCity = getInitialCity(cities, idxSource);
        source->push(source->structure, initialCity);

        bool *visited = (bool *)calloc(numCities, sizeof(bool));
        int *parent = (int *)calloc(numCities, sizeof(int));
        float *distances = (float *)calloc(numCities, sizeof(float));

        for (i = 0; i < numCities; i++)
        {
            parent[i] = -1;
            distances[i] = 0;
        }

        int numVisitedCities = 0;
        float totalDistance = 0;

        while (!source->is_empty(source->structure))
        {
            tCity *currentCity = source->pop(source->structure);
            int currentIdx = getIdx(currentCity);
            if (compareCities(getName(currentCity), getName(getInitialCity(cities, idxDest))))
            {
                findCity = 1;
                visited[currentIdx] = true;
                numVisitedCities++;
                break;
            }

            int numNeighbors = getNumNeighbors(currentCity);

            for (i = 0; i < numNeighbors; i++)
            {
                tNeighbor *neighbor = getNeighbor(currentCity, i);
                int idxNeighbor = getNeighborIdx(neighbor);
                float distanceNeighbor = getDistance(neighbor);
                tCity *neighborCity = vectorGet(cities, idxNeighbor);

                if (visited[idxNeighbor])
                {
                    continue;
                }
                else if (dequeFind(source->structure, neighborCity, eqName) == -1)
                {
                    source->push(source->structure, neighborCity);
                }
                if (parent[idxNeighbor] == -1)
                {
                    parent[idxNeighbor] = currentIdx;
                    distances[idxNeighbor] = distanceNeighbor;
                }
            }
            if (!visited[currentIdx])
            {
                visited[currentIdx] = true;
                numVisitedCities++;
            }
        }

        if (findCity == 1)
        {
            Deque *pathDeque = dequeConstruct();
            int traceCity = idxDest;

            while (traceCity != -1)
            {
                dequePushBack(pathDeque, vectorGet(cities, traceCity));
                totalDistance += distances[traceCity];
                traceCity = parent[traceCity];
            }

            while (!dequeIsEmpty(pathDeque))
            {
                tCity *cityInPath = dequePopBack(pathDeque);
                printf("%s\n", getName(cityInPath));
            }

            printf("Custo: %.2f ", totalDistance);
            printf("Num_Expandidos: %d\n", numVisitedCities);

            dequeDestroy(pathDeque);
        }

        free(visited);
        free(parent);
        free(distances);
    }
    else if (!strcmp(algorithm, "UCS") || !strcmp(algorithm, "A*"))
    {
        strcpy(source->sourceAlgorithm, algorithm);
        tCity *initialCity = getInitialCity(cities, idxSource);
        source->push(source->structure, initialCity);

        bool *visited = (bool *)calloc(numCities, sizeof(bool));
        int *parent = (int *)calloc(numCities, sizeof(int));
        float *distances = (float *)calloc(numCities, sizeof(float));

        for (i = 0; i < numCities; i++)
        {
            parent[i] = -1;
            distances[i] = 0;
        }

        int numVisitedCities = 0;

        while (!source->is_empty(source->structure))
        {
            tCity *currentCity = source->pop(source->structure);
            int currentIdx = getIdx(currentCity);

            if (compareCities(getName(currentCity), getName(getInitialCity(cities, idxDest))))
            {
                findCity = 1;
                visited[currentIdx] = true;
                numVisitedCities++;
                break;
            }
            else if (visited[currentIdx])
            {
                continue;
            }

            int numNeighbors = getNumNeighbors(currentCity);

            for (i = 0; i < numNeighbors; i++)
            {
                tNeighbor *neighbor = getNeighbor(currentCity, i);
                int idxNeighbor = getNeighborIdx(neighbor);
                if (!visited[idxNeighbor])
                {
                    float distanceNeighbor = getDistance(neighbor);
                    tCity *neighborCity = getInitialCity(cities, idxNeighbor);

                    if (parent[idxNeighbor] != -1)
                    {

                        float distanceOld = getDistanceOrigin(getInitialCity(cities, idxNeighbor)) +
                                            getDistanceHeuristic(getInitialCity(cities, idxNeighbor));

                        float distanceNew = getDistanceOrigin(getInitialCity(cities, getIdx(currentCity))) +
                                            distanceNeighbor + getDistanceHeuristic(getInitialCity(cities, idxNeighbor));

                        if (distanceOld > distanceNew)
                        {
                            parent[idxNeighbor] = getIdx(currentCity);
                            distances[idxNeighbor] = distanceNeighbor;
                        }
                    }
                    else
                    {
                        parent[idxNeighbor] = getIdx(currentCity);
                        distances[idxNeighbor] = distanceNeighbor;
                    }

                    float totalDistance = 0;
                    while (idxNeighbor != idxSource)
                    {
                        totalDistance += distances[idxNeighbor];
                        idxNeighbor = parent[idxNeighbor];
                    }
                    distanceOrigin(neighborCity, totalDistance);

                    if (!strcmp(algorithm, "A*"))
                    {
                        distanceHeuristic(neighborCity, getInitialCity(cities, idxDest));
                    }
                    source->push(source->structure, neighborCity);
                }
            }
            visited[currentIdx] = true;
            numVisitedCities++;
        }

        if (findCity == 1)
        {
            Deque *pathDeque = dequeConstruct();
            int traceCity = idxDest;
            float totalDistance = 0;

            while (traceCity != -1)
            {
                dequePushBack(pathDeque, vectorGet(cities, traceCity));
                totalDistance += distances[traceCity];
                traceCity = parent[traceCity];
            }

            while (!dequeIsEmpty(pathDeque))
            {
                tCity *cityInPath = dequePopBack(pathDeque);
                printf("%s\n", getName(cityInPath));
            }

            printf("Custo: %.2f ", totalDistance);
            printf("Num_Expandidos: %d\n", numVisitedCities);

            dequeDestroy(pathDeque);
        }

        free(visited);
        free(parent);
        free(distances);
    }
    destroySource(source, cities);
    if (findCity == 0)
    {
        printf("IMPOSSIVEL\n");
    }
}

tSource *sourceConstruction(int idxSource, int idxDest, Vector *cities, int numCities, char *algorithm, int (*cmp)(void *, void *))
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
        source->push = heapPush;
        source->pop = heapPop;
        source->is_empty = heapIsEmpty;
    }

    else if (!strcmp(algorithm, "A*"))
    {
        source->structure = heapConstruct(compareCitiesByHeuristic);
        source->push = heapPush;
        source->pop = heapPop;
        source->is_empty = heapIsEmpty;
    }
    return source;
}

void destroySource(tSource *source, Vector *cities)
{
    int size = vectorSize(cities);
    int i;

    for (i = 0; i < size; i++)
    {
        void *c = vectorPopBack(cities);
        cityDestroy(c);
    }
    vectorDestroy(cities);

    if (!strcmp(source->sourceAlgorithm, "DFS") || !strcmp(source->sourceAlgorithm, "BFS"))
    {
        dequeDestroy((Deque *)source->structure);
    }
    else if (!strcmp(source->sourceAlgorithm, "UCS") || !strcmp(source->sourceAlgorithm, "A*"))
    {
        heapDestroy((Heap *)source->structure);
    }
    free(source);
}