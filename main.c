// Includes
#include <stdio.h>
#include <stdlib.h>
#include "city.h"
#include "neighbor.h"
#include "source.h"

// Constants
#define MAX_LENGTH_NAME 30
#define MAX_TAM_DIRECTORY 1001

int main()
{
    char input[MAX_TAM_DIRECTORY];
    scanf("%s", input);
    getchar();

    FILE *arq = fopen(input, "r");

    if (!arq)
        exit(printf("ERRO: falha ao abrir arquivo input.txt"));

    char algorithm[MAX_LENGTH_NAME];
    int numCities, idxSource, idxDest;

    fscanf(arq, "%s\n", algorithm);
    fscanf(arq, "%d %d\n", &idxSource, &idxDest);
    fscanf(arq, "%d", &numCities);

    Vector *cities = vectorConstruct();
    char cityName[MAX_LENGTH_NAME];
    float coordX, coordY;
    int numNeighbors;
    int i, j;

    for (i = 0; i < numCities; i++)
    {
        fscanf(arq, "\n%s %f %f %d", cityName, &coordX, &coordY, &numNeighbors);
        tCity *city = cityConstructor(cityName, coordX, coordY, numNeighbors);

        for (j = 0; j < numNeighbors; j++)
        {

            float neighborDistance;
            int neighborIdx;

            fscanf(arq, "%d %f", &neighborIdx, &neighborDistance);
            tNeighbor *neighbor = neighborConstructor(neighborIdx, neighborDistance);

            pushNeighbor(city, neighbor);
        }

        vectorPushBack(cities, city);
    }

    doTheSearch(idxSource, idxDest, cities, numCities, algorithm);

    fclose(arq);
    return 0;
}
