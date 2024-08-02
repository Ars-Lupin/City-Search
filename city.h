#ifndef _CITY_H_
#define _CITY_H_

#include "neighbor.h"
#include "vector.h"
#include <stdbool.h>

typedef struct tCity tCity;

tCity *cityConstructor(char *name, int x, int y, int numNeighbors);

const char *getName(tCity *city);
float getCoordenateX(tCity *city);
float getCoordenateY(tCity *city);

int getNumNeighbors(tCity *city);
void *getNeighbor(tCity *city, int idx);
void pushNeighbor(tCity *city, void *neighbor);

bool compareCities(const void *a, const void *b);
bool compareCitiesByDistance(const void *a, const void *b);
void cityDestroy(tCity *city);

tCity *getInitialCity(Vector *cities, int idxSource);
void distanceOrigin(tCity *city, float distance);
float getDistanceOrigin(tCity *city);

#endif