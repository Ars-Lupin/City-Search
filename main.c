// Includes
#include <stdio.h>
#include <stdlib.h>
#include "city.h"
#include "neighbor.h"
#include "source.h"

// Constants
#define MAX_LENGTH_NAME 30
#define MAX_TAM_DIRECTORY 1001

int main(int argc, char **argv)
{

    // Read directory name
    if (argc < 2)
        exit(printf("ERRO: local dos arquivos não informado"));

    char directory[MAX_TAM_DIRECTORY];
    char input[MAX_TAM_DIRECTORY];
    sprintf(input, "%s", argv[1]);
    // sprintf(input, "input.txt");

    FILE *arq = fopen(input, "r");

    if (!arq)
        exit(printf("ERRO: falha ao abrir arquivo input.txt"));

    char algorithm[MAX_LENGTH_NAME];
    int numCities, idxSource, idxDest;

    fscanf(arq, "%s", algorithm);
    fscanf(arq, "%d %d", &idxSource, &idxDest);
    fscanf(arq, "%d", &numCities);

    // printf("%s %d %d %d\n", algorithm, idxSource, idxDest, numCities);

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
    printf("FEZ A PESQUISA\n");

    fclose(arq);
    return 0;
}
