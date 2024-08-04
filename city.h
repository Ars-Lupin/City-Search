#ifndef _CITY_H_
#define _CITY_H_

#include "neighbor.h"
#include "vector.h"
#include "neighbor.h"
#include <stdbool.h>
#include <math.h>

typedef struct tCity tCity;

tCity *cityConstructor(char *name, int x, int y, int numNeighbors, int idx);

const char *getName(tCity *city);
float getCoordenateX(tCity *city);
float getCoordenateY(tCity *city);

int getNumNeighbors(tCity *city);
Vector *getNeighbors(tCity *city);
void *getNeighbor(tCity *city, int idx);
void pushNeighbor(tCity *city, void *neighbor);

int compareCities(const void *a, const void *b);
int compareCity(tCity *cityA, void *dequeCity);
int compareCitiesByDistance(void *a, void *b);
int compareCitiesByHeuristic(void *a, void *b);
void cityDestroy(void *c);
int getIdx(tCity *city);

tCity *getInitialCity(Vector *cities, int idxSource);
void distanceOrigin(tCity *city, float distance);
float getDistanceOrigin(tCity *city);
void distanceHeuristic(tCity *city, tCity *destCity);
float getDistanceHeuristic(tCity *city);
float heuristic(tCity *cityA, tCity *cityB);

#endif