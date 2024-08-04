#ifndef _SOURCE_H_
#define _SOURCE_H_

#include "neighbor.h"
#include "vector.h"
#include "heap.h"
#include "deque.h"
#include "city.h"
#include "neighbor.h"

typedef struct tSource tSource;

void doTheSearch(int idxSource, int idxDest, Vector *cities, int numCities,
                 char *algorithm, int (*cmp)(void *, void *));

tSource *sourceConstruction(int idxSource, int idxDest, Vector *cities, int numCities,
                            char *algorithm, int (*cmp)(void *, void *));
void destroySource(tSource *source, Vector *cities);

int eq_name(void *c1, void *c2);

#endif