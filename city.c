// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "city.h"


// Constants
#define MAX_LENGTH_NAME 30
#define MAX_TAM_DIRECTORY 1001

struct tCity
{
    char name[MAX_LENGTH_NAME];
    float x;
    float y;
    int idx;
    float distanceOrigin;
    float distanceHeuristic;
    int numNeighbors;
    Vector *neighbors;
};

tCity *cityConstructor(char *name, int x, int y, int numNeighbors, int idx)
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
    city->idx = idx;

    return city;
}

const char *getName(tCity *city)
{

    return (city->name);
}

int getIdx(tCity *city)
{
    return (city->idx);
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

Vector *getNeighbors(tCity *city)
{
    return city->neighbors;
}

void *getNeighbor(tCity *city, int idx)
{
    return vectorGet(city->neighbors, idx);
}

void pushNeighbor(tCity *city, void *neighbor)
{

    vectorPushBack(city->neighbors, neighbor);
}

int compareCities(const void *a, const void *b)
{

    const tCity *cityA = (const tCity *)a;
    const tCity *cityB = (const tCity *)b;

    if (!strcmp(cityA->name, cityB->name))
    {
        return 1;
    }

    return 0;
}

int compareCity(tCity *cityA, void *dequeCity)
{
    tCity *cityB = (tCity *)dequeCity;
    if (!strcmp(cityA->name, cityB->name))
    {
        return 1;
    }

    return 0;
}

int compareCitiesByDistance(void *a, void *b)
{

    tCity *cityA = ( tCity *)a;
    tCity *cityB = ( tCity *)b;

    if (cityA->distanceOrigin > cityB->distanceOrigin)
    {
        return 1;
    }

    return 0;
}

int compareCitiesByHeuristic(void *a, void *b) {
    tCity *cityA = (tCity *)a;
    tCity *cityB = (tCity *)b;

    if ((cityA->distanceOrigin + cityA->distanceHeuristic) > (cityB->distanceOrigin + cityB->distanceHeuristic)) {
        return 1;   
    }
    return 0;
}


void cityDestroy(void *c)
{
    tCity *city = (tCity *)c;
    int i;
    if (city)
    {

        for (i = 0; i < city->numNeighbors; i++)
        {
            tNeighbor *neighborPopped = vectorPopBack(city->neighbors);
            neighborDestroy(neighborPopped);
        }

        vectorDestroy(city->neighbors);
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

void distanceHeuristic(tCity *city, tCity *destCity)
{
    city->distanceHeuristic = heuristic(city, destCity);
}

float getDistanceHeuristic(tCity *city)
{
    return city->distanceHeuristic;
}

float getDistanceOrigin(tCity *city)
{
    return city->distanceOrigin;
}

float heuristic(tCity *cityA, tCity *cityB)
{
   return sqrt(pow(cityA->x - cityB->x, 2) + pow(cityA->y - cityB->y, 2));
}