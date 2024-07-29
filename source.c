// Includes
#include <stdlib.h>
#include <stdio.h>
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

void doTheSearch(int idxSource, int idxDest, Vector *cities, int numCities, char *algorithm)
{
    if (!strcmp(algorithm, "DFS") || !strcmp(algorithm, "BFS"))
    {
        tSource source;
        strcpy(source.sourceAlgorithm, algorithm);
        printf("deque");
    }

    if (!strcmp(algorithm, "UCS") || !strcmp(algorithm, "A*"))
    {
        tSource source;
        strcpy(source.sourceAlgorithm, algorithm);
        printf("heap");
    }
}