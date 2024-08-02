// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "city.h"
#include "neighbor.h"

// Constants
#define MAX_LENGTH_NAME 30
#define MAX_TAM_DIRECTORY 1001

struct tCity
{
    char name[MAX_LENGTH_NAME];
    float x;
    float y;
    float distanceOrigin;
    int numNeighbors;
    Vector *neighbors;
};

tCity *cityConstructor(char *name, int x, int y, int numNeighbors)
{

    tCity *city = (tCity *)calloc(1, sizeof(tCity));

    if (!city)
        exit(0);

    city->neighbors = vectorConstruct();

    if (!city->neighbors)
        exit(0);

    strcpy(city->name, name);
    city->x = x;
    city->y = y;
    city->numNeighbors = numNeighbors;

    return city;
}

const char *getName(tCity *city)
{

    return (city->name);
}

float getCoordenateX(tCity *city)
{

    return (city->x);
}

float getCoordenateY(tCity *city)
{

    return (city->y);
}

int getNumNeighbors(tCity *city)
{

    return (city->numNeighbors);
}

void *getNeighbor(tCity *city, int idx)
{
    return vectorGet(city->neighbors, idx);
}

void pushNeighbor(tCity *city, void *neighbor)
{

    vectorPushBack(city->neighbors, neighbor);
}

bool compareCities(const void *a, const void *b)
{

    const tCity *cityA = (const tCity *)a;
    const tCity *cityB = (const tCity *)b;

    if (!strcmp(cityA->name, cityB->name))
    {
        return true;
    }

    return false;
}

bool compareCitiesByDistance(const void *a, const void *b)
{

    const tCity *cityA = (const tCity *)a;
    const tCity *cityB = (const tCity *)b;

    if (cityA->distanceOrigin > cityB->distanceOrigin);
    {
        return true;
    }

    return false;
}

void cityDestroy(tCity *city)
{
    int i;
    if (city)
    {

        for (i = 0; i < city->numNeighbors; i++)
        {
            tNeighbor *neighborPopped = vectorPopBack(city->neighbors);
            neighborDestroy(neighborPopped);
        }

        vectorDestroy(city->neighbors, (void *)neighborDestroy);
        free(city);
    }
}

tCity *getInitialCity(Vector *cities, int idxSource)
{
    return vectorGet(cities, idxSource);
}

void distanceOrigin(tCity *city, float distance)
{
    city->distanceOrigin = distance;
}

float getDistanceOrigin(tCity *city)
{
    return city->distanceOrigin;
}