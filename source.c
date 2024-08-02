// Includes
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "source.h"
#include "heap.h"
#include "deque.h"
#include "city.h"
#include "neighbor.h"

#define INF 1e30

// Constants
#define MAX_LENGTH_NAME 30
#define MAX_TAM_DIRECTORY 1001

struct tSource
{
    char sourceAlgorithm[4];
    void *structure;
    void (*push)(void *structure, void *element);
    void *(*pop)(void *structure);
    bool (*is_empty)(void *structure);
};

void doTheSearch(int idxSource, int idxDest, Vector *cities, int numCities, char *algorithm)
{
    tSource *source = sourceConstruction(idxSource, idxDest, cities, numCities, algorithm);
    if (!strcmp(algorithm, "DFS"))
    {
        strcpy(source->sourceAlgorithm, algorithm);
        tCity *initialCity = getInitialCity(cities, idxSource);
        source->push(source->structure, initialCity);

        int numCities = vectorSize(cities);
        bool *visited = (bool *)calloc(numCities, sizeof(bool));
        tCity **predecessors = (tCity **)calloc(numCities, sizeof(tCity *));
        float *distances = (float *)calloc(numCities, sizeof(float)); // Array para armazenar distâncias

        int numVisitedCities = 0;
        float totalDistance = 0.0f; // Distância total

        while (!source->is_empty(source->structure))
        {
            tCity *currentCity = source->pop(source->structure);

            int currentIdx;
            for (currentIdx = 0; currentIdx < numCities; ++currentIdx)
            {
                if (compareCities(getName(currentCity), getName(vectorGet(cities, currentIdx))))
                {
                    break;
                }
            }

            if (visited[currentIdx])
            {
                continue;
            }

            visited[currentIdx] = true;
            numVisitedCities++;

            if (compareCities(getName(currentCity), getName(getInitialCity(cities, idxDest))))
            {

                Deque *pathDeque = dequeConstruct();
                tCity *traceCity = currentCity;
                while (traceCity != NULL)
                {
                    dequePushFront(pathDeque, traceCity);
                    int traceIdx;
                    for (traceIdx = 0; traceIdx < numCities; ++traceIdx)
                    {
                        if (compareCities(getName(traceCity), getName(vectorGet(cities, traceIdx))))
                        {
                            break;
                        }
                    }
                    traceCity = predecessors[traceIdx];
                }

                while (!dequeIsEmpty(pathDeque))
                {
                    tCity *cityInPath = dequePopFront(pathDeque);
                    printf("%s\n", getName(cityInPath));
                }

                totalDistance = getDistanceOrigin(currentCity);
                printf("Custo: %.2f ", totalDistance);
                printf("Num_Expandidos: %d\n", numVisitedCities);

                dequeDestroy(pathDeque);
                break;
            }

            int numNeighbors = getNumNeighbors(currentCity);
            for (int i = 0; i < numNeighbors; i++)
            {
                tNeighbor *neighbor = getNeighbor(currentCity, i);
                tCity *cityNeighbor = vectorGet(cities, getNeighborIdx(neighbor));

                int neighborIdx;
                for (neighborIdx = 0; neighborIdx < numCities; ++neighborIdx)
                {
                    if (compareCities(getName(cityNeighbor), getName(vectorGet(cities, neighborIdx))))
                    {
                        break;
                    }
                }

                if (!visited[neighborIdx])
                {
                    source->push(source->structure, cityNeighbor);
                    predecessors[neighborIdx] = currentCity;

                    float distanceToNeighbor = getDistance(neighbor);
                    float currentDistance = getDistanceOrigin(currentCity) + distanceToNeighbor;
                    distanceOrigin(cityNeighbor, currentDistance);
                }
            }
        }

        free(visited);
        free(predecessors);
        free(distances);
    }

    else if (!strcmp(algorithm, "BFS"))
    {
        strcpy(source->sourceAlgorithm, algorithm);
        tCity *initialCity = getInitialCity(cities, idxSource);
        source->push(source->structure, initialCity);

        int numCities = vectorSize(cities);
        bool *visited = (bool *)calloc(numCities, sizeof(bool));
        tCity **predecessors = (tCity **)calloc(numCities, sizeof(tCity *));
        float *distances = (float *)calloc(numCities, sizeof(float));

        int numVisitedCities = 0;
        float totalDistance = 0;

        Deque *pathDeque = dequeConstruct();

        while (!source->is_empty(source->structure))
        {
            tCity *currentCity = source->pop(source->structure);

            int currentIdx;
            for (currentIdx = 0; currentIdx < numCities; ++currentIdx)
            {
                if (compareCities(getName(currentCity), getName(vectorGet(cities, currentIdx))))
                {
                    break;
                }
            }

            if (visited[currentIdx])
            {
                continue;
            }

            visited[currentIdx] = true;
            numVisitedCities++;

            if (compareCities(getName(currentCity), getName(getInitialCity(cities, idxDest))))
            {
                tCity *traceCity = currentCity;
                while (traceCity != NULL)
                {
                    dequePushFront(pathDeque, traceCity);
                    int traceIdx;
                    for (traceIdx = 0; traceIdx < numCities; ++traceIdx)
                    {
                        if (compareCities(getName(traceCity), getName(vectorGet(cities, traceIdx))))
                        {
                            break;
                        }
                    }
                    traceCity = predecessors[traceIdx];
                }

                while (!dequeIsEmpty(pathDeque))
                {
                    tCity *cityInPath = dequePopFront(pathDeque);
                    printf("%s\n", getName(cityInPath));
                }

                totalDistance = getDistanceOrigin(currentCity);
                printf("Custo: %.2f ", totalDistance);
                printf("Num_Expandidos: %d\n", numVisitedCities);

                dequeDestroy(pathDeque);
                break;
            }

            int numNeighbors = getNumNeighbors(currentCity);
            for (int i = 0; i < numNeighbors; i++)
            {
                tNeighbor *neighbor = getNeighbor(currentCity, i);
                tCity *cityNeighbor = vectorGet(cities, getNeighborIdx(neighbor));

                int neighborIdx;
                for (neighborIdx = 0; neighborIdx < numCities; ++neighborIdx)
                {
                    if (compareCities(getName(cityNeighbor), getName(vectorGet(cities, neighborIdx))))
                    {
                        break;
                    }
                }

                if (!visited[neighborIdx])
                {
                    source->push(source->structure, cityNeighbor);
                    predecessors[neighborIdx] = currentCity;

                    float distanceToNeighbor = getDistance(neighbor);
                    float currentDistance = getDistanceOrigin(currentCity) + distanceToNeighbor;
                    distanceOrigin(cityNeighbor, currentDistance);
                }
            }
        }

        free(visited);
        free(predecessors);
        free(distances);
    }

    else if (!strcmp(algorithm, "UCS"))
    {
        strcpy(source->sourceAlgorithm, algorithm);

        
        int numCities = vectorSize(cities);
        bool *visited = (bool *)calloc(numCities, sizeof(bool));
        tCity **predecessors = (tCity **)calloc(numCities, sizeof(tCity *));
        float *costs = (float *)calloc(numCities, sizeof(float)); 

        for (int i = 0; i < numCities; ++i)
        {
            costs[i] = INF; 
        }

        tCity *initialCity = getInitialCity(cities, idxSource);
        source->push(source->structure, initialCity);
        int initialIdx;
        for (initialIdx = 0; initialIdx < numCities; ++initialIdx)
        {
            if (compareCities(getName(initialCity), getName(vectorGet(cities, initialIdx))))
            {
                break;
            }
        }
        costs[initialIdx] = 0.0f;

        float totalDistance = 0.0f; 

        while (!source->is_empty(source->structure))
        {

            tCity *currentCity = source->pop(source->structure);

            int currentIdx;
            for (currentIdx = 0; currentIdx < numCities; ++currentIdx)
            {
                if (compareCities(getName(currentCity), getName(vectorGet(cities, currentIdx))))
                {
                    break;
                }
            }

            if (visited[currentIdx])
            {
                continue;
            }

            visited[currentIdx] = true;

            if (compareCities(getName(currentCity), getName(getInitialCity(cities, idxDest))))
            {
                Deque *pathDeque = dequeConstruct();
                tCity *traceCity = currentCity;
                while (traceCity != NULL)
                {
                    dequePushFront(pathDeque, traceCity);
                    int traceIdx;
                    for (traceIdx = 0; traceIdx < numCities; ++traceIdx)
                    {
                        if (compareCities(getName(traceCity), getName(vectorGet(cities, traceIdx))))
                        {
                            break;
                        }
                    }
                    traceCity = predecessors[traceIdx];
                }

                while (!dequeIsEmpty(pathDeque))
                {
                    tCity *cityInPath = dequePopFront(pathDeque);
                    printf("%s\n", getName(cityInPath));
                }

                totalDistance = getDistanceOrigin(currentCity);
                printf("Custo: %.2f ", totalDistance);
                printf("Num_Expandidos: %d\n", numCities);

                dequeDestroy(pathDeque);
                break;
            }

            int numNeighbors = getNumNeighbors(currentCity);
            for (int i = 0; i < numNeighbors; i++)
            {
                tNeighbor *neighbor = getNeighbor(currentCity, i);
                tCity *cityNeighbor = vectorGet(cities, getNeighborIdx(neighbor));

                int neighborIdx;
                for (neighborIdx = 0; neighborIdx < numCities; ++neighborIdx)
                {
                    if (compareCities(getName(cityNeighbor), getName(vectorGet(cities, neighborIdx))))
                    {
                        break;
                    }
                }

                float distanceToNeighbor = getDistance(neighbor);
                float newCost = costs[currentIdx] + distanceToNeighbor;

                if (!visited[neighborIdx] && newCost < costs[neighborIdx])
                {
                    costs[neighborIdx] = newCost;
                    distanceOrigin(cityNeighbor, newCost);
                    predecessors[neighborIdx] = currentCity;
                    source->push(source->structure, cityNeighbor);
                }
            }
        }

        free(visited);
        free(predecessors);
        free(costs);
    }

        else if (!strcmp(algorithm, "A*"))
        {
            strcpy(source->sourceAlgorithm, algorithm);
            printf("%s", source->sourceAlgorithm);
        }
        destroySource(source);
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
            source->push = heapPush;
            source->pop = heapPop;
            source->is_empty = heapIsEmpty;
        }

        else if (!strcmp(algorithm, "A*"))
        {
            source->structure = heapConstruct(compareCitiesByDistance);
            source->push = heapPush;
            source->pop = heapPop;
            source->is_empty = heapIsEmpty;
        }
    }

    void destroySource(tSource * source)
    {
        if (!strcmp(source->sourceAlgorithm, "DFS") || !strcmp(source->sourceAlgorithm, "BFS"))
        {
            dequeDestroy((Deque *)source->structure);
        }
        else if (!strcmp(source->sourceAlgorithm, "UCS") || !strcmp(source->sourceAlgorithm, "A*"))
        {
            heapDestroy((Heap *)source->structure, cityDestroy);
        }
        free(source);
    }