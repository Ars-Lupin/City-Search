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
    tSource *source = (tSource *)calloc(1, sizeof(tSource));
    if (!strcmp(algorithm, "DFS"))
    {
        strcpy(source->sourceAlgorithm, algorithm);
        printf("%s", source->sourceAlgorithm);
    }
    if (!strcmp(algorithm, "BFS"))
    {
        strcpy(source->sourceAlgorithm, algorithm);
        printf("%s", source->sourceAlgorithm);
    }

    if (!strcmp(algorithm, "UCS"))
    {
        strcpy(source->sourceAlgorithm, algorithm);
        printf("%s", source->sourceAlgorithm);
    }

    if (!strcmp(algorithm, "A*"))
    {
        strcpy(source->sourceAlgorithm, algorithm);
        printf("%s", source->sourceAlgorithm);
    }
}