
#ifndef _VECTOR_H_
#define _VECTOR_H_

typedef void *dataType;

typedef struct Vector Vector;

// Cria um vetor vazio
Vector *vectorConstruct();

// Adiciona um elemento no final do vetor
void vectorPushBack(Vector *v, dataType val);

// Retorna o i-ésimo elemento do vetor
dataType vectorGet(Vector *v, int i);

// Atribui o valor val ao i-ésimo elemento do vetor
void vectorSet(Vector *v, int i, dataType val);

// Retorna o tamanho do vetor
int vectorSize(Vector *v);

// Retorna o indice do primeiro elemento com valor val. Retorna -1 se nao encontrado.
int vectorFind(Vector *v, dataType val, int cmp(const void *, const void *));

// Remove o i-ésimo elemento do vetor.
dataType vectorRemove(Vector *v, int i);

// Remove o primeiro elemento
dataType vectorPopFront(Vector *v);

// Remove o ultimo elemento
dataType vectorPopBack(Vector *v);

// Insere o elemento na i-esima posicao
void vectorInsert(Vector *v, int i, dataType val);

// Troca os elementos das posições i e j (i vira j e j vira i)
void vectorSwap(Vector *v, int i, int j);

// Ordena o vetor in-place (sem criar um novo vetor)
void vectorSort(Vector *v, int(cmp_fn)(const void *prod1, const void *prod2));

// Retorna o indice de val usando busca binaria. Retorna -1 se nao encontrado.
int vectorBinarySearch(Vector *v, dataType val);

// Inverte o vetor in-place (sem criar um novo vetor)
void vectorReverse(Vector *v);

// Libera a memoria alocada para o vetor
void vectorDestroy(Vector *v);

dataType vectorMax(Vector *v, int cmp(const void *, const void *));

dataType vectorMin(Vector *v, int cmp(const void *, const void *));

int vectorArgmax(Vector *v, int cmp(const void *, const void *));

int vectorArgmin(Vector *v, int cmp(const void *, const void *));

#endif
