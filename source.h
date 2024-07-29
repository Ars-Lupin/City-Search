#ifndef _SOURCE_H_
#define _SOURCE_H_

#include "neighbor.h"
#include "vector.h"

typedef struct tSource tSource;

void doTheSearch(int idxSource, int idxDest, Vector* cities, int numCities, char* algorithm);


#endif