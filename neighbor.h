#ifndef _NEIGHBOR_H_
#define _NEIGHBOR_H_

typedef struct tNeighbor tNeighbor;

tNeighbor *neighborConstructor(int idx, int distance);
float getDistance(tNeighbor *n);
int getNeighborIdx(tNeighbor *n);
void neighborDestroy(tNeighbor *n);

#endif